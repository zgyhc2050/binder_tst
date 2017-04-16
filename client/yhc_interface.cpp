#include "yhc_interface.h"
#include <utils/Log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "binder:yhc_interface.cpp"
#endif

#ifdef LOG_NDEBUG
#undef LOG_NDEBUG
#define LOG_NDEBUG 0
#endif


namespace android {

Picture::Picture(): m_pClient(ClientCreator::createClient())
{

}

YHC_S32 Picture::setAspect(YHC_U32 u32Mode)
{
    Parcel request, reply;

    YHC_S32 s32Ret = YHC_SUCCESS;
    request.writeInt32(YHC_PICTURE_SETASPECT);
    request.writeInt32(u32Mode);

    s32Ret = m_pClient->invoke(request, &reply);
    LOGE("d");

    return reply.readInt32();
}


YHC_S32 Picture::getAspect()
{
    return YHC_SUCCESS;
}

}
