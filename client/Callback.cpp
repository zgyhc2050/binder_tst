#define LOG_NDEBUG 0
#define LOG_TAG "YHC@Callback.cpp"

#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <utils/String16.h>
#include <utils/threads.h>
#include <utils/Atomic.h>
#include <cutils/properties.h>
#include <cutils/compiler.h>
#include "Callback.h"
#include "yhc_common.h"

namespace android {

int TestCallback::notify(int type, unsigned int data)
{
    LOGD("Callback::notifyCallback, Actually, come from TestService.., the callback value:  %d, data:%d", type, data);
    return 0;
}

}

