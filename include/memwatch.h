//
// Created by dengyao on 18-3-27.
//

#ifndef MEMWATCH_MEMWATCH_H
#define MEMWATCH_MEMWATCH_H

#include <stdlib.h>

#ifdef MEMORY_WATCH
#define MW_MALLOC(x) mw_malloc(x,__FILE__,__LINE__)
#define MW_FREE(p) mw_free(p,__FILE__,__LINE__)
#else
#define MW_MALLOC(x) malloc(x)
#define MW_FREE(p) free(p)
#endif

void* mw_malloc(size_t num_bytes, const char* file, int line);

void mw_free(void* p, const char* file, int line);

#endif //MEMWATCH_MEMWATCH_H
