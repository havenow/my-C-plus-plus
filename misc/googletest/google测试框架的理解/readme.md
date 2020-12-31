# 实现调试信息LOG日志打印
```
#include <stdio.h>

#define LOG(frm, args...) {\
	printf("\033[0;33m[%s : %s : %d] \033[0m", __FILE__, __func__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}
```

# 实现EXPECT系列封装

# 实现COLOR系列封装

# 使用__attribute__完成函数注册

# 测试框架