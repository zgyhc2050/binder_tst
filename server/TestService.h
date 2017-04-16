#ifndef __YHC_TESTSERVICE__
#define __YHC_TESTSERVICE__


#include "../interface/ITestService.h"
#include <binder/BinderService.h>
#include <binder/Parcel.h>
#include "ICallback.h"

namespace android {
class TestService : public BinderService<TestService>, public BnTestService {
public:
    static const char* getServiceName() { return "TestService"; }//will be the service name
    virtual int setSomething(int a);
    virtual int getSomething();
    virtual int invoke(const Parcel &in, Parcel *out);
    virtual int connect(const sp<ITestCallback>& callback);
    virtual int notify(int type, unsigned int data);
    TestService();

    static TestService *initinstace();
protected:
    int             myParam;
    sp<ITestCallback>   m_Callback;
    static TestService *m_pTestService;
  };
}







#endif /* end of __YHC_TESTSERVICE__ */

