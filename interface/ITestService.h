#ifndef ITESTService_H
#define ITESTService_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "ICallback.h"

namespace android {
class ITestService : public IInterface
{
public:
    DECLARE_META_INTERFACE(TestService);
#ifdef XXXX
    static const android::String16 descriptor;
    static android::sp<ITestService> asInterface(const android::sp<android::IBinder>& obj);
    virtual const android::String16& getInterfaceDescriptor() const;
    ITestService();
    virtual ~ITestService();
#endif
    virtual int setSomething(int a) = 0;
    virtual int getSomething() = 0;
    virtual int invoke(const Parcel &in, Parcel *out) = 0;
    virtual int connect(const sp<ITestCallback>& callback) = 0;
};

#ifdef XXXX
template<typename INTERFACE>
class BnInterface : public ITestService, public BBinder
#endif




class BnTestService : public BnInterface<ITestService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}
#endif
