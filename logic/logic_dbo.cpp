#define LOG_NDEBUG 0
#define LOG_TAG "YHC@logic_dbo.cpp"


#include "logic_dbo.h"
#include "yhc_common.h"


YhcDbo *YhcDbo::m_pYhcDboClass = YHC_NULL;



YHC_S32 YhcDbo::inserUsrData()
{
    YHC_DB_TEST1_ST stTest1 = {60, 1920, 1080, YHC_TRUE};
    YHC_DB_TEST2_ST stTest2 = {"zgyhc2050", 720, YHC_FALSE};

    insert(YHC_DBO_ATTR_TEST1, &stTest1, sizeof(YHC_DB_TEST1_ST));
    insert(YHC_DBO_ATTR_TEST2, &stTest2, sizeof(YHC_DB_TEST2_ST));

    return YHC_SUCCESS;
}





YHC_U32 checkSum(YHC_VOID *pData, YHC_U32 u32Length)
{
    YHC_U32 u32CheckSum = 0;

    for (YHC_U32 i=0; i<u32Length; i++)
    {
        u32CheckSum += *(YHC_U8*)pData;
    }
    return u32CheckSum;
}



YHC_S32 YhcDbo::init(YHC_CHAR *pFileStr, YHC_U32 u32Id)
{
    CHECK_PARA_NULL(pFileStr);

    m_pFileStorage = new (std::nothrow)FileStorage(pFileStr);

    m_pFileStorage->init(pFileStr, u32Id);


    return YHC_SUCCESS;
}

YHC_S32 YhcDbo::insert(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length)
{
    CHECK_RET_RANGE(YHC_DBO_ATTR_TEST1, YHC_DBO_ATTR_BUTT-1, enDbAttr);
    CHECK_PARA_NULL(pData);

    YHC_DB_DATA_ST stData;
    memset(&stData, 0, sizeof(YHC_DB_DATA_ST));

    if (0 == m_mapDbo.size())
    {
        LOGI("first insert data");
    }
    else
    {
        LOGW("stData.u32Len:%d", m_mapDbo[enDbAttr]->u32Len);

    }

    map<YHC_U32, YHC_DB_DATA_ST *>::iterator it = m_mapDbo.find(enDbAttr);
    map<YHC_U32, YHC_DB_DATA_ST *>::reverse_iterator iter = m_mapDbo.rbegin();



    if (it == m_mapDbo.end())
    {
        stData.u32Pos = 0;

        for (it = m_mapDbo.begin(); it != m_mapDbo.end(); it++)
        {
            stData.u32Pos = it->second->u32Len;
            stData.u32Pos = m_mapDbo[0]->u32Len;
            LOGW("stData.u32Pos:%d", stData.u32Pos);
        }

       stData.u32FileId = 0;
       stData.u32Len = u32Length;
       stData.u32CheckSum = checkSum(pData, u32Length);
       m_mapDbo[enDbAttr] = &stData;
       LOGI("enDbAttr;%d, u32Length:%d, u32Pos:%d", enDbAttr, u32Length, stData.u32Pos);

       m_pFileStorage->write(stData.u32Pos, &stData, u32Length);


    map<YHC_U32, YHC_DB_DATA_ST *>::iterator itcur = m_mapDbo.find(enDbAttr);

    LOGW("000 length:%d and query length:%d, pos:%d",
        u32Length, itcur->second->u32Len, itcur->second->u32Pos);
    }
    else
    {
        LOGE("data is exsit!");
        return YHC_FAILURE;
    }

    return YHC_SUCCESS;
}


YHC_S32 YhcDbo::query(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length)
{
    map<YHC_U32, YHC_DB_DATA_ST *>::iterator itccc = m_mapDbo.find(enDbAttr);

    LOGW("yyyyyyy length:%d and query length:%d, pos:%d, enDbAttr:%d",
        u32Length, itccc->second->u32Len, itccc->second->u32Pos, enDbAttr);




    CHECK_RET_RANGE(YHC_DBO_ATTR_TEST1, YHC_DBO_ATTR_BUTT-1, enDbAttr);
    CHECK_PARA_NULL(pData);

    map<YHC_U32, YHC_DB_DATA_ST *>::iterator it = m_mapDbo.find(enDbAttr);

    if (it == m_mapDbo.end())
    {
        LOGE("not find data, type:0x%x", enDbAttr);
        return YHC_FAILURE;
    }
    else
    {
        if (u32Length != it->second->u32Len)
        {
            LOGE("diff from DB length:%d and query length:%d, type:0x%x, pos:%d",
                u32Length, it->second->u32Len, enDbAttr, it->second->u32Pos);

            LOGE("000 length:%d and query length:%d, pos:%d",
                u32Length, m_mapDbo[0]->u32Len, m_mapDbo[0]->u32Pos);
            LOGE("000 length:%d and query length:%d,  pos:%d",
                u32Length, m_mapDbo[1]->u32Len,  m_mapDbo[1]->u32Pos);

            return YHC_FAILURE;
        }
        memcpy(pData, it->second->pData, sizeof(YHC_DB_DATA_ST));
    }

    return YHC_SUCCESS;
}


YHC_S32 YhcDbo::update(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length)
{
    CHECK_RET_RANGE(YHC_DBO_ATTR_TEST1, YHC_DBO_ATTR_BUTT-1, enDbAttr);
    CHECK_PARA_NULL(pData);

    YHC_DB_DATA_ST stData;

    map<YHC_U32, YHC_DB_DATA_ST *>::iterator it = m_mapDbo.find(enDbAttr);
    map<YHC_U32, YHC_DB_DATA_ST *>::reverse_iterator iter = m_mapDbo.rbegin();
    if (it == m_mapDbo.end())
    {
        LOGE("not find data, type:0x%x", enDbAttr);
        return YHC_FAILURE;

    }
    else
    {
        if (u32Length != it->second->u32Len)
        {
            LOGE("update data diff from DB length:%d and query length:%d, type:0x%x",
                u32Length, it->second->u32Len, enDbAttr);
            return YHC_FAILURE;
        }

        m_mapDbo[enDbAttr]->pData = pData;
        m_pFileStorage->write(m_mapDbo[enDbAttr]->u32Pos,  m_mapDbo[enDbAttr], sizeof(YHC_DB_DATA_ST));
    }

    return YHC_SUCCESS;
}







