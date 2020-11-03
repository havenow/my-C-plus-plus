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
tag 1.7.0 执行cmake时会报错
需要在cmake/Toolchains/ios.cmake 35行添加
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY?"")
```

```
代码值得一看

threadpool
prioritizedworkqueue
threadutil 封装了一个event类	使用std::condition_variable，调用condition_variable的wait、wait_for和notify_one函数
executor
```

```
1.4.1之后的thread直接用了c++标准库中的
1.2.1 base/mutex.h中有event的跨平台封装
```

```
1.2.1 
1.2.2
1.3
三个版本编译官方的工程
ppsspp/ios下面readme.md有生成xcode工程的说明
mkdir build-ios
cd build-ios
cmake -DCMAKE_TOOLCHAIN_FILE=../ios/ios.toolchain.cmake -GXcode ..

cmake 进入程序的目录bin下面

注意：下面两个点是从1.4.1的工程比对出来的
错误：property with 'retain(or strong)' attribute must be of object type
1、natvie这个工程的设置
Build Settings/Deployment/IOS DeploymentTarget改成 ios6.0
Build Settings/Apple Clang - Custom Compiler Flags/Other C Flags和Other C++ Flags 添加 -mios-version-min=6.0

2、工程的配置中去掉 -march=armv7-a
Build Settings/Apple Clang - Custom Compiler Flags/Other C Flags和Other C++ Flags

3、注释掉编译不通过的汇编代码
4、thread.h内存注释掉，使用c++标准库的 #inlude <thread>
5、u32 --> (u32)(long)
6、RemoteISOScreen.h 
添加#include <thread>
注释掉
namespace std{
	class thread;
}
7、fast_math.c注释掉 fast_matrix_mul_4x4 = &fast_matrix_mul_4x4_neon(链接错误，没有将fast_math_neon.S参与编译)
fast_matrix_mul_4x4_neon是arm汇编实现的neon代码
1.4的工程是可以编译.S文件，怎么样让xCode编译汇编？？？

8、The clang compiler does not support '-mcpu=cortex-a9'
去掉-mfpu=cortex-a9
```