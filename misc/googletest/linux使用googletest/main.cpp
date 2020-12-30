

#include "include/gtest/gtest.h"

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
	return RUN_ALL_TESTS();
}

/*
-I头文件路径
-L库文件路径
-l库文件
g++ main.cpp -o usingGT -I/home/wangfeng/文档/usingGoogletest/include -L/home/wangfeng/文档/usingGoogletest/lib -lgtest -lpthread -std=c++11
*/