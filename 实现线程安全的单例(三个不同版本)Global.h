#pragma once

#define  DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&) = delete;	\
	TypeName& operator= (const TypeName&) = delete

//------------------------------------------------------------------------------------------
//使用static obj的方式创建，保证线程安全
class CGlobal
{
public:
	static CGlobal* Instance()
	{
		static CGlobal obj;//vs2015 static的对象是线程安全的
		//看thread_safe_statics.cpp中加锁了，这样实现单例效率会不会有问题？？？
		return &obj;
	}
	void test()
	{
		printf("just for test\n");
	}
protected:
	CGlobal() {};
	~CGlobal() {};

private:
	DISALLOW_COPY_AND_ASSIGN(CGlobal);
};
/*
百度C++编码规范：
 尽可能避免使用全局变量，如有必要使用单例模式代替
 禁止使用class类型的静态或全局变量
1、全局变量跟所有代码都发生了耦合，如果出错非常难跟踪。因此该尽可能避免。
2、静态变量的构造函数，析构函数以及初始化操作的调用顺序在C++标准中未明确定义，
甚至每次编译构建都可能会发生变化，从而导致难以发现的bug。比如：结束程序时，某个静态变量已经被析构了，
但代码还在跑，此时其他线程很可能还在试图访问该变量，直接导致崩溃。

这种单例的写法有问题？？？
*/

//------------------------------------------------------------------------------------------
//使用锁来保证线程安全，用new的方式创建
std::mutex resMutex;
class CGlobal_v2
{
public:
	static CGlobal_v2* Instance()
	{
		if (_pInstance == nullptr)//提升效率，不用每次调用Instance时就加锁
		{
			std::unique_lock<std::mutex> instanceMutex(resMutex);//保证单例是线程安全的
			if (_pInstance == nullptr)
			{
				_pInstance = new CGlobal_v2();
				static CCG cg;
			}
		}
		return _pInstance;
	}

	class CCG {//类中嵌套类，用来释放对象
	public:
		~CCG()
		{
			if (CGlobal_v2::_pInstance)
			{
				delete CGlobal_v2::_pInstance;
				CGlobal_v2::_pInstance = nullptr;
			}
		}
	};

	void test()
	{
		printf("just for test\n");
	}
protected:
	CGlobal_v2() {};
	~CGlobal_v2() {};

private:
	DISALLOW_COPY_AND_ASSIGN(CGlobal_v2);
	static CGlobal_v2* _pInstance;
};

CGlobal_v2* _pInstance = nullptr;

//------------------------------------------------------------------------------------------
//使用call_once来保证线程安全，用new的方式创建
std::once_flag _flag;
class CGlobal_v3
{
public:
	static void createInstance()
	{
		_pInstanceV3 = new CGlobal_v3();
		static CCG cg;
	}

	static CGlobal_v3* Instance()
	{
		std::call_once(_flag, createInstance);//多线程时，createInstance只会执行一次
		//类似锁的功能，效率会不会不高？？？
		return _pInstanceV3;
	}

	class CCG {//类中嵌套类，用来释放对象
	public:
		~CCG()
		{
			if (CGlobal_v3::_pInstanceV3)
			{
				delete CGlobal_v3::_pInstanceV3;
				CGlobal_v3::_pInstanceV3 = nullptr;
			}
		}
	};

	void test()
	{
		printf("just for test\n");
	}
protected:
	CGlobal_v3() {};
	~CGlobal_v3() {};

private:
	DISALLOW_COPY_AND_ASSIGN(CGlobal_v3);
	static CGlobal_v3* _pInstanceV3;
};

CGlobal_v3* _pInstanceV3 = nullptr;