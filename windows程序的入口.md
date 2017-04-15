- # 用vs2010新建默认的程序
- 新建win32控制台程序，可以看到项目的属性 C/C++-->预处理器-->预处理器定义 中有一个_CONSOLE的宏，代码中程序的入口是_tmain()函数。  
- 新建win32程序，可以看到项目的属性 C/C++-->预处理器-->预处理器定义 中有一个_WINDOWS的宏，代码中程序的入口是_tWinMain()函数。  

如果上述宏，和入口函数不对应，编译器会报错：    
***error LNK2019: 无法解析的外部符号 _wWinMain@16，该符号在函数 ___tmainCRTStartup 中被引用***    
- 错误原因可能是：_WINDOWS的宏，但是入口是_tmain()。   
- 错误原因可能是：没有写_tWinMain()  

- # 查看crt0.c的_tmainCRTStartup函数
```c++
//Windows程序的入口函数：_tmainCRTStartup（vs2013即以下的IDE）
/************************************************************************/
//C:\Program Files\Microsoft Visual Studio 10.0\VC\crt\src\crt0.c
/*       Function:               User entry called:
*       mainCRTStartup          main
*       wmainCRTStartup         wmain
*       WinMainCRTStartup       WinMain
*       wWinMainCRTStartup      wWinMain                                                               

      */
/************************************************************************/

__declspec(noinline)
int
__tmainCRTStartup(
         void
         )
{

#ifdef _WINMAIN_

            lpszCommandLine = _twincmdln();
            mainret = _tWinMain( (HINSTANCE)&__ImageBase,
                                 NULL,
                                 lpszCommandLine,
                                 StartupInfo.dwFlags & STARTF_USESHOWWINDOW
                                      ? StartupInfo.wShowWindow
                                      : SW_SHOWDEFAULT
                                );
#else
            _tinitenv = _tenviron;
            mainret = _tmain(__argc, _targv, _tenviron);
#endif 

        .. ...
}
```
可以看到根据不同的宏类型，调用_tmain或者_tWinMain。

- # 项目属性-->链接器-->高级-->入口点   
如果项目属性设置去掉_CONSOLE或者_WINDOWS的宏，在项目属性-->链接器-->高级-->入口点手动设置程序的入口即可。    
- 如果是UINCODE的工程，设置为：		  
       wmainCRTStartup         (win32控制台程序的入口设置)         
       wWinMainCRTStartup      (win32程序的入口设置)         
- 如果是多字节的工程，设置为：		        
       mainCRTStartup         (win32控制台程序的入口设置)          
       WinMainCRTStartup      (win32程序的入口设置)     
       
- # 入口函数
```c++
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
```
```c++
#include <Windows.h>
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	return 0;
}
```
