#pragma once

#define  DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&) = delete;	\
	TypeName& operator= (const TypeName&) = delete

//------------------------------------------------------------------------------------------
//ʹ��static obj�ķ�ʽ��������֤�̰߳�ȫ
class CGlobal
{
public:
	static CGlobal* Instance()
	{
		static CGlobal obj;//vs2015 static�Ķ������̰߳�ȫ��
		//��thread_safe_statics.cpp�м����ˣ�����ʵ�ֵ���Ч�ʻ᲻�������⣿����
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
�ٶ�C++����淶��
 �����ܱ���ʹ��ȫ�ֱ��������б�Ҫʹ�õ���ģʽ����
 ��ֹʹ��class���͵ľ�̬��ȫ�ֱ���
1��ȫ�ֱ��������д��붼��������ϣ��������ǳ��Ѹ��١���˸þ����ܱ��⡣
2����̬�����Ĺ��캯�������������Լ���ʼ�������ĵ���˳����C++��׼��δ��ȷ���壬
����ÿ�α��빹�������ܻᷢ���仯���Ӷ��������Է��ֵ�bug�����磺��������ʱ��ĳ����̬�����Ѿ��������ˣ�
�����뻹���ܣ���ʱ�����̺߳ܿ��ܻ�����ͼ���ʸñ�����ֱ�ӵ��±�����

���ֵ�����д�������⣿����
*/

//------------------------------------------------------------------------------------------
//ʹ��������֤�̰߳�ȫ����new�ķ�ʽ����
std::mutex resMutex;
class CGlobal_v2
{
public:
	static CGlobal_v2* Instance()
	{
		if (_pInstance == nullptr)//����Ч�ʣ�����ÿ�ε���Instanceʱ�ͼ���
		{
			std::unique_lock<std::mutex> instanceMutex(resMutex);//��֤�������̰߳�ȫ��
			if (_pInstance == nullptr)
			{
				_pInstance = new CGlobal_v2();
				static CCG cg;
			}
		}
		return _pInstance;
	}

	class CCG {//����Ƕ���࣬�����ͷŶ���
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
//ʹ��call_once����֤�̰߳�ȫ����new�ķ�ʽ����
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
		std::call_once(_flag, createInstance);//���߳�ʱ��createInstanceֻ��ִ��һ��
		//�������Ĺ��ܣ�Ч�ʻ᲻�᲻�ߣ�����
		return _pInstanceV3;
	}

	class CCG {//����Ƕ���࣬�����ͷŶ���
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