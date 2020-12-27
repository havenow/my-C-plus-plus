
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

int main()
{
	Base a;
	return 0;
}