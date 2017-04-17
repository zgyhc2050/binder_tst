#include "yhc_type.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "yhc_common.h"
#include <cutils/log.h>



YHC_VOID logPrint(YHC_LOG_LEVEL_E enPrintLevel, const YHC_CHAR *pTag, const YHC_CHAR *pFunc, YHC_U32 u32Line, const YHC_CHAR *fmt, ...)
{
    YHC_U32         u32Length = 0;
    YHC_CHAR        astrLine[10];
    YHC_CHAR        au32Str[LOG_MAX_CHAR];
    const YHC_CHAR  *pstrTemp = YHC_NULL;
    va_list         arg_ptr;

#ifdef ANDROID_SYSTEM
    va_start(arg_ptr, fmt);
    u32Length += vsprintf(au32Str+u32Length, fmt, arg_ptr);
    au32Str[u32Length] = '\0';
    va_end(arg_ptr);

    switch(enPrintLevel)
    {
        case YHC_PRINT_LEVEL_V:
            /* 白色 white */
            __android_log_print(ANDROID_LOG_VERBOSE, pTag, "\033[0;37m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        case YHC_PRINT_LEVEL_D:
            /* 深绿色 deep green*/
            __android_log_print(ANDROID_LOG_DEBUG, pTag, "\033[0;36m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        case YHC_PRINT_LEVEL_I:
            /* 绿色 green */
            __android_log_print(ANDROID_LOG_INFO, pTag, "\033[0;32m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        case YHC_PRINT_LEVEL_W:
            /* 蓝色 blue */
            __android_log_print(ANDROID_LOG_WARN, pTag, "\033[0;35m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        case YHC_PRINT_LEVEL_E:
            /* 红色 red */
            __android_log_print(ANDROID_LOG_ERROR, pTag, "\033[0;31m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        case YHC_PRINT_LEVEL_F:
            /* 高亮、闪烁、反显、下划线、红色 highilght,twinkle,reverse,underline,red*/
            __android_log_print(ANDROID_LOG_FATAL, pTag, "\033[1;4;5;7;31m[%s:%d] %s\033[0m", pFunc, u32Line, au32Str);
            break;

        default:
            LOGD("%s", au32Str);
            break;
    }

#else

    va_start(arg_ptr, fmt);

    /* display file name */
    strncpy(au32Str+u32Length, pTag, strlen(pTag));
    u32Length += strlen(pTag);
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

