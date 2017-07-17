
```c++
//创建
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif



//释放
#ifdef _DEBUG
	FreeConsole();
#endif
```
