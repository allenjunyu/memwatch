//
// Created by dengyao on 18-3-27.
//

#include <stdio.h>
#include "memwatch.h"

static size_t g_total_malloc = 0;

typedef struct ptr_info{
    void* ptr;
    size_t size;
    const char* file;
    int line;
    struct ptr_info* prev;
    struct ptr_info* next;
}ptr_info;

static ptr_info* g_total_head = NULL; // 头指针

void set_ptr_info(ptr_info* p,void* ptr,size_t size,const char* file,int line, ptr_info* prev, ptr_info* next){
    if(p!=NULL){
        p->ptr = ptr;
        p->size = size;
        p->file = file;
        p->line = line;
        p->prev = prev;
        p->next = next;
    }
}

void* mw_malloc(size_t num_bytes, const char* file, int line){
    void* res = malloc(num_bytes);
    if(res!=NULL){
        g_total_malloc+=num_bytes;
        if(g_total_head==NULL){
            ptr_info* new_node = (ptr_info*)malloc(sizeof(ptr_info));
            set_ptr_info(new_node,res,num_bytes,file,line,NULL,NULL);
            g_total_head = new_node;
        }else{
            ptr_info* new_node = (ptr_info*)malloc(sizeof(ptr_info));
            // 往头指针中添加
            set_ptr_info(new_node,res,num_bytes,file,line,NULL,g_total_head);
            g_total_head->prev = new_node;
            g_total_head = new_node;
        }
        printf("#mw %s:%d malloc %d byte(s) for pointer %p, now total %d byte(s)\n",file,line,num_bytes,res,g_total_malloc);
    }

    return res;
}

ptr_info* find_ptr_info_from_total(ptr_info* head,void* ptr){
    if(head==NULL){
        return NULL;
    }else{
        while(head!=NULL){
            if(head->ptr == ptr){
                return head;
            }else{
                head = head->next;
            }
        }
        return NULL; // 仍没找到
    }
}

void mw_free(void* p, const char* file, int line){
    ptr_info* ptr = find_ptr_info_from_total(g_total_head,p);
    if(ptr==NULL){
        printf("#wm error: not found pointer %p when do free!\n",p);
        return;
    }
    free(p);
    g_total_malloc-=ptr->size;

    printf("#mw %s:%d free %d byte(s) for pointer %p, now total %d byte(s)\n",
           file,line,ptr->size,ptr->ptr,g_total_malloc);
    if(ptr==g_total_head){
        // head ptr_info node
        if(g_total_head->next==NULL){
            free(g_total_head);
            g_total_head = NULL;
        }else{
            ptr_info* second_node = g_total_head->next;
            second_node->prev = NULL;
            free(g_total_head);
            g_total_head = second_node;
        }
    }else{
        // not head node
        if(ptr->next==NULL){
            // last one
            ptr->prev->next = NULL;
            free(ptr);
        }else{
            // middle one
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            free(ptr);
        }
    }
}