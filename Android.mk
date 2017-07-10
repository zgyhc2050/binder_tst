#include $(call all-subdir-makefiles)

###################### compile client #######################
LOCAL_PATH:= $(call my-dir)
#LOCAL_CFLAGS_ALL :=-I. -I$(LOCAL_PATH)/..

include $(CLEAR_VARS)
APP_STL := gnustl_static

include external/stlport/libstlport.mk

LOCAL_SHARED_LIBRARIES := \
    libstlport \
LOCAL_C_INCLUDES += \
    external/stlport/stlport \


LOCAL_C_INCLUDES += external/stlport/stlport bionic/ bionic/libstdc++/include
LOCAL_SRC_FILES:= \
	    client/yhc_client.cpp\
        client/main_TestClient.cpp \
        client/yhc_interface.cpp\
        client/Callback.cpp\
        ./interface/ICallback.cpp\
        ./interface/ITestService.cpp \
        ./common/yhc_common.cpp\
        ./logic/yhc_file_storage.cpp\
        ./logic/logic_dbo.cpp

#LOCAL_SRC_FILES := \
	client/*.cpp\
	interface/*.cpp\
	logic/*.cpp\
	common/*.cpp\



LOCAL_SHARED_LIBRARIES := \
        libui libcutils libutils libbinder libstdc++ libcrypto libexpat libicuuc libicui18n libssl libz libstlport
LOCAL_STATIC_LIBRARIES := \
       libstdc++ libfdlibm

LOCAL_C_INCLUDES += \
    frameworks/base/include \
    frameworks/native/include \
    frameworks/binder_tst/common\
    frameworks/binder_tst/interface\
	frameworks/binder_tst/logic/include\
	frameworks/binder_tst/include\


LOCAL_MODULE:= test_binder_client
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)



##################### compile server ################

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ./server/main_TestService.cpp \
    ./server/TestService.cpp \
    ./interface/ITestService.cpp \
    ./interface/ICallback.cpp\
    ./module/picture_module.cpp\
    ./logic/logic_picture.cpp\
    ./common/yhc_common.cpp\

LOCAL_SHARED_LIBRARIES := \
        libcutils libutils libbinder libdl

LOCAL_C_INCLUDES += \
    frameworks/base/include \
    frameworks/native/include \
    frameworks/binder_tst/client\
    frameworks/binder_tst/interface\
    frameworks/binder_tst/common\
    frameworks/binder_tst/module\
    frameworks/binder_tst/logic/include\
	frameworks/binder_tst/server/\
    ./common/\
    $(VENDOR_SDK_INCLUDES)


LOCAL_MODULE:= test_binder_server
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
