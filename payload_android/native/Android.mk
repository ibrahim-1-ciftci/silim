LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := payload
LOCAL_SRC_FILES := payload.c
LOCAL_LDLIBS    := -llog
include $(BUILD_SHARED_LIBRARY)