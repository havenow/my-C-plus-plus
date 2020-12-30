#include "include\\gtest\\gtest.h"
#pragma comment(lib, "lib\\Debug\\gtestd.lib")
int add(int a, int b)
{
	return a + b;
}

TEST(test, add1) {
	EXPECT_EQ(add(3, 4), 7);//==
	EXPECT_NE(add(3, 4), 9);//!=
	EXPECT_LT(add(3, 4), 8);//<
	EXPECT_LE(add(3, 4), 7);//<=
	EXPECT_GT(add(3, 4), 6);//>
	EXPECT_GE(add(3, 4), 7);//>=
}

TEST(test, add2) {
	EXPECT_EQ(add(3, 4), 7);//==
	EXPECT_NE(add(3, 4), 9);//!=
	EXPECT_LT(add(3, 4), 8);//<
	EXPECT_LE(add(3, 4), 7);//<=
	EXPECT_GT(add(3, 4), 9);//error >
	EXPECT_GE(add(3, 4), 7);//>=
}

int main()
{
	testing::InitGoogleTest();
	RUN_ALL_TESTS();
	return 0;
}

/*
googletest编译
cmake生成windows工程
打开windows工程文件，生成gtest.lib静态库，gtest工程属性 C/C++ -->代码生成器 --> 运行库 --> d多线程调试DLL(/MDd)
输出的信息是彩色的，没看具体的实现
*/