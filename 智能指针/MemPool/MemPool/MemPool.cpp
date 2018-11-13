#include "stdafx.h"
#include "CELLTimestamp.hpp"
#include "Alloctor.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

std::mutex m;
const int tCount = 8;
const int mCount = 100000;
const int nCount = mCount / tCount;

void workFun(int index)
{

	char* data[nCount];
	for (size_t i = 0; i < nCount; i++)
	{
		data[i] = new char[(rand() % 128) +1];
	}
	for (size_t i = 0; i < nCount; i++)
	{
		delete[] data[i];
	}
}


class ClassA
{
public:
	ClassA(int n)
	{
		num = n;
		printf("ClassA\n");
	}
	~ClassA()
	{
		printf("~ClassA\n");
	}

	int num = 0;
private:
	
};

ClassA& fun(ClassA& pA)
{
	pA.num++;
	return pA;
}

/*std::shared_ptr<ClassA>&*/void fun(std::shared_ptr<ClassA>& pA)
{
	pA->num++;
	//return pA;
}

/*ClassA**/void fun(ClassA* pA)
{
	pA->num++;
	//return pA;
}

int main()
{
	/*std::thread t[tCount];
	for (int n = 0; n < tCount; n++)
	{
		t[n] = std::thread(workFun, n);
	}
	CELLTimestamp cTime;
	for (int n = 0; n < tCount; n++)
	{
		//t[n].detach();
		t[n].join();
	}

	std::cout << cTime.getElapsedTimeInMilliSec() << std::endl;
	std::cout << "Hello, main thread." << std::endl;*/

	
	/*int* a = new int;
	*a = 10;
	printf("a %d\n", *a);
	delete a;

	//C++标准库智能指针的一种
	std::shared_ptr<int> b = std::make_shared<int>();
	*b = 100;
	printf("b %d\n", *b);

	ClassA* c = new ClassA;
	c->num = 20;
	delete c;

	{
		ClassA e;
		e.num = 200;
	}*/

	/*{
		ClassA d(100);
		d.num = 200;
		CELLTimestamp tTime;
		for (int n = 0; n < 100000000; n++)
		{
			ClassA& e = fun(d);
		}
		std::cout << tTime.getElapsedTimeInMilliSec() << std::endl;//时间为0，被编译器优化掉了？
	}*/

	{
		std::shared_ptr<ClassA> d = std::make_shared<ClassA>(100);
		d->num = 200;
		CELLTimestamp tTime;
		for (int n = 0; n < 100000000; n++)
		{
			/*std::shared_ptr<ClassA> e =*/ fun(d);
		}
		std::cout << tTime.getElapsedTimeInMilliSec() << std::endl;

		/*std::shared_ptr<ClassA> e =  fun(d);
		printf("3 use_count=%d\n", d.use_count());
		printf("%d\n", d->num);*/
	}

	{
		ClassA* b = new ClassA(100);
		b->num = 200;
		CELLTimestamp tTime;
		for (int n = 0; n < 100000000; n++)
		{
			/*ClassA* c =*/ fun(b);
		}
		std::cout << tTime.getElapsedTimeInMilliSec() << std::endl;
		//delete b;
	}


	return 0;
}