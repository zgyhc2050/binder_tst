#include "ITestService.h"
#include "ICallback.h"
#include <binder/BinderService.h>
namespace android {
class TestCallback: public BnTestCallback
{
    public:
      virtual int notify(int type, unsigned int data);
      TestCallback(){};
      virtual ~TestCallback(){};
};
}

