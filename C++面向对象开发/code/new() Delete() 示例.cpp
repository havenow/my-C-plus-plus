// newDelete.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <iostream>

using namespace std;

class Bad
{
public:
	Bad(){cout << "terminate called after throwing an instance of ::Bad" << endl;}
};

class Foo
{
public:
	Foo(){cout<<"Foo::Foo()" << endl;}
	Foo(int i){cout<<"Foo::Foo(int)" << endl; throw Bad();}
	//故意在这里抛出expection，测试placement operator delete

	//1.一般的operator new()的重载
	void* operator new(size_t size){
		cout << "operator new(size_t size), size=" << size <<endl;
		return malloc(size);
	}
	//2.标准库已提供的placement new()的重载的形式，模拟standard placement new
	void* operator new(size_t size, void* start){
		cout << "operator new(size_t size, void* start), size=" << size  << " start=" << start <<endl;
		return start;
	}
	//3.这个是崭新的placement new
	void* operator new(size_t size, long extra){
		cout << "operator new(size_t size, long extra), size=" << size  << " extra=" << extra <<endl;
		return malloc(size+extra);
	}
	//4.这又是一个placement new
	void* operator new(size_t size, long extra, char init){
		cout << "operator new(size_t size, char init), size=" << size  << " char=" << init <<endl;
		return malloc(size+extra);
	}
	//5.故意写错第一个参数的type
	//error C2821: “operator new”的第一个形参必须为“size_t”
	/*void* operator new(long extra, char init){
		return malloc(extra);
	}*/

	//1.一般的operator delete()的重载
	void operator delete(void*, size_t){
		cout << "operator delete(void*, size_t)" << endl;
	}

	//2.
	void operator delete(void*, void*){
		cout << "operator delete(void*, void*)" << endl;
	}

	//3.
	void operator delete(void*, long){
		cout << "operator delete(void*, long)" << endl;
	}

	//4.
	void operator delete(void*, long, char){
		cout << "operator delete(void*, long, char)" << endl;
	}

private:
	int m_i;
};




int _tmain(int argc, _TCHAR* argv[])
{
    Foo start;
	Foo* p1 = new Foo;
	Foo* p2 = new(&start) Foo;
	Foo* p3 = new(100) Foo;
	Foo* p4 = new(100, '1') Foo;
	Foo* p5 = new(100) Foo(1);//vs2010没有调用operator delete(void*, long)

	return 0;
}

