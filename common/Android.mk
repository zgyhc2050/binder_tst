LOCAL_PATH:= $(call my-dir)
#LOCAL_CFLAGS_ALL :=-I. -I$(LOCAL_PATH)/..

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        yhc_common.cpp \
        yhc_common.h \
	yhc_common_type.h

LOCAL_SHARED_LIBRARIES := \
        libcutils libutils libbinder libdl

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include \
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= test_binder_icommon
LOCAL_MODULE_TAGS := optional
