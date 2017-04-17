#include "logic_picture.h"
//#include <pthread.h>
#include "yhc_common.h"


pthread_t TestPthreadIdOne;
using namespace android;

//#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "YHC@logic_picture.cpp"

static void *testPthreadOne(void *arg)
{
    while(1)
    {
        LOGW("send notify to Client! type:111, data:222");
        TestService::initinstace()->notify(111, 222);
        sleep(1);
    }
    return (void*)0;
}


YHC_S32 setAspect_Logic(YHC_PICTURE_ASPECT_E enAspect)
{
    LOGW("I AM holly!");
    LOGE("I AM holly!");
    pthread_create(&TestPthreadIdOne, NULL, testPthreadOne, NULL);
    return YHC_SUCCESS;
}

