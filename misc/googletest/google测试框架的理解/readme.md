# 实现调试信息LOG日志打印
```
#include <stdio.h>

#define LOG(frm, args...) {\
	printf("\033[0;33m[%s : %s : %d] \033[0m", __FILE__, __func__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}


注意 ：
## 是连接符
##args这种写法，printf("msg");这种输出才能过编译

\033[A1;A2;A3;...An m 
\033[开头 m结尾 A1;A2;A3;...An是配色内容
配色内容有一个规范：以0开头，以0m结束，这样可以重置之前的信息
```

# 实现EXPECT系列封装
```
#define EXPECT(a, comp, b) {	\
	__typeof(a) __a = a, __b = b;\
	if(!((__a) comp (__b))){	\
		printf(RED("  %s:%d: Failure\n"), __FILE__, __LINE__);\
		printf(YELLOW("    EXPECTED: (%s) %s (%s), actual: %d vs %d\n"), \
			#a, #comp, #b, __a, __b);\
	}	\
}	\

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)


注意：
__typeof(a) __a = a
定义一个和变量a类型相同的临时变量__a
例如：EXPECT_GT(add(3, 4), 9); 展开后的代码是
{ 
	__typeof(add(3, 4)) __a = add(3, 4), __b = 9; 
	if(!((__a) > (__b))){ 
	printf("\033[0;1;" "31" "m" "  %s:%d: Failure\n" "\033[0m", "main.cpp", 21); 
	printf("\033[0;1;" "33" "m" "    EXPECTED: (%s) %s (%s), actual: %d vs %d\n" "\033[0m", "add(3, 4)", ">", "9", __a, __b); 
	} 
};
输出：
main.cpp:21: Failure
    EXPECTED: (add(3, 4)) > (9), actual: 7 vs 9
```

# 实现COLOR系列封装
```
#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m"
#define RED(msg)	COLOR(msg, 31)
#define GREEN(msg)	COLOR(msg, 32)
#define YELLOW(msg)	COLOR(msg, 33)
#define BLUE(msg)	COLOR(msg, 34)
```

# 使用__attribute__完成函数注册
```
#define TEST(a, b)	\
void gTest_##a##_##b();	\
__attribute__((constructor)) 	\
void reg_##a##_##b(){	\
	add_test_func(gTest_##a##_##b, #a "." #b);	\
}	\
void gTest_##a##_##b()	\

struct{
	void(*func)();
	const char* func_name;
} func_arr[100];
int func_cnt = 0;

void add_test_func(void(*func)(), const char* str){
	func_arr[func_cnt].func = func;
	func_arr[func_cnt].func_name = str;
	func_cnt++;
	return;
}

int RUN_ALL_TESTS(){
	for(int i = 0; i < func_cnt; i++) {
		printf(GREEN("[  Run  ]") " %s\n", func_arr[i].func_name);
		func_arr[i].func();
	}
	return 0;
}

__attribute__((constructor)) 修饰的函数会先于main函数执行
```

# 测试框架
```
int add(int a, int b){
	return a + b;
}

TEST(test, add1) {
	EXPECT_EQ(add(3, 4), 7);//==
	EXPECT_NE(add(3, 4), 9);//!=
	EXPECT_LT(add(3, 4), 8);//<
	EXPECT_LE(add(3, 4), 7);//<=
	EXPECT_GT(add(3, 4), 6);//>
	EXPECT_GE(add(3, 4), 7);//>=
}

TEST(test, add2) {
	EXPECT_EQ(add(3, 4), 7);//==
	EXPECT_NE(add(3, 4), 9);//!=
	EXPECT_LT(add(3, 4), 8);//<
	EXPECT_LE(add(3, 4), 7);//<=
	EXPECT_GT(add(3, 4), 9);//error >
	EXPECT_GE(add(3, 4), 7);//>=
}

int main()
{
	return RUN_ALL_TESTS();
}

输出结果：
[  Run  ] test.add1
[  Run  ] test.add2
  main.cpp:21: Failure
    EXPECTED: (add(3, 4)) > (9), actual: 7 vs 9

```

```
对TEST的展开
便于观察，做下面的修改
#define EXPECT(a, comp, b) {	\
	if(!((a) comp (b))){	\
		printf("error\n");	\
	}\
}\
g++ -E main.cpp > m.cpp，获取预处理后的文件，
打开m.cpp后，可以看到
int add(int a, int b){
 return a + b;
}

void gTest_test_add1(); //函数申明
__attribute__((constructor)) 
void reg_test_add1(){ add_test_func(gTest_test_add1, "test" "." "add1"); } //注册测试函数
void gTest_test_add1() {//测试函数主体
 { if(!((add(3, 4)) == (7))){ printf("error\n"); }};
 { if(!((add(3, 4)) != (9))){ printf("error\n"); }};
 { if(!((add(3, 4)) < (8))){ printf("error\n"); }};
 { if(!((add(3, 4)) <= (7))){ printf("error\n"); }};
 { if(!((add(3, 4)) > (6))){ printf("error\n"); }};
 { if(!((add(3, 4)) >= (7))){ printf("error\n"); }};
}

void gTest_test_add2(); __attribute__((constructor)) void reg_test_add2(){ add_test_func(gTest_test_add2, "test" "." "add2"); } void gTest_test_add2() {
 { if(!((add(3, 4)) == (7))){ printf("error\n"); }};
 { if(!((add(3, 4)) != (9))){ printf("error\n"); }};
 { if(!((add(3, 4)) < (8))){ printf("error\n"); }};
 { if(!((add(3, 4)) <= (7))){ printf("error\n"); }};
 { if(!((add(3, 4)) > (9))){ printf("error\n"); }};
 { if(!((add(3, 4)) >= (7))){ printf("error\n"); }};
}
```