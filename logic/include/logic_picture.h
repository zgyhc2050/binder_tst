#ifndef __LOGIC_PICTURE_H__
#define __LOGIC_PICTURE_H__

#include "yhc_common_type.h"
#include "yhc_common.h"




typedef enum Yhc_PICTURE_ASPECT_E
{
    PICTURE_ASPECT_AUTO     = 0,
    PICTURE_ASPECT_16_9     = 1,
    PICTURE_ASPECT_4_3      = 2,
    PICTURE_ASPECT_P2P      = 3,

    YHC_PRINT_LEVEL_BUTT    = 4,
}YHC_PICTURE_ASPECT_E;




YHC_S32 setAspect(YHC_PICTURE_ASPECT_E enAspect);

#endif /* end of __LOGIC_PICTURE_H__ */

