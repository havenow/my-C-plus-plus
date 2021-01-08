
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

class Derive : public Base
{
	
};

int main()
{
	Base a;
	Derive d;
	return 0;
}