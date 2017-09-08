初始化时调用   
```c++
//创建
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif


退出时调用   
//释放
#ifdef _DEBUG
	FreeConsole();
#endif
```
