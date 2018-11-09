// MemPool.cpp : 定义控制台应用程序的入口点。
//

/*
#include "stdafx.h"
#include "Alloctor.h"
#include <stdlib.h>

int main()
{
	
	//char* data1 = new char[128];
	//delete[] data1;

	//char* data2 = new char;
	//delete data2;

	//char* data3 = new char[64];
	//delete[] data3;
	

	
	//char* data[12];
	//for (size_t i = 0; i < 12; i++)
	//{
	//	data[i] = new char[60];
	//}
	//for (size_t i = 0; i < 12; i++)
	//{
	//	delete[] data[i];
	//}
	

	char* data[1100];
	for (size_t i = 0; i < 1100; i++)
	{
		data[i] = new char[1 + i];
	}
	for (size_t i = 0; i < 1100; i++)
	{
		delete[] data[i];
	}

    return 0;
}

*/

#include "stdafx.h"
#include "CELLTimestamp.hpp"
#include "Alloctor.h"

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
const int tCount = 1;
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

	//for (int n = 0; n < nCount; n++)
	//{
	//	//自解锁
	//	//std::lock_guard<std::mutex> lg(m);
	//	//m.lock();
	//	
	//	//m.unlock();
	//}
}

int main()
{
	std::thread t[tCount];
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
	std::cout << "Hello, main thread." << std::endl;
	return 0;
}