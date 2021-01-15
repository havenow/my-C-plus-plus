
class Base
{
public:
	Base() = default;
	virtual ~Base() = default;
	void FuncA() {}
	virtual void FuncB(){}
	int a;
	int b;
};

class BaseA : virtual public Base
{
public:
	BaseA() = default;
	virtual ~BaseA() = default;
	void FuncA() {}
	virtual void FuncB(){}
	int a;
	int b;
};

class BaseB : virtual public Base
{
public:
	BaseB() = default;
	virtual ~BaseB() = default;
	void FuncA() {}
	virtual void FuncC(){}
	int a;
	int b;
};

class Derive : public BaseB, public BaseA
{
public:
	void FuncB() override {}
	void FuncC() override {}
};

int main()
{
	BaseA a;
	Derive d;
	return 0;
}