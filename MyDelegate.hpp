#pragma once
#include <assert.h>
#include <new>          // For placement new
namespace   CRAZY
{
    /**
    *   构件该类的目的是不需要再次的使用堆内存
    *   高效率，弱点：占用更多的内存
    */

	template<typename ReturnType, typename ... ParamType>
	class IDelegate
	{
	public:
		virtual ReturnType invoke(ParamType ... params) = 0;
	};

	//类成员函数
	template<typename T, typename ReturnType, typename ... ParamType>
	class IDelegateImp : public IDelegate<ReturnType, ParamType ...>
	{
	public:
		typedef ReturnType(T::*Method)(ParamType ...);

		IDelegateImp(T* object, Method method) : m_pObject(object), m_pMethod(method){}
		virtual ReturnType invoke(ParamType ... params)
		{
			return (m_pObject->*m_pMethod)(params ...);
		}

	private:
		T*		m_pObject;
		Method	m_pMethod;
	};

	//全局函数
	template<typename ReturnType, typename ... ParamType>
	class IDelegateImpStatic : public IDelegate<ReturnType, ParamType ...>
	{
	public:
		typedef ReturnType(*Method)(ParamType ...);

		IDelegateImpStatic(Method method) : m_pMethod(method) {};
		virtual ReturnType invoke(ParamType ... params)
		{
			return m_pMethod(params ...);
		}
	private:
		Method	m_pMethod;
	};

	template<typename ReturnType, typename ... ParamType>
	class Delegate
	{
	public:
		Delegate()
		{
			memset(this, 0, sizeof(Delegate));
		}
		Delegate(const Delegate& right)
		{
			memcpy(m_realObject, right.m_realObject, sizeof(m_realObject));
			if (right.m_delegate)
			{
				m_delegate = (IDelegate<ReturnType, ParamType ...>*)(m_realObject);
			}
			else
			{
				m_delegate = 0;
			}
		}
		Delegate&  operator = (const Delegate& right)
		{
			memcpy(m_realObject, right.m_realObject, sizeof(m_realObject));
			if (right.m_delegate)
			{
				m_delegate = (IDelegate<ReturnType, ParamType ...>*)(m_realObject);
			}
			return  *this;
		}

		//通过参数设置代理函数
		template<typename T>
		void    bind(T* object, ReturnType(T::*method)(ParamType ...))
		{
			if (object != 0 && method != 0)
			{
				//在给定的内存上进行构造，而不是使用堆内存
				assert(sizeof(IDelegateImp<T, ReturnType, ParamType ...>(object, method)) <= sizeof(m_realObject));
				m_delegate = new(m_realObject) IDelegateImp<T, ReturnType, ParamType ...>(object, method);
			}
			else
			{
				m_delegate = 0;
			}
		}
	
		//通过参数设置代理函数
		void    bind(ReturnType(*method)(ParamType ...))
		{
			if (method != 0)
			{
				//在给定的内存上进行构造，而不是使用堆内存
				m_delegate = new(m_realObject) IDelegateImpStatic<ReturnType, ParamType ...>(method);
			}
			else
			{
				m_delegate = 0;
			}
		}

		//调用代理函数
		ReturnType operator()(ParamType ... params)
		{
			if (m_delegate)
			{
				return  m_delegate->invoke(params ...);
			}
			else
			{
				return  ReturnType(0);
			}

		}

	private:
		IDelegate<ReturnType, ParamType ...>*		m_delegate;
		char										m_realObject[48];//placement operator new: inline void *__CRTDECL operator new(size_t, void *_Where) _THROW0()
	};
}
