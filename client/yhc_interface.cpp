#define LOG_NDEBUG 0
#define LOG_TAG "YHC@yhc_interface.cpp"

#include "yhc_interface.h"
#include "yhc_common.h"




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
