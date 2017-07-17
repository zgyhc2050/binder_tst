#define LOG_NDEBUG 0
#define LOG_TAG "YHC@logic_dbo.cpp"


#include "logic_dbo.h"
#include "yhc_common.h"


YhcDbo *YhcDbo::m_pYhcDboClass = YHC_NULL;



static YHC_S32 inserUsrData(YhcDbo *pDbo)
{
    YHC_DB_TEST1_ST stTest1;
    YHC_DB_TEST2_ST stTest2;
    memset(&stTest1, 0, sizeof(YHC_DB_TEST1_ST));
    memset(&stTest2, 0, sizeof(YHC_DB_TEST2_ST));

    stTest1.u32Frame = 60;
    stTest1.u32Width = 1920;
    stTest1.u32Hidth = 1080;
    stTest1.bByPass = YHC_TRUE;

    stTest2.bByPass = YHC_FALSE;
    stTest2.pName = "zgyhc2050";
    stTest2.u32Width = 720;

    pDbo->insert(YHC_DBO_ATTR_TEST1, &stTest1, sizeof(YHC_DB_TEST1_ST));
    pDbo->insert(YHC_DBO_ATTR_TEST2, &stTest2, sizeof(YHC_DB_TEST2_ST));

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



YHC_S32 YhcDbo::loadUsrDefault(YhcDbo *pDbo)
{
    YHC_U32 u32FileSize = 0;
    YHC_U32 u32Version = 0;
    YHC_U32 u32Pos = 0;
    YHC_BOOL bResetDb = YHC_FALSE;
    YHC_DB_DATA_ST  *pstData = YHC_NULL;
    YHC_VOID        *pDat = YHC_NULL;

    m_pFileStorage->size(&u32FileSize);
    if (0 == u32FileSize || u32FileSize < sizeof(u32Version))
    {
        bResetDb = YHC_TRUE;
        LOGI("DB file not exsit, load ini");
    }
    else
    {
        m_pFileStorage->read(0, &u32Version, sizeof(u32Version));
        if (u32Version != VERSION)
        {
            bResetDb = YHC_TRUE;
            LOGI("version update, reload ini");
        }
        else
        {
            for (u32Pos = sizeof(u32Version); u32Pos < u32FileSize; )
            {
                if (u32Pos+LENGTH >= u32FileSize)
                {
                    bResetDb = YHC_TRUE;
                    LOGI("file too small, reload ini");
                    break;
                }
                else
                {
                    YHC_U8 u8Temp[LENGTH];
                    YHC_U32 u32Length = 0;

                    pstData = (YHC_DB_DATA_ST *)malloc(sizeof(YHC_DB_DATA_ST));
                    pDat = malloc(u32Length);

                    m_pFileStorage->read(u32Pos, &u8Temp, LENGTH);
                    u32Length = *(YHC_U32 *)(u8Temp +8);

                    YHC_U8 *pu8FileData = new YHC_U8[u32Length+LENGTH+4];

                    m_pFileStorage->read(u32Pos, pu8FileData, u32Length+LENGTH+4);


                    pstData->u32AttrId = *(YHC_U32 *)pu8FileData;
                    pstData->u32FileId = *(YHC_U32 *)pu8FileData+4;
                    pstData->u32Pos = *(YHC_U32 *)(pu8FileData+8);
                    pstData->u32Len = *(YHC_U32 *)(pu8FileData+12);

                    memcpy(pDat, pu8FileData+16, pstData->u32Len);
                    pstData->pData = pDat;
                    if (*(YHC_U32 *)(pu8FileData+LENGTH+pstData->u32Len) != checkSum(pDat, pstData->u32Len))
                    {
                        bResetDb = YHC_TRUE;
                        LOGI("data error, reload ini");
                        break;
                    }
                    else
                    {
                        pstData->u32CheckSum = *(YHC_U32 *)(pu8FileData+LENGTH+pstData->u32Len);
                        u32Pos += LENGTH + pstData->u32Len + 4;
                        m_mapDbo[pstData->u32AttrId] = pstData;
                    }
                    if (pu8FileData != YHC_NULL)
                    {
                        delete pu8FileData;
                    }
                }
            }
        }
    }

    if (bResetDb)
    {
        m_pFileStorage->clear();
        inserUsrData(pDbo);
    }


    return YHC_SUCCESS;

}


YHC_S32 YhcDbo::init(YHC_CHAR *pFileStr, YHC_U32 u32Id)
{
    CHECK_PARA_NULL(pFileStr);

    m_pFileStorage = new (std::nothrow)FileStorage(pFileStr);

    m_pFileStorage->init(pFileStr, u32Id);

    loadUsrDefault(this);

    return YHC_SUCCESS;
}

YHC_S32 YhcDbo::insert(YHC_DBO_ATTR_E enDbAttr, YHC_VOID *pData, YHC_U32 u32Length)
{
    CHECK_RET_RANGE(YHC_DBO_ATTR_TEST1, YHC_DBO_ATTR_BUTT-1, enDbAttr);
    CHECK_PARA_NULL(pData);

    YHC_DB_DATA_ST  *pstData = YHC_NULL;
    YHC_VOID        *pDat = YHC_NULL;

    pstData = (YHC_DB_DATA_ST *)malloc(sizeof(YHC_DB_DATA_ST));
    pDat = malloc(u32Length);
    memcpy(pDat, pData, u32Length);


    pstData->u32Pos = 0;
    if (0 == m_mapDbo.size())
    {
        YHC_U32 u32Version = VERSION;
        LOGI("first insert data");
        m_pFileStorage->write(0, &u32Version, sizeof(u32Version));

        LOGI("111");
        pstData->u32Pos = sizeof(u32Version);
        LOGI("2");
    }


    map<YHC_U32, YHC_DB_DATA_ST *>::iterator it = m_mapDbo.find(enDbAttr);
//    map<YHC_U32, YHC_DB_DATA_ST *>::reverse_iterator iter = m_mapDbo.rbegin();

    if (it == m_mapDbo.end())
    {

        for (it = m_mapDbo.begin(); it != m_mapDbo.end(); it++)
        {
            pstData->u32Pos = it->second->u32Len;
            LOGW("pstData->u32Pos:%d", pstData->u32Pos);
        }


        pstData->u32AttrId = enDbAttr;
        pstData->u32FileId = 0;
        pstData->u32Len = u32Length;
        pstData->pData = pDat;
        pstData->u32CheckSum = checkSum(pData, u32Length);
        m_mapDbo[enDbAttr] = pstData;

        m_pFileStorage->write(pstData->u32Pos, pstData, u32Length);
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







