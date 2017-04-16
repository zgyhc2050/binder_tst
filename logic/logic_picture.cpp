#include "logic_picture.h"
//#include <pthread.h>
#include "yhc_common.h"


pthread_t TestPthreadIdOne;
using namespace android;


static void *testPthreadOne(void *arg)
{
    while(1)
    {
        LOG_W("send notify to Client! type:111, data:222");
        TestService::initinstace()->notify(111, 222);
        sleep(1);
    }
    return (void*)0;
}


YHC_S32 setAspect_Logic(YHC_PICTURE_ASPECT_E enAspect)
{
    LOG_W("I AM holly!");
    LOG_E("I AM holly!");
    pthread_create(&TestPthreadIdOne, NULL, testPthreadOne, NULL);
    return YHC_SUCCESS;
}

