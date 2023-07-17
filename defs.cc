#include "defs.h"

#include <stdlib.h>
void* operator new(size_t objsize) { 
    return malloc(objsize); 
} 

void operator delete(void* obj) { 
    free(obj); 
}