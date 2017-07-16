#define LOG_NDEBUG 0
#define LOG_TAG "YHC@picture_module.cpp"

#include "picture_module.h"
#include "logic_picture.h"
#include "yhc_common.h"

using namespace android;

YHC_S32 testMain(const Parcel &in, Parcel *out)
{
    setAspect(in, out);
    return 0;
}



YHC_S32 setAspect(const Parcel &in, Parcel *out)
{
    setAspect_Logic(PICTURE_ASPECT_16_9);
    return 0;
}


YHC_S32 getAspect(const Parcel &in, Parcel *out)
{
    return 0;
}





YHC_CMD_INSTRUCT_ST g_apnfInstruct_cmd[100] = {
    {CMD_INSTRUCT_TEST1, testMain},
    {CMD_INSTRUCT_SETASPECT, setAspect},
    {CMD_INSTRUCT_GETASPECT, getAspect}

};


