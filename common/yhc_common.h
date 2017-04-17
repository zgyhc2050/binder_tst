#ifndef __YHC_COMMON_H__
#define __YHC_COMMON_H__

#include "yhc_type.h"

#define ANDROID_SYSTEM

typedef enum Yhc_LOG_LEVEL_E
{
    YHC_PRINT_LEVEL_V       = 0,
    YHC_PRINT_LEVEL_D       = 1,
    YHC_PRINT_LEVEL_I       = 2,
    YHC_PRINT_LEVEL_W       = 3,
    YHC_PRINT_LEVEL_E       = 4,
    YHC_PRINT_LEVEL_F       = 5,

    YHC_PRINT_LEVEL_BUTT    = 6,
}YHC_LOG_LEVEL_E;


#define LOG_MAX_CHAR 1024


typedef enum Yhc_ATTR_TYPE_E
{
    ATTR_TYPE_TEST_ONE  = 0,
    ATTR_TYPE_TEST_TWO  = 1,

    ATTR_TYPE_TEST_BUTT = 2,
}YHC_ATTR_TYPE_E;

YHC_VOID logPrint(YHC_LOG_LEVEL_E enPrintLevel, const YHC_CHAR *pTag, const YHC_CHAR *pFunc, YHC_U32 u32Line, const YHC_CHAR *fmt, ...);

//#ifndef LOG_NDEBUG
#define LOG(type, ...)\
    logPrint(type, LOG_TAG, __FUNCTION__, __LINE__, __VA_ARGS__)
//#else
//#define LOG(type, ...)
//#endif

#ifdef LOGV
#undef LOGV
#endif
#define LOGV(...) \
    LOG(YHC_PRINT_LEVEL_V, __VA_ARGS__)

#ifdef LOGD
#undef LOGD
#endif
#define LOGD(...) \
    LOG(YHC_PRINT_LEVEL_D, __VA_ARGS__)

#ifdef LOGI
#undef LOGI
#endif
#define LOGI(...) \
    LOG(YHC_PRINT_LEVEL_I, __VA_ARGS__)

#ifdef LOGW
#undef LOGW
#endif
#define LOGW(...) \
    LOG(YHC_PRINT_LEVEL_W, __VA_ARGS__)

#ifdef LOGE
#undef LOGE
#endif
#define LOGE(...) \
    LOG(YHC_PRINT_LEVEL_E, __VA_ARGS__)

#ifdef LOGF
#undef LOGF
#endif
#define LOGF(...) \
    LOG(YHC_PRINT_LEVEL_F, __VA_ARGS__)


#define PRINT_COLOR_CONVERT(type) \




#define CHECK_PARA_NULL(ptr)            \
    do                                  \
    {                                   \
        if (YHC_NULL == ptr)            \
        {                               \
            printf("NULL Pointer!\n");  \
            return YHC_FAILURE;         \
        }                               \
    }while(0)


#define CHECK_RET_VALUE(s32Ret, ...)               \
    do                                             \
    {                                              \
        if (s32Ret != YHC_SUCCESS)                 \
        {                                          \
            LOGE(__VA_ARGS__);                     \
            return s32Ret;                         \
        }                                          \
    }while(0)

#define CHECK_RET_DEBUG_LOG(s32Ret, ...)           \
    do                                             \
    {                                              \
        if (s32Ret != YHC_SUCCESS)                 \
        {                                          \
            LOGE(__VA_ARGS__);                     \
        }                                          \
        else                                       \
        {                                          \
            LOGD(__VA_ARGS__);                     \
        }                                          \
        return s32Ret;                             \
    }while(0)







#endif /* end of __YHC_COMMON_H__ */
