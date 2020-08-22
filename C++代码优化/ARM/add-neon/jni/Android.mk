LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := neonAdd

LOCAL_SRC_FILES := neonAdd.cpp.neon

LOCAL_STATIC_LIBRARIES := cpufeatures

LOCAL_LDLIBS := -llog

LOCAL_CFLAGS += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE
include $(BUILD_EXECUTABLE)

