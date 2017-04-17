#include "ITestService.h"
#include <binder/Parcel.h>
#include <binder/IInterface.h>
#include "ICallback.h"
#include "yhc_common.h"

#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "YHC@ITestService.cpp"

namespace android {

enum {
    SET_SOMETHING = IBinder::FIRST_CALL_TRANSACTION,
    GET_SOMETHING,
    CONNECT,
};

//------------------------------------proxy side--------------------------------

class BpTestService : public BpInterface<ITestService>
{
public:
    BpTestService(const sp<IBinder>& impl)
        : BpInterface<ITestService>(impl) {
    }
    virtual int setSomething(int a)
    {
        LOGD(" BpTestService::setSomething a = %d ", a);
        Parcel data,reply;
        data.writeInt32(a);
        remote()->transact(SET_SOMETHING,data,&reply);
        return reply.readInt32();
    }
    virtual int getSomething()
    {
        LOGW("BpTestService::getSomething ");
        Parcel data,reply;
        data.writeInterfaceToken(ITestService::getInterfaceDescriptor());
        remote()->transact(GET_SOMETHING,data,&reply);
        return reply.readInt32();
    }
    virtual int invoke(const Parcel &in, Parcel *out)
    {
        int ret = 0;
        LOGW("BpTestService::invoke ");
        //data.writeInterfaceToken(ITestService::getInterfaceDescriptor());
        ret = remote()->transact(0, in, out);
        return ret;
    }
    virtual int connect(const sp<ITestCallback>& callback)
    {
        LOGW("BpTestService::connect");
        Parcel in, out;
        in.writeStrongBinder(callback->asBinder());
        remote()->transact(CONNECT, in, &out);
        return out.readInt32();

    }
};


//---------------------- interface--------------------
IMPLEMENT_META_INTERFACE(TestService, "chenxf.binder.ITestService");
#ifdef XXXXXXXXX
const android::String16 ITestService::descriptor("chenxf.binder.ITestService");
const android::String16& ITestService::getInterfaceDescriptor() const
{
     return ITestService::descriptor;
}
android::sp<ITestService> ITestService::asInterface(const android::sp<android::IBinder>& obj)
{
    android::sp<ITestService> intr;
    if (obj != NULL)
    {
        intr = static_cast<ITestService>(obj->queryLocalInterface(ITestService::descriptor).get());
        if (intr == NULL)
        {
            intr = new BpTestService(obj);
        }
    }
    return intr;
}
ITestService::ITestService() { }
ITestService::~ITestService() { }
#endif


//------------------------------------server side--------------------------------
status_t BnTestService::onTransact (uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    int ret = 0;
    switch (code)
    {
        case SET_SOMETHING:
        {
            LOGD("BnTestService::onTransact  SET_SOMETHING ");
            reply->writeInt32(setSomething((int) data.readInt32()));
            return NO_ERROR;
        }
        break;
        case GET_SOMETHING:
        {
            LOGD("BnTestService::onTransact  GET_SOMETHING ");
            reply->writeInt32(getSomething());
            return NO_ERROR;
        } break;
        case CONNECT:
        {
            LOGW("BnTestService::onTransact  CONNECT ");
            sp<ITestCallback> callback = interface_cast<ITestCallback>(data.readStrongBinder());
            reply->writeInt32(connect(callback));
            return NO_ERROR;
        }
        default:
            LOGD("BnTestService::onTransact  invoke");
            ret = invoke(data, reply);
            LOGD("BnTestService::onTransact  invoke ret:%d ", ret);
            return NO_ERROR;
            break;
    }
    return BBinder::onTransact(code, data, reply, flags);
}


}
