#include "stdafx.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib>//abort()
#include <cstdio>//snprintf()
#include <iostream>
#include <ctime>
#include <algorithm>//sort()

using namespace std;
const long ASIZE  =   1000000L;

string get_a_target_string()
{
	long target = 0;
	char buf[10];
	cout << "target (0~" << RAND_MAX << "):";
	cin >> target;
	sprintf(buf, "%d", target);
	return string(buf);
}

int compareStrings(const void* a, const void* b)
{
	if (*(string*)a > *(string*)b)
		return 1;
	else if (*(string*)a < *(string*)b)
		return -1;
	else
		return 0;
}

namespace jj02
{
	void test_vector()
	{
		cout << "\ntest_vector().......... \n";

	vector<string> c;  	
	char buf[10];

	clock_t timeStart = clock();									
		for(long i=0; i< ASIZE; ++i) {
			try
			{
				sprintf(buf, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock()-timeStart) << endl;	//
		cout << "array.size()= " << c.size() << endl;		
		cout << "array.front()= " << c.front() << endl;	
		cout << "array.back()= " << c.back() << endl;	
		cout << "array.data()= " << c.data() << endl;
		cout << "vector.capacity()= " << c.capacity() << endl;

	string target = get_a_target_string();
		{
		timeStart = clock();
	auto pItem = ::find(c.begin(), c.end(), target);
		cout << "::find(), milli-seconds : " << (clock()-timeStart) << endl;
		if (pItem != c.end())
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;
		}

		{
		timeStart = clock();
		sort(c.begin(), c.end());
	string* pItem = (string*)::bsearch(&target, (c.data()), ASIZE, sizeof(string), compareStrings); 
		cout << "sort()+bsearch(), milli-seconds : " << (clock()-timeStart) << endl;	//    
		if (pItem != NULL)
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;	
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	jj02::test_vector();		
	return 0;
}

