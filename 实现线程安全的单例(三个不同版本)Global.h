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