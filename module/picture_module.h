#ifndef __PICTURE_MODULE_H__
#define __PICTURE_MODULE_H__

#include "yhc_type.h"
#include "yhc_common.h"
#include <binder/Parcel.h>

using namespace android;
//class Parcel;

typedef enum Yhc_CMD_INSTRUCT_E
{
    CMD_INSTRUCT_SETASPECT      = 0,
    CMD_INSTRUCT_GETASPECT      = 1,

    CMD_INSTRUCT_GETASPECT_BUTT = 2,
}YHC_CMD_INSTRUCT_E;

typedef YHC_S32 (*pnfModuleFunc)(const Parcel &, Parcel *);

typedef struct Yhc_CMD_INSTRUCT_ST
{
    YHC_CMD_INSTRUCT_E  enFuncCmd;
    pnfModuleFunc       pnfFunction;
}YHC_CMD_INSTRUCT_ST;



YHC_S32 setAspect(const Parcel &in, Parcel *out);
YHC_S32 getAspect(const Parcel &in, Parcel *out);



#endif
