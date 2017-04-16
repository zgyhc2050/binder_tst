#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "TestService.h"
//#define LOG_NDEBUG 0
//#define LOG_TAG "yhc: TestService-main"

#define EASY_START_BINDER_SERVICE 0

using namespace android;

int main(int argc, char** argv)
{
#if EASY_START_BINDER_SERVICE
    TestService::publishAndJoinThreadPool();
#else
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm(defaultServiceManager());
    sm->addService(String16(TestService::getServiceName()), TestService::initinstace());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
#endif
    while(1)
    {
        TestService::initinstace()->notify(1111, 22222);
        LOGW("service send notify to client");
    }

    return 0;
}
