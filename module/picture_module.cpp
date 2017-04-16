

#include "picture_module.h"
#include "logic_picture.h"

using namespace android;


YHC_S32 setAspect(const Parcel &in, Parcel *out)
{
    setAspect(PICTURE_ASPECT_16_9);
    return 0;
}


YHC_S32 getAspect(const Parcel &in, Parcel *out)
{
    return 0;
}





g_apnfInstruct_cmd[] = {
    {CMD_INSTRUCT_SETASPECT, setAspect},
    {CMD_INSTRUCT_GETASPECT, getAspect}

};
