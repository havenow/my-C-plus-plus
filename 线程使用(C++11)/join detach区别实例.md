#
```
void* threadHookBlenchBvnProc(void* param)
{
	//搜索地址的base值,找到地址线程就结束
	while(!g_findAddrBase)
	{
		_timeStampHook.update();
		updateAddr_safe();
		if (_timeStampHook.getElapsedSecond() < 0.25)
			usleep(250000); 
	}
	return NULL;
}

EXPORT_FUNC void on_shared_so_load(std::string soName, void* handle)
{
	if (soName.find("com.qiya.babycard.ssvs") != string::npos && soName.find("libCore.so") != string::npos)
	{
		hook_thread = std::thread(threadHookBlenchBvnProc, nullptr);
		hook_thread.detach();
/*
这里应该用detach
如果用join，由于threadHookBlenchBvnProc是搜索到地址才会结束线程（没有使用类似condition_variable wait()来将线程block, allowing other locked threads to continue.）
所以后面的g_on_shared_so_load_Sucess = true，在地址没搜索到之前是不会执行到的，导致后面的doCheat函数会一直return
在virtualApp里面，游戏是直接卡住的
*/
		
		g_on_shared_so_load_Sucess = true;
	}
}

EXPORT_FUNC void doCheat(int arg0, int arg1, int arg2)
{
	if (!g_on_shared_so_load_Sucess)
	{
		return;
	}
	process_cheat(arg0, arg1);
}
```