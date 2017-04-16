#include "yhc_client.h"
#include <binder/IServiceManager.h>

namespace android {

ClientManager::ClientManager(): m_pPicture(YHC_NULL)
{
    int count = 10;
    if (m_pTestService == YHC_NULL)
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
        m_pTestService = interface_cast<ITestService>(binder);
    }
}



Picture *ClientManager::getPicture()
{
    if (YHC_NULL == m_pPicture.get())
    {
        m_pPicture = new (std::nothrow)Picture();
        if (YHC_NULL == m_pPicture.get())
        {
            LOGE("new Picture faild!");
        }
    }
    return m_pPicture.get();
}


YHC_S32 ClientManager::invoke(const Parcel &in, Parcel *out)
{
    YHC_S32 s32Ret = YHC_SUCCESS;
    s32Ret = m_pTestService->invoke(in, out);
    return s32Ret;
}

ClientManager *ClientCreator::m_pClientManager;


ClientManager *ClientCreator::createClient()
{
    if (YHC_NULL == m_pClientManager)
    {
        m_pClientManager = new (std::nothrow)ClientManager();
        if (YHC_NULL == m_pClientManager)
        {
            LOGE("new ClientManager faild!");
        }
    }
    return m_pClientManager;
}

}
