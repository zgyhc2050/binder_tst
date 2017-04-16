LOCAL_PATH:= $(call my-dir)
#LOCAL_CFLAGS_ALL :=-I. -I$(LOCAL_PATH)/..

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        yhc_client.cpp\
        main_TestClient.cpp \
        yhc_interface.cpp\
        Callback.cpp\
        ../interface/ICallback.cpp\
        ../interface/ITestService.cpp \
        ../common/yhc_common.cpp\
#        ../interface/ICallback.cpp \
#        Callback.cpp

LOCAL_SHARED_LIBRARIES := \
        libui libcutils libutils libbinder

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include \
    frameworks/binder_tst/common\
    frameworks/binder_tst/interface\
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= test_binder_client
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
