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

# ʹ��__attribute__��ɺ���ע��

# ���Կ��