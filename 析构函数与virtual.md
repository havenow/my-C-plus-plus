- # 问题  
一次面试时，问道的问题：析构函数前面的virtual，是不是一定需要？什么时候必须要？     

- # 结论 
只要能够保证继承关系中最高的基类的析构函数是虚的，那么就不会产生delete pC所发生的问题。     
这就是为什么在想使用多态特性的时候，需要将基类的析构函数设成虚的真正原因。       

```c++
	class A 
	{
	public:
		A() {};
		~A() { printf("~A()\n"); };
	};
	class B 
	{
	public:
		B() {};
		virtual ~B() { printf("virtual ~B()\n"); };
	};
	class C : public A
	{
	public:
		C() {};
		virtual ~C() { printf("virtual ~C()\n"); };
	};
	class D : public B
	{
	public:
		D() {};
		virtual ~D() { printf("~D()\n"); };
	};
	class E : public B
	{
	public:
		E() {};
		~E() { printf("~E()\n"); };
	};
	class F : public E
	{
	public:
		F() {};
		~F() { printf("~F()\n"); };
	};
  
  		A* pA = new A();
			B* pB = new B();
			delete pA;
			delete pB;

			//A* pC = new C();
			//delete pC;//类A的析构函数不是虚函数，delete pC时，vs会报异常
			B* pD = new D();
			delete pD;

			B* pE = new E();
			delete pE;
			B* pF = new F();
			delete pF;//类B中的析构函数设成虚的，E F类中的析构函数前面的virtual关键字不管是否存在，其析构函数也一定是虚的
```
