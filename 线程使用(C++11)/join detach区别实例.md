#
```
void* threadHookBlenchBvnProc(void* param)
{
	//������ַ��baseֵ,�ҵ���ַ�߳̾ͽ���
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
����Ӧ����detach
�����join������threadHookBlenchBvnProc����������ַ�Ż�����̣߳�û��ʹ������condition_variable wait()�����߳�block, allowing other locked threads to continue.��
���Ժ����g_on_shared_so_load_Sucess = true���ڵ�ַû������֮ǰ�ǲ���ִ�е��ģ����º����doCheat������һֱreturn
��virtualApp���棬��Ϸ��ֱ�ӿ�ס��
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