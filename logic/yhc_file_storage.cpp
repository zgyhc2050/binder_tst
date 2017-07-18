#define LOG_NDEBUG 0
#define LOG_TAG "YHC@yhc_file_storage.cpp"


#include "yhc_file_storage.h"
#include "yhc_common.h"
#include <stdlib.h>
#include <errno.h>


FILE *FileStorage::m_pFileID[MAX_FILE_NUM];
YHC_CHAR *FileStorage::m_pFilePath[MAX_FILE_NUM];


FileStorage::FileStorage(char *pchrPath) : m_pchrPath(pchrPath)
{

}

FileStorage::~FileStorage()
{

}




YHC_S32 FileStorage::init(YHC_CHAR *pFileStr, YHC_U32 u32Id)
{
    CHECK_PARA_NULL(pFileStr);

    if (u32Id >= MAX_FILE_NUM)
    {
        LOGE("illegal param u32Id:%d, too large, max ID is %d", u32Id, MAX_FILE_NUM-1);
        return YHC_FAILURE;
    }
    if (m_pFileID[u32Id] != YHC_NULL)
    {
        LOGE("file u32Id:%d is exist", u32Id);
        return YHC_FAILURE;
    }

    YHC_S32 s32Ret = YHC_SUCCESS;
    FILE *pFile = YHC_NULL;

    pFile = fopen(pFileStr, "r+b");
    if (YHC_NULL == pFile)
    {
//        string shellCmd = "mkdir -p ";
//        system((shellCmd + pFileStr.substr(0, pFileStr.rfind('/'))).c_str());
        s32Ret = system("mkdir -p /yhc/db");

        LOGW("system, ret:0x%x", s32Ret);
        pFile = fopen(pFileStr, "w+b");
        if (YHC_NULL == pFile)
        {
            LOGE("create file:%s failure! ret:0x%x", pFileStr, errno);
            return YHC_FAILURE;
        }
    }

    m_pFileID[u32Id] = pFile;
    LOGW("m_pFileID[0]:%p", m_pFileID[0]);

    return YHC_SUCCESS;
}

YHC_S32 FileStorage::write(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length)
{
    if (YHC_NULL == m_pFileID[0])
    {
        LOGE("file not open");
        return YHC_FAILURE;
    }

    YHC_S32 s32Ret = YHC_SUCCESS;


    LOGI("m_pFileID[0]:%p, u32pos:%d, ", m_pFileID[0], u32pos);

    s32Ret = fseek(m_pFileID[0], u32pos, SEEK_SET);
    if (s32Ret != YHC_SUCCESS)
    {
//        LOGE("fwrite ret:%s", perror("dddd"));
        perror("dddd");
    }


    LOGI("ab");
    s32Ret = fwrite(pData, 1, u32Length, m_pFileID[0]);
    if (s32Ret != u32Length)
    {
    }
    LOGE("fwrite, u32Length:%d, ID:%d, u32pos:%d, ret:0x%x",
        u32Length, 0, u32pos, s32Ret);

    YHC_U32 DDDDD;
    size(&DDDDD);
    LOGF("size:%d", DDDDD);

    return YHC_SUCCESS;
}


YHC_S32 FileStorage::read(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length)
{
    if (YHC_NULL == m_pFileID[0])
    {
        LOGE("file not open");
        return YHC_FAILURE;
    }


    YHC_S32 s32ReadCnt = 0;

    fseek(m_pFileID[0], u32pos, SEEK_SET);

    s32ReadCnt = fread(pData, 1, u32Length, m_pFileID[0]);
    if (s32ReadCnt != (YHC_S32)u32Length)
    {
        LOGE("fwrite, u32Length:%d, ID:%d, u32pos:%d, ReadCnt:0x%x",
            u32Length, *(YHC_U32 *)pData, u32pos, s32ReadCnt);

        return YHC_FAILURE;
    }

    return YHC_SUCCESS;

}

YHC_S32 FileStorage::size(YHC_U32 *pu32Size)
{
    if (YHC_NULL == m_pFileID[0])
    {
        LOGE("file not open");
        return YHC_FAILURE;
    }

    fseek(m_pFileID[0], 0, SEEK_END);
    *pu32Size = ftell(m_pFileID[0]);
    LOGI("FileStorage size :%d", *pu32Size);

    return YHC_SUCCESS;

}

YHC_S32 FileStorage::clear()
{
    if (YHC_NULL == m_pFileID[0])
    {
        LOGE("file not open");
        return YHC_FAILURE;
    }
    system("rm -rf /yhc/db/*");

    m_pFileID[0] = fopen("/yhc/db/usr.db", "w+b");
    if (YHC_NULL == m_pFileID[0])
    {
        LOGE("create file failure! ret:0x%x", errno);
        return YHC_FAILURE;
    }
    LOGW("m_pFileID[0]:%p", m_pFileID[0]);

    return YHC_SUCCESS;

}

