#define LOG_NDEBUG 0
#define LOG_TAG "YHC@yhc_file_storage.cpp"


#include "yhc_file_storage.h"
#include "yhc_common.h"
#include <stdlib.h>
#include <errno.h>


FILE *FileStorage::m_pFileID[MAX_FILE_NUM];


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

    return YHC_SUCCESS;
}

YHC_S32 FileStorage::write(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length)
{
    YHC_S32 s32Ret = YHC_SUCCESS;

    fseek(m_pFileID[*(YHC_U32 *)pData], u32pos, SEEK_SET);

    s32Ret = fwrite(pData, 1, u32Length, m_pFileID[*(YHC_U32 *)pData]);
    CHECK_RET_VALUE(s32Ret, "fwrite, u32Length:%d, ID:%d, u32pos:%d, ret:0x%x",
        u32Length, *(YHC_U32 *)pData, u32pos, s32Ret);
    return YHC_SUCCESS;
}


YHC_S32 FileStorage::read(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length)
{
    return YHC_SUCCESS;

}

