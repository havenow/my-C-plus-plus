#visual studio
```
1、打开vs 开发人员命令(Visual Studio Command Prompt)，使用cl命令
cl ex.cpp /d1 reportSingleClassLayoutBaseAA /EHsc
2、右键所要显示的*.cpp >> 属性 >> 命令行 >> 其它选项
在其他选项中添加：
/d1 reportSingleClassLayoutXXX  (XXX指的是要显示的类)
如果是在vs里面，直接编译的时候就会输出内存布局（不需要链接）
使用reportAllClassLayout会输出很多信息，用处不大


如果是单独的写一个源文件来查看布局，有下面注意的（使用的是VS2015的Command Prompt）：
只写类，不写main函数，以输出对象布局和虚函数布局，但是会提示LINK : fatal error LNK1561: 必须定义入口点；只用写一个main函数体，return 0;
不声明对象，也可以输出对象布局和虚函数布局
在使用reportSingleClassLayout时，查找的方式是包含串就输出，Base和BaseV，如果搜索Base，两个类的布局都会输出
```

#gcc
```
g++ -fdump-class-hierarchy mode.cc
```

#clang
```
查看对象布局
clang -Xclang -fdump-record-layouts -stdlib=libc++ -std=c++11 -c ex.cpp
查看虚函数表布局
clang -Xclang -fdump-vtable-layouts -stdlib=libc++ -std=c++11 -c ex.cpp

没找到如何只输出一个类，上面的命令输出所有类的布局
可以没有main函数，但是需要定义一个类的对象才会输出对象布局和虚函数布局
-std=c++11 可以避免有-Wc++11-extensions的警告
```