LOCAL_PATH:= $(call my-dir)
#LOCAL_CFLAGS_ALL :=-I. -I$(LOCAL_PATH)/..

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        ITestService.cpp \
        ICallback.cpp\

LOCAL_SHARED_LIBRARIES := \
        libcutils libutils libbinder libdl

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include \
    frameworks/binder_tst/interface\
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= test_binder_iserver
LOCAL_MODULE_TAGS := optional
