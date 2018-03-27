//
// Created by dengyao on 18-3-27.
//

#include <stdio.h>

//#define MEMORY_WATCH
#include "memwatch.h"

int main(){
    char* buff = (char*)MW_MALLOC(32);
    printf("here is middle\n");
    for(long i=0;i<100L;++i){
        for(long j=0;j<9999999L;++j){

        }
        char* leak = (char*)MW_MALLOC(100);
    }
    MW_FREE(buff);
    return 0;
}