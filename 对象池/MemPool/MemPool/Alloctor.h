#ifndef _Alloc_20181026_
#define _Alloc_20181026_

void* operator new(size_t const size);
void* operator new[](size_t const size);
void operator delete(void* block);
void operator delete[](void* block);

void* mem_alloc(size_t const size);
void mem_free(void* block);
#endif

