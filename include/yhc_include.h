#ifndef __YHC_INCLUDE_H__
#define __YHC_INCLUDE_H__

#include "yhc_type.h"



typedef enum Yhc_DBO_ATTR_E
{
    YHC_DBO_ATTR_TEST1       = 0,
    YHC_DBO_ATTR_TEST2       = 1,

    YHC_DBO_ATTR_BUTT        = 100,
}YHC_DBO_ATTR_E;


typedef struct Yhc_DB_TEST1_ST
{
    YHC_U32 u32Frame;
    YHC_U32 u32Width;
    YHC_U32 u32Hidth;
    YHC_BOOL bByPass;
}YHC_DB_TEST1_ST;


typedef struct Yhc_DB_TEST2_ST
{
    YHC_CHAR *pName;
    YHC_U32 u32Width;
    YHC_U32 u32Hidth;
    YHC_BOOL bByPass;
}YHC_DB_TEST2_ST;


#endif /* end of __YHC_INCLUDE_H__ */


