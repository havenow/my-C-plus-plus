#ifndef _CELLTimestamp_hpp_
#define _CELLTimestamp_hpp_

#include <chrono>
//using namespace std::chrono;

class CELLTimestamp
{
public:
	CELLTimestamp()
	{
		update();
	}

	~CELLTimestamp()
	{
	}

	void update()
	{
		_begin = std::chrono::high_resolution_clock::now();
	}

	/************************************************************************/
	/* 获取当前秒                                                           */
	/************************************************************************/
	double getElapsedSecond()
	{
		return getElapsedTimeInMicroSec() * 0.000001;
	}

	/************************************************************************/
	/* 获取毫秒                                                           */
	/************************************************************************/
	double getElapsedTimeInMilliSec()
	{
		return this->getElapsedTimeInMicroSec() * 0.001;
	}

	/************************************************************************/
	/* 获取微秒                                                           */
	/************************************************************************/
	long long getElapsedTimeInMicroSec()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _begin).count();
	}

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> _begin;
};

#endif