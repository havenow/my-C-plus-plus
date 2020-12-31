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

# 使用__attribute__完成函数注册

# 测试框架