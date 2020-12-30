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
googletest����
google��ndk���߰�������һ���ļ��� sources\third_party\googletest������õİ汾��21.1.6352462
sources\third_party\googletest��ֻ��һ��Android.mk�ļ���û��Application.mk���½�һ��

APP_ABI := armeabi-v7a
APP_PLATFORM := android-26
APP_STL := c++_static
NDK_TOOLCHAIN_VERSION := clang

�½�һ��Ŀ¼src������googletest�ļ���src�£��޸�googletest������Ϊjni
ndk-build�����Կ���obj\local\armeabi-v7a\libgtest.a

�½�һ��ndk���̣�ʹ��libgtest.a�����ӵ�ʱ���Ҳ������ţ�δ�ҵ�ԭ��

��ʱ���������
��googletest��Android.mk���ӣ�
include $(CLEAR_VARS)
LOCAL_MODULE    := usingGoogleTest
LOCAL_SRC_FILES := main.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include					
LOCAL_LDLIBS := -llog 
LOCAL_STATIC_LIBRARIES :=  libgtest

LOCAL_CFLAGS += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE

include $(BUILD_EXECUTABLE)

usingGoogleTest ���򿽱���/data/local/tmpĿ¼��������
*/