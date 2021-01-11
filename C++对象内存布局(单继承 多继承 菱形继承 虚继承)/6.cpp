
class BaseA
{
public:
	BaseA() = default;
	virtual ~BaseA() = default;
	void FuncA() {}
	virtual void FuncB(){}
	int a;
	int b;
};

class BaseB
{
public:
	BaseB() = default;
	virtual ~BaseB() = default;
	void FuncA() {}
	virtual void FuncC(){}
	int a;
	int b;
};

class Derive : public BaseA, public BaseB
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