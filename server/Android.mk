LOCAL_PATH:= $(call my-dir)
#LOCAL_CFLAGS_ALL :=-I. -I$(LOCAL_PATH)/..

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    main_TestService.cpp \
	TestService.cpp \
    ../interface/ITestService.cpp \
    ../interface/ICallback.cpp\
	../module/picture_module.cpp\
	../logic/logic_picture.cpp\
	../common/yhc_common.cpp\

LOCAL_SHARED_LIBRARIES := \
        libcutils libutils libbinder libdl

LOCAL_C_INCLUDES := \
    frameworks/base/include \
    frameworks/native/include \
    frameworks/binder_tst/client\
    frameworks/binder_tst/interface\
	frameworks/binder_tst/common\
	frameworks/binder_tst/module\
	frameworks/binder_tst/logic/include\
    ../common/\
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= test_binder_server
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
