#ifndef __COMPLEX__
#define __COMPLEX__

//前置声明----------------------------------------------------------
class Complex;

Complex& __doapl(Complex* ths, const Complex& r);

//类声明------------------------------------------------------------
class Complex
{
public:
	Complex(double r=0, double i=0)
		: re(r), im(i)//初值列
	{
	}

	inline double getReal() const {return re;}//inline，函数const
	inline double getImag() const {return im;}

	Complex& operator += (const Complex& r);//返回为引用-->支持连加操作
	
private:
	double re;
	double im;

	friend Complex& __doapl(Complex* ths, const Complex& r);//friends-->对象就可以直接取私有的成员变量

};


//类定义------------------------------------------------------------
inline Complex& 
Complex::operator +=(const Complex& r)
{
	return __doapl(this,  r);
}

//------------------------------------------------------------------------------------
//下面是全局函数
inline Complex&
__doapl(Complex* ths, const Complex& r)//此函数为Complex的friends，所以对象可以直接取私有数据
{
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

//加 运算符
inline Complex 
operator + (const Complex& x, const Complex& y)
{
	return Complex(x.getReal() + y.getReal(), x.getImag() + y.getImag());
}

//取正 运算符
inline Complex
operator + (const Complex& x)
{
	return x;
}

//取负 运算符
inline Complex
operator - (const Complex& x)
{
	return Complex(-x.getReal(), -x.getImag());
}

//相等 运算符
inline bool
operator == (const Complex x, const Complex y)
{
	if (x.getReal() == y.getReal() && x.getImag() == y.getImag())
		return true;
	else
		return false;
}

//不相等 运算符
inline bool
operator != (const Complex x, const Complex y)
{
	if (x.getReal() != y.getReal() || x.getImag() != y.getImag())
		return true;
	else
		return false;
}

//<< 运算符
#include <IOSTREAM.H>
inline ostream&//没有返回void，是考虑到cout << c1 << conj(c1);这种用法；不能加const
operator << (ostream& os, Complex& r)//此处第一个参数不能加const
{
	return cout << '(' << r.getReal() << ',' << r.getImag() << ')' << endl;
}


#endif