// C11Thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CELLTimestamp.hpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex m;
const int tCount = 4;
//int sum = 0;
//std::atomic_int sum = 0;
std::atomic<int> sum = 0;

void workFun(int index)
{
	//std::cout << index << std::endl;
	for (int n = 0; n < 20000000; n++)
	{
		//自解锁
		//std::lock_guard<std::mutex> lg(m);
		//m.lock();
		sum++;
		//m.unlock();
	}
}//抢占式

int main()
{
	std::thread t[tCount];
	for (int n = 0; n < tCount; n++)
	{
		t[n] = std::thread(workFun, n);
	}
	CELLTimestamp cTime;
	for (int n = 0; n < tCount; n++)
	{
		//t[n].detach();
		t[n].join();
	}
	std::cout << cTime.getElapsedTimeInMilliSec() << ",sum=" << sum << std::endl;


	sum = 0;
	cTime.update();
	for (int n = 0; n < 80000000; n++)
	{
		sum++;
	}
	std::cout << cTime.getElapsedTimeInMilliSec() << ",sum=" << sum << std::endl;

	std::cout << "Hello, main thread." << std::endl;
    return 0;
}

// example for thread::join
/*#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

int main()
{
	std::cout << "Spawning 3 threads...\n";
	std::thread t1(pause_thread, 1);
	std::thread t2(pause_thread, 2);
	std::thread t3(pause_thread, 3);
	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads joined!\n";

	return 0;
}*/

/*#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

int main()
{
	std::cout << "Spawning and detaching 3 threads...\n";
	std::thread(pause_thread, 1).detach();
	std::thread(pause_thread, 2).detach();
	std::thread(pause_thread, 3).detach();
	std::cout << "Done spawning threads.\n";

	std::cout << "(the main thread will now pause for 5 seconds)\n";
	// give the detached threads time to finish (but not guaranteed!):
	pause_thread(5);
	return 0;
}*/


// thread::get_id / this_thread::get_id
/*#include <iostream>       // std::cout
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds

std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
	if (main_thread_id == std::this_thread::get_id())
		std::cout << "This is the main thread.\n";
	else
		std::cout << "This is not the main thread.\n";
}

int main()
{
	is_main_thread();
	std::thread th(is_main_thread);
	th.join();
}*/