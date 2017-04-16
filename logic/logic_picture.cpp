#include "logic_picture.h"
#include <pthread.h>

#include "TestService.h"

pthread_t TestPthreadIdOne;


static void *testPthreadOne(void *arg)
{
    while(1)
    {
        LOGW("send notify to Client! type:111, data:222");
        TestService::initinstace()->notify(111, 222);
        sleep(1);
    }
}


YHC_S32 setAspect(YHC_PICTURE_ASPECT_E enAspect)
{
    LOGW("I AM holly!");
    LOGE("I AM holly!");
    pthread_create(&TestPthreadIdOne, NULL, testPthreadOne, NULL);
}

