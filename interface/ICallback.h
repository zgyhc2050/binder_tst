#ifndef ITESTCALLBAK_H
#define ITESTCALLBAK_H

#include <binder/IInterface.h>

namespace android {


class ITestCallback : public IInterface
{
public:
    DECLARE_META_INTERFACE(TestCallback);
#ifdef XXXX
        static const android::String16 descriptor;
        static android::sp<ITestCallback> asInterface(const android::sp<android::IBinder>& obj);
        virtual const android::String16& getInterfaceDescriptor() const;
        ITestCallback();
        virtual ~ITestCallback();
#endif

    virtual int notify(int type, unsigned int data) = 0;
};

#ifdef XXXX
template<typename INTERFACE>
class BnInterface : public ITestCallback, public BBinder
#endif




class BnTestCallback : public BnInterface<ITestCallback>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
//    BnTestCallback(){};
//    ~BnTestCallback(){};
};

}
#endif // end of ITESTCALLBAK_H


