#include "include\\gtest\\gtest.h"

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
google的ndk工具包里面有一个文件夹 sources\third_party\googletest，这边用的版本是21.1.6352462
sources\third_party\googletest下只有一个Android.mk文件，没有Application.mk，新建一个

APP_ABI := armeabi-v7a
APP_PLATFORM := android-26
APP_STL := c++_static
NDK_TOOLCHAIN_VERSION := clang

新建一个目录src，拷贝googletest文件夹src下，修改googletest的名称为jni
ndk-build，可以看到obj\local\armeabi-v7a\libgtest.a

新建一个ndk工程，使用libgtest.a，链接的时候找不到符号，未找到原因

临时解决方案：
在googletest的Android.mk最后加：
include $(CLEAR_VARS)
LOCAL_MODULE    := usingGoogleTest
LOCAL_SRC_FILES := main.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include					
LOCAL_LDLIBS := -llog 
LOCAL_STATIC_LIBRARIES :=  libgtest

LOCAL_CFLAGS += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE

include $(BUILD_EXECUTABLE)

usingGoogleTest 程序拷贝到/data/local/tmp目录可以运行
*/