#
```
编译器报错信息：
 error: undefined reference to 'vtable for CCheatGTASA'
 the vtable symbol may be undefined because the class is missing its key function
 
 代码如下：
 cheatI.h文件
 
 class CCheatI
{
public:
	CCheatI(){};
	virtual ~CCheatI(){};
	virtual void printfHelp() = 0;
	virtual void initCheatFun() = 0;
	virtual string& getFunSymByIndex(int index) = 0; 
protected:
	map<int,string> callMap;
};

class CCheatGTASA : public CCheatI
{
public:
	CCheatGTASA() {};
	virtual ~CCheatGTASA() {};
	virtual void printfHelp() {};
	virtual void initCheatFun() {};
	virtual string& getFunSymByIndex(int index) {};
};


cheatMain.cpp调用：
CCheatI* pCheat = new CCheatGTASA();

这种方式在ndk和visual stduio都可以编译通过
如果将CCheatGTASA的printfHelp initCheatFun getFunSymByIndex实现放在.cpp中，ndk编译不通过，visual stduio编译通过
原因：生成两个模块 ，cheatGTASA.cpp只加入到一模块中，和想象的不一样，开始以为是源文件编译有先后顺序
include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)

虚函数表建立的时期：编译时
程序构建（Build）的四个过程（预编译、编译、汇编和链接）
《深度探索C++对象模型》
“表格中的virtual functions地址是如何被建构起来的？
在C++中，virtual functions（可经由其class object被调用）可以在编译时期获知。此外，这一组地址是固定不变的，执行期不可能新增或替换之。
由于程序执行时，表格的大小和内容都不会改变，所以其建构和存取皆可以由编译器完全掌控，不需要执行期的任何介入。”
https://www.cnblogs.com/xiehongfeng100/p/4678892.html

疑问：虚表里面的pointer应该是相对地址，程序启动后，在构造函数的initializer list 被重新计算？？？

```