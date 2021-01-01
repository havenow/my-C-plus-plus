#include "gtest.h"
#include "quick_sort.h"

int main(int argc, char** argv){
	#define MAX_N 10000000
	int* arr = getRandData(MAX_N);
	TEST(quick_sort_v1, arr, MAX_N);
	free(arr);
	#undef MAX_N
	return 0;
}
