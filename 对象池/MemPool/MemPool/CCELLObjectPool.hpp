#ifndef _CELLObjectPool_hpp_
#define _CELLObjectPool_hpp_
#include <stdlib.h>
#include <mutex>
#include <assert.h>

#ifdef _DEBUG
	#ifndef xPrintf
		#include <stdio.h>
		#define xPrintf(...) printf(__VA_ARGS__)
	#endif
#else
	#ifndef xPrintf
		#define xPrintf(...)
	#endif
#endif


template<class Type, size_t nPoolSize>
class CELLObjectPool
{
	class NodeHeader
	{
	public:
		//内存块编号
		int nID;
		//下一块位置
		NodeHeader* pNext;
		//引用次数
		char nRef;
		//是否在内存池中
		bool bPool;
	private:
		//预留
		char c1;
		char c2;
	};

public:
	CELLObjectPool()
	{
		initPool();
	}

	~CELLObjectPool()
	{
		if (_pBuf)
			delete[] _pBuf;
	}

	//释放对象内存
	void freeObjMemory(void* pMem)
	{
		NodeHeader* pBlock = (NodeHeader*)((char*)pMem - sizeof(NodeHeader));
		//xPrintf("freeObjMemory: %lx, id= %d\n", pBlock, pBlock->nID);
		assert(1 == pBlock->nRef);
		if (pBlock->bPool)
		{
			std::lock_guard<std::mutex> lg(_mutex);
			if (0 != --pBlock->nRef)
				return;
			pBlock->pNext = _pHeader;
			_pHeader = pBlock;
		}
		else
		{//不在对象池中
			if (0 != --pBlock->nRef)
				return;
			delete [] pBlock;
		}
	}

	//申请对象内存
	void* allocObjMemory(size_t nSize)
	{
		std::lock_guard<std::mutex> lg(_mutex);
		NodeHeader* pReturn = nullptr;
		if (nullptr == _pHeader)//对象池中无可用内存
		{
			pReturn = (NodeHeader*)new char[(sizeof(Type) + sizeof(NodeHeader))];
			pReturn->bPool = false;
			pReturn->nID = -1;
			pReturn->nRef = 1;
			pReturn->pNext = nullptr;
		}
		else
		{
			pReturn = _pHeader;
			_pHeader = _pHeader->pNext;
			assert(0 == pReturn->nRef);
			pReturn->nRef = 1;
		}
		xPrintf("allocObjMemory: %lx, id= %d, size= %d\n", pReturn, pReturn->nID, nSize);
		return ((char*)pReturn + sizeof(NodeHeader));
	}

private:
	//初始化对象池
	void initPool()
	{
		assert(nullptr == _pBuf);
		if (_pBuf)
			return;
		//计算对象池的大小
		size_t realSize = sizeof(Type) + sizeof(NodeHeader);
		size_t n = nPoolSize * realSize;
		//申请池的内存
		_pBuf = new char[n];//使用内存池中的
		//初始化内存池
		_pHeader = (NodeHeader*)_pBuf;
		_pHeader->bPool = true;
		_pHeader->nID = 0;
		_pHeader->nRef = 0;
		_pHeader->pNext = nullptr;

		NodeHeader* pTemp1 = _pHeader;
		for (size_t n = 1; n < nPoolSize; n++)
		{
			NodeHeader* pTemp2 = (NodeHeader*)(_pBuf + (n * realSize));
			pTemp2->bPool = true;
			pTemp2->nID = n;
			pTemp2->nRef = 0;
			pTemp2->pNext = nullptr;
			pTemp1->pNext = pTemp2;
			pTemp1 = pTemp2;
		}
	}

	//
	NodeHeader* _pHeader;
	//对象池缓存区地址
	char* _pBuf = nullptr;
	std::mutex _mutex;
};

template<class Type, size_t nPoolSize>
class ObjectPoolBase
{
public:
	ObjectPoolBase()
	{
		
	}

	~ObjectPoolBase()
	{

	}

	void* operator new(size_t const size)
	{
		return objectPool().allocObjMemory(size);
	}

	void operator delete(void* p)
	{
		objectPool().freeObjMemory(p);
	}

	template<typename ...Args>//可变参数
	static Type* createObject(Args ... args)
	{
		Type* pObj = new Type(args ...);
		//可以做点想做的事情
		return pObj;
	}

	static void deleteObject(Type* pObj)
	{
		delete pObj;
	}

private:
	typedef CELLObjectPool<Type, nPoolSize> ClassTypePool;

	static ClassTypePool& objectPool()
	{
		static ClassTypePool sPool;
		return sPool;
	}
};

#endif