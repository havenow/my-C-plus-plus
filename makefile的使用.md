- # 使用makefile
以下操作在mac上完成  
```c++
//hello.c
#include <stdio.h>

int main(int argc, char** argv)
{
        printf("hello\n");
        return 0;
}

//执行命令
gcc -o hello hello.c  
./hello 
//在命令行打印出了hello
```

```makefile
//写一个makefile文件
hello:hello.c
        gcc -o hello hello.c
clean:
        rm hello

//在命令行打印出了hello
//执行命令
make
./hello
//在命令行打印出了hello
```

```makefile
//有中间文件的makefile文件
hello:hello.o
        gcc -o hello hello.o
hello.o:hello.c
        gcc -o hello.o -c hello.c #-c表示只编译不链接
clean:
        rm hello hello.o
```

- # 程序文件的分类  
- bin文件  
纯粹的代码，一般用在裸机上，比如单片机上，编译代码，烧到单片机上，可以直接运行   

- elf文件  
(一般运行在linux操作系统上，elf文件时有头部信息的)  
可执行文件(比如 hello)   
可重定位文件(比如 hello.o)  
库文件(目标文件的归档，静态库 动态库) 

`readelf -h hello`  
可以看到有一个entry point address  0x8048310(mac上没有readelf命令？)

`readelf -h hello.o`
可以看到entry point address  0x0  
只有这些可重定位文件组装成可执行文件后这个地址才不是0  

```
file hello
file hello.o
```
可以查看文件的类型
```
hello: elf 32-bit lsb executable,…
hello.o: elf 32-bit lsb relocatable,…
```

- # makefile文件的主要内容  
规则  
变量  
条件执行  
文本、文件名处理函数  
文件包含  
注释   

makefile的目的是构建依赖关系树，依赖关系树的生命周期  
- 解析阶段载入内存  
- 运行阶段根据其进行编译、根据时间戳生成文件  
- 有新文件添加、减少会动态改变依赖关系树  

