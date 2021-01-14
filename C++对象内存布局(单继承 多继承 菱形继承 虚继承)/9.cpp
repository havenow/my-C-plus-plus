
class Base
{
public:
	Base() = default;
	virtual ~Base() = default;
	void FuncA() {}
	virtual void FuncB(){}
	virtual void FuncC(){}
	int a;
	int b;
};

class Derive : virtual public Base
{
public:
	void FuncB() override {}
};

int main()
{
	Base a;
	Derive d;
	return 0;
}