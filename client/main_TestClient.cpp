#include <stdio.h>
#include "../interface/ITestService.h"
#include <binder/IServiceManager.h>
//#include <utils/Log.h>
#include <stdlib.h>
#include "yhc_common_type.h"
#include "yhc_client.h"
#include "Callback.h"



//#define LOG_NDEBUG 0
//#define LOG_TAG "chenxf: Client-main"

using namespace android;

sp<ITestService> mTestService;

void initTestServiceClient()
{
    int count = 10;
    if (mTestService == 0)
    {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        do
        {
            binder = sm->getService(String16("TestService"));
            if (binder != 0)
            break;
            LOGW("TestService not published, waiting...");
            sleep(1); // 1 s
            count++;
        } while (count < 20);
        mTestService = interface_cast<ITestService>(binder);
    }
}


int main(int argc, char* argv[])
{
#if 1
    Parcel in, out;
    int ret = 0;
    if (argc > 1)
    {
        LOGW("*argv[1] %d", atoi(argv[1]));
    }
    initTestServiceClient();
    if(mTestService ==NULL)
    {
        LOGW("cannot find TestService");
        return 0;
    }

    sp<TestCallback> c = new TestCallback();
    mTestService->connect(c);

    in.writeInt32(0);
    in.writeInt32(1000);
    LOGD("invoke start");

    ret = mTestService->invoke(in, &out);

    LOGD("invoke end, retrun value:%d, ret:%d", out.readInt32(), ret);
#else

    int s32Ret = YHC_SUCCESS;
    Picture *pPicture = YHC_NULL;
    pPicture = ClientCreator::createClient()->getPicture();

    s32Ret = pPicture->setAspect(2080);

#endif

    return 0;
}
