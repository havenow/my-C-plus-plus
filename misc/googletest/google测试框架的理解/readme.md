# ʵ�ֵ�����ϢLOG��־��ӡ
```
#include <stdio.h>

#define LOG(frm, args...) {\
	printf("\033[0;33m[%s : %s : %d] \033[0m", __FILE__, __func__, __LINE__);\
	printf(frm, ##args);\
	printf("\n");\
}
```

# ʵ��EXPECTϵ�з�װ

# ʵ��COLORϵ�з�װ

# ʹ��__attribute__��ɺ���ע��

# ���Կ��