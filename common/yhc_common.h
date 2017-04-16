#include "yhc_common_type.h"
#include <cutils/log.h>

#ifndef __YHC_COMMON__
#define __YHC_COMMON__

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

YHC_VOID logPrint(YHC_LOG_LEVEL_E enPrintLevel, const YHC_CHAR *pFile, \
    const YHC_CHAR *pFunc, YHC_U32 u32Line, const YHC_CHAR *fmt, ...)
{
    YHC_U32         u32Length = 0;
    YHC_CHAR        astrLine[10];
    YHC_CHAR        au32Str[LOG_MAX_CHAR];
    const YHC_CHAR  *pstrTemp = YHC_NULL;
    va_list         arg_ptr;

    va_start(arg_ptr, fmt);

    /* display file name */
    strncpy(au32Str+u32Length, pFile, strlen(pFile));
    u32Length += strlen(pFile);
    au32Str[u32Length] = ':';
    u32Length++;

    /* display function name */
    strncpy(au32Str+u32Length, pFunc, strlen(pFunc));
    u32Length += strlen(pFunc);
    au32Str[u32Length] = ':';
    u32Length++;

    /* display line number */
    sprintf(astrLine, "%d", u32Line);
    strncpy(au32Str+u32Length, astrLine, strlen(astrLine));
    u32Length += strlen(astrLine);
    au32Str[u32Length] = ',';
    u32Length++;

    /* display variable parameter*/
    u32Length += vsprintf(au32Str+u32Length, fmt, arg_ptr);

    au32Str[u32Length] = '\0';

#if ANDROID_SYSTEM

    switch(enPrintLevel)
    {
        case YHC_PRINT_LEVEL_V:
            /* 白色 white */
            LOGV("\033[0;37mV/%s\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_D:
            /* 深绿色 deep green*/
            LOGD("\033[0;36mD/%s\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_I:
            /* 绿色 green */
            LOGI("\033[0;32mI/%s\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_W:
            /* 蓝色 blue */
            LOGW("\033[0;35mW/%s\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_E:
            /* 红色 red */
            LOGE("\033[0;31mE/%s\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_F:
            /* 高亮、闪烁、反显、下划线、红色 highilght,twinkle,reverse,underline,red*/
            LOGF("\033[1;4;5;7;31mF/%s\033[0m", au32Str);
            break;

        default:
            LOGD("%s", au32Str);
            break;
    }

#else

    switch(enPrintLevel)
    {
        case YHC_PRINT_LEVEL_V:
            /* 白色 white */
            printf("\033[0;37mV/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_D:
            /* 深绿色 deep green*/
            printf("\033[0;36mD/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_I:
            /* 绿色 green */
            printf("\033[0;32mI/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_W:
            /* 蓝色 blue */
            printf("\033[0;35mW/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_E:
            /* 红色 red */
            printf("\033[0;31mE/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_F:
            /* 高亮、闪烁、反显、下划线、红色 highilght,twinkle,reverse,underline,red*/
            printf("\033[1;4;5;7;31mF/%s\n\033[0m", au32Str);
            break;

        default:
            printf("%s\n", au32Str);
            break;
    }
#endif
    va_end(arg_ptr);
}

#ifndef LOG_NDEBUG
#define LOG(type, ...)\
    logPrint(type, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define LOG(type, ...)
#endif


#define LOG_V(...) \
    LOG(YHC_PRINT_LEVEL_V, __VA_ARGS__)

#define LOG_D(...) \
    LOG(YHC_PRINT_LEVEL_D, __VA_ARGS__)

#define LOG_I(...) \
    LOG(YHC_PRINT_LEVEL_I, __VA_ARGS__)

#define LOG_W(...) \
    LOG(YHC_PRINT_LEVEL_W, __VA_ARGS__)

#define LOG_E(...) \
    LOG(YHC_PRINT_LEVEL_E, __VA_ARGS__)

#define LOG_F(...) \
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







#endif /* end of __YHC_COMMON__ */
