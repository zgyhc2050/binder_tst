#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
//#include <utils/Log.h>
#include <cutils/log.h>

#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <utils/threads.h>
#include "yhc_common_type.h"

#include <cutils/properties.h>
#include "TestService.h"
//#define LOG_NDEBUG 0
//#define LOG_TAG "chenxf: TestService"
#include "picture_module.h"
extern YHC_CMD_INSTRUCT_ST g_apnfInstruct_cmd[100];

namespace android {
    TestService::TestService()
    {
        myParam = 0;
    }

    int TestService::setSomething(int a)
    {
        LOGD(" TestService::setSomething a = %d myParam %d", a, myParam);
        myParam += a;
        return 0;//OK
    }
    int TestService::getSomething()
    {
        LOGD("#TestService::getSomething myParam = %d", myParam);
        return myParam;
    }
    int TestService::invoke(const Parcel &in, Parcel *out)
    {
        YHC_S32 s32Ret = YHC_SUCCESS;
        YHC_CMD_INSTRUCT_E enCmd = (YHC_CMD_INSTRUCT_E)in.readInt32();
        for (YHC_U32 i=0; i<sizeof(g_apnfInstruct_cmd); i++)
        {
            if (g_apnfInstruct_cmd[i].enFuncCmd == enCmd)
            {
                LOGD("#2TestService::invoke enCmd: %d", enCmd);
                s32Ret = (*g_apnfInstruct_cmd[i].pnfFunction)(in, out);
                LOGD("#3TestService::invoke enCmd: %d", enCmd);
                break;
            }
        }
        return s32Ret;
    }
    int TestService::notify(int type, unsigned int data)
    {
        LOGD("\033[0;35mW/1#TestService::notify type:%d, first data:%d\033[0m", type, data);
        LOGW("2#TestService::notify type:%d, first data:%d", type, data);
        m_Callback->notify(type, data);

        return -222;
    }

    int TestService::connect(const sp<ITestCallback>& callback)
    {
        LOGD(" TestService::connect");
        m_Callback = callback;
        return 0;
    }


TestService *TestService::m_pTestService;

TestService *TestService::initinstace()
{
    if (NULL == m_pTestService)
    {
        m_pTestService = new (std::nothrow)TestService();
        if (NULL == m_pTestService)
        {
            LOGE("new TestService faild!");
        }
    }
    return m_pTestService;
}


}
