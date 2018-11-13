#include "Alloctor.h"
#include <stdlib.h>
#include "MemoryMgr.hpp"

void* operator new(size_t const size)
{
	return MemoryMgr::Instance().allocMem(size);
	//return malloc(size);
}

void* operator new[](size_t const size)
{
	return MemoryMgr::Instance().allocMem(size);
	//return malloc(size);
}

void operator delete(void* block)
{
	MemoryMgr::Instance().freeMem(block);
	//free(block);
}

void operator delete[](void* block)
{
	MemoryMgr::Instance().freeMem(block);
	//free(block);
}

void* mem_alloc(size_t const size)
{
	return malloc(size);
}

void mem_free(void* block)
{
	free(block);
}