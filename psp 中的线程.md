#
```
tag 1.2.1
ext/natvie/thread目录下面
thread.h
这个头文件其实就是c++标准库里面的thread

#define THREAD_HANDLE HANDLE
#define THREAD_HANDLE pthread_t
typedef THREAD_HANDLE native_handle_type;
native_handle_type m_handle;

	template <typename F>
	void StartThread(F* param)
	{
#ifdef USE_BEGINTHREADEX
		m_handle = (HANDLE)_beginthreadex(NULL, 0, &RunAndDelete<F>, param, 0, &m_id.m_thread);
#elif defined(_WIN32)
		m_handle = CreateThread(NULL, 0, &RunAndDelete<F>, param, 0, &m_id.m_thread);
#else
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setstacksize(&attr, 1024 * 1024);
		if (pthread_create(&m_id.m_thread, &attr, &RunAndDelete<F>, param))
			m_id = id();
#endif
	}
	
	可以看到不同平台创建线程的具体实现
	所以使用c11里面的线程，代码就是跨平台的
```

```
代码值得一看

threadpool
prioritizedworkqueue
threadutil 封装了一个event类
executor
```

```
1.4.1之后的thread直接用了c++标准库中的
1.2.1 base/mutex.h中有event的跨平台封装
```