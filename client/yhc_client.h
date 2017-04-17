#ifndef __YHC_CLIENT_H__
#define __YHC_CLIENT_H__

#include <binder/Parcel.h>
//#include "../interface/ITestService.h"
#include "ITestService.h"
#include "yhc_type.h"
#include "yhc_interface.h"

#include <stdlib.h>
namespace android {

class Picture;

class ClientManager
{
public:
    Picture *getPicture();
    YHC_S32 invoke(const class Parcel &in, class Parcel *out);
    ClientManager();
    virtual ~ClientManager(){};
private:
    sp<Picture>         m_pPicture;
    sp<ITestService>    m_pTestService;
};


class ClientCreator
{
public:
    static ClientManager *createClient();
private:
    static ClientManager *m_pClientManager;
};

}
#endif /* end of __YHC_CLIENT_H__ */

