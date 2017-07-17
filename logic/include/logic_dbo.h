#ifndef __LOGIC_DBO_H__
#define __LOGIC_DBO_H__

#include "yhc_type.h"
#include "yhc_common.h"
#include "yhc_include.h"
#include <string.h>
#include "yhc_file_storage.h"

#include <map>

using namespace std;

typedef struct Yhc_DB_DATA_ST
{
    YHC_U32     u32AttrId;
    YHC_U32     u32FileId;
    YHC_U32     u32Pos;
    YHC_U32     u32Len;
    YHC_VOID    *pData;
    YHC_U32     u32CheckSum;
}YHC_DB_DATA_ST;

#define LENGTH (sizeof(YHC_U32) + sizeof(YHC_U32) + sizeof(YHC_U32) + sizeof(YHC_U32))


class YhcDbo
{
public:
    static YhcDbo *getDbo();
    YHC_S32 init(YHC_CHAR *pFileStr, YHC_U32 u32Id);
    YHC_S32 insert(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length);
    YHC_S32 query(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length);
    YHC_S32 update(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length);
private:
    YhcDbo();
    ~YhcDbo();
    YHC_S32 loadUsrDefault(YhcDbo *pDbo);
    map<YHC_U32, YHC_DB_DATA_ST *>   m_mapDbo;
    FileStorage *m_pFileStorage;
    static YhcDbo *m_pYhcDboClass;
    static const YHC_U32 VERSION = 1;

};


inline YhcDbo::YhcDbo()
{
    init("/yhc/db/usr.db", 0);
}

inline YhcDbo::~YhcDbo()
{

}

inline YhcDbo *YhcDbo::getDbo()
{
    if (YHC_NULL == m_pYhcDboClass)
    {
        m_pYhcDboClass = new (std::nothrow)YhcDbo();
        if (YHC_NULL == m_pYhcDboClass)
        {
            LOGE("new YhcDbo faild!");
        }
    }
    return m_pYhcDboClass;
}


#endif /* end of __LOGIC_DBO_H__ */





