

#include "picture_module.h"
#include "logic_picture.h"

using namespace android;

YHC_CMD_INSTRUCT_ST g_apnfInstruct_cmd[100] = {
    {CMD_INSTRUCT_SETASPECT, setAspect},
    {CMD_INSTRUCT_GETASPECT, getAspect}

};

YHC_S32 setAspect(const Parcel &in, Parcel *out)
{
    setAspect_Logic(PICTURE_ASPECT_16_9);
    return 0;
}


YHC_S32 getAspect(const Parcel &in, Parcel *out)
{
    return 0;
}






