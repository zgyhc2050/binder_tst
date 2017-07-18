#ifndef __FILE_STORAGE_H__
#define __FILE_STORAGE_H__

#include "yhc_type.h"
#include "yhc_common.h"

#define MAX_FILE_NUM 5


class FileStorage
{
public:
    FileStorage(char *pchrPath);
    ~FileStorage();
    YHC_S32 init(YHC_CHAR *pFileStr, YHC_U32 u32Id);
    YHC_S32 write(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length);
    YHC_S32 read(YHC_U32 u32pos, YHC_VOID *pData, YHC_U32 u32Length);
    YHC_S32 size(YHC_U32 *pu32Size);
    YHC_S32 clear();
private:
    static FILE *m_pFileID[MAX_FILE_NUM];
    static YHC_CHAR *m_pFilePath[MAX_FILE_NUM];
    FILE *m_pCurFileID;
    char *m_pchrPath;


};




#endif

