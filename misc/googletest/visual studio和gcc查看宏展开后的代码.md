#Vistual Studio
```
Vistual Studio 使用/P参数将TEST展开

1. 选中需要展开的代码文件，右键 - 属性 - C/C++ - Preprocessor(预处理器)
2. Generate Preprocessed File(预处理到文件) 设置：是(/P)
3. 关闭属性对话框，右键选中需要展开的文件，右键菜单中点击：Compile
编译过后，会生成一个后缀为.i的文件
```

#gcc
```
g++ -E main.cpp > m.cpp，获取预处理后的文件
```