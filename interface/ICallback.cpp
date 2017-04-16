#include <binder/Parcel.h>
#include <binder/IInterface.h>
#include <utils/Log.h>
#include "ICallback.h"

//#define LOG_NDEBUG 0
//#define LOG_TAG "binder@ITestCallback"

namespace android {

enum {
    SET_NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
    GET_SOMETHING,
};

//------------------------------------proxy side--------------------------------

class BpTestCallback : public BpInterface<ITestCallback>
{
public:
    BpTestCallback(const sp<IBinder>& impl): BpInterface<ITestCallback>(impl)
    {
    }
    virtual int notify(int type, unsigned int dat)
    {
        int ret = 0;
        Parcel data, reply;
        LOGW(" BpTestCallback::invoke ");
        data.writeInt32(type);
        data.writeInt32(dat);
        //data.writeInterfaceToken(ITestCallback::getInterfaceDescriptor());
        ret = remote()->transact(0, data, &reply);
        return ret;
    }
};


//---------------------- interface--------------------
IMPLEMENT_META_INTERFACE(TestCallback, "test.binder.ITestCallback");
#ifdef XXXXXXXXX
const android::String16 ITestCallback::descriptor("test.binder.ITestCallback");
const android::String16& ITestCallback::getInterfaceDescriptor() const
{
     return ITestCallback::descriptor;
}
android::sp<ITestCallback> ITestCallback::asInterface(const android::sp<android::IBinder>& obj)
{
    android::sp<ITestCallback> intr;
    if (obj != NULL)
    {
        intr = static_cast<ITestCallback>(obj->queryLocalInterface(ITestCallback::descriptor).get());
        if (intr == NULL)
        {
            intr = new BpTestCallback(obj);
        }
    }
    return intr;
}
ITestCallback::ITestCallback() { }
ITestCallback::~ITestCallback() { }
#endif


//------------------------------------server side--------------------------------
status_t BnTestCallback::onTransact (uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    int ret = 0;
    switch (code)
    {
        case SET_NOTIFY:
            LOGD("BpTestCallback::onTransact  notify");
            ret = notify(data.readInt32(), data.readInt32());
            LOGD("BpTestCallback::onTransact  notify ret:%d ", ret);
            return NO_ERROR;

        default:
            LOGD("BpTestCallback::onTransact  invoke");
            LOGD("BpTestCallback::onTransact  invoke ret:%d ", ret);
            return NO_ERROR;
            break;
    }
    return BBinder::onTransact(code, data, reply, flags);
}


}

