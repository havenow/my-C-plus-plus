#ifndef _GTEST_H_
#define _GTEST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m"
#define RED(msg)	COLOR(msg, 31)
#define GREEN(msg)	COLOR(msg, 32)
#define YELLOW(msg)	COLOR(msg, 33)
#define BLUE(msg)	COLOR(msg, 34)

__attribute__((constructor))
void init_rand(){
	srand(time(0));
	return;
}

int* getRandData(int n){
	int* arr = (int*)malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++){
		arr[i] = rand() % n;
	}
	return arr;
}

int check(int *arr, int n){
	for(int i = 1; i < n; i++){
		if(arr[i] < arr[i - 1])
			return 0;
	}
	return 1;
}

#define TEST(func, arr, n) __TEST(func, arr, n, #func)
void __TEST(
	void (*func)(int *, int, int),
	int *arr, int n,
	const char *func_name){

	int *temp = (int *)malloc(sizeof(int) * n);
	memcpy(temp, arr, sizeof(int) * n);
	long long b = clock();
	func(temp, 0, n - 1);
	long long e = clock();
	if(check(temp, n)){
		printf(GREEN("[  OK  ]\n"));
	} else{
		printf(RED("[  FAILED  ]\n"));
	}
	printf("%s" YELLOW("(%lldms)\n"), func_name, 1000 * (e - b) / CLOCKS_PER_SEC);
	free(temp);
	return;
}

#endif
