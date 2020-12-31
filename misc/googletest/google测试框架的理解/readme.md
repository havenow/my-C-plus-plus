# ʵ�ֵ�����ϢLOG��־��ӡ
```
#include <stdio.h>

#define LOG(frm, args...) {\
	printf("\033[0;33m[%s : %s : %d] \033[0m", __FILE__, __func__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}


ע�� ��
## �����ӷ�
##args����д����printf("msg");����������ܹ�����
```

# ʵ��EXPECTϵ�з�װ
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


ע�⣺
__typeof(a) __a = a
����һ���ͱ���a������ͬ����ʱ����__a
���磺EXPECT_GT(add(3, 4), 9); չ����Ĵ�����
{ 
	__typeof(add(3, 4)) __a = add(3, 4), __b = 9; 
	if(!((__a) > (__b))){ 
	printf("\033[0;1;" "31" "m" "  %s:%d: Failure\n" "\033[0m", "main.cpp", 21); 
	printf("\033[0;1;" "33" "m" "    EXPECTED: (%s) %s (%s), actual: %d vs %d\n" "\033[0m", "add(3, 4)", ">", "9", __a, __b); 
	} 
};
�����
main.cpp:21: Failure
    EXPECTED: (add(3, 4)) > (9), actual: 7 vs 9
```

# ʵ��COLORϵ�з�װ
```
#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m"
#define RED(msg)	COLOR(msg, 31)
#define GREEN(msg)	COLOR(msg, 32)
#define YELLOW(msg)	COLOR(msg, 33)
#define BLUE(msg)	COLOR(msg, 34)
```

# ʹ��__attribute__��ɺ���ע��
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

__attribute__((constructor)) ���εĺ���������main����ִ��
```

# ���Կ��