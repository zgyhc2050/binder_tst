#ifndef __YHC_INTERFACE_H__
#define __YHC_INTERFACE_H__

#include "yhc_common_type.h"
#include "yhc_client.h"
#include <binder/Parcel.h>

namespace android {

typedef enum Yhc_CMD_INVOKE_E
{
    YHC_PICTURE_SETASPECT       = 0,
    YHC_PICTURE_GETASPECT       = 1,

    YHC_PICTURE_BUTT            = 100,
}YHC_CMD_INVOKE_E;

class ClientManager;

class Picture: public RefBase
{
public:
    YHC_S32 setAspect(YHC_U32 u32Mode);
    YHC_S32 getAspect();

    Picture();
    virtual ~Picture(){};
private:
    ClientManager *m_pClient;
};

}
#endif /* end of __YHC_INTERFACE_H__ */

