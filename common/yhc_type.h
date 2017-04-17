#ifndef __YHC_TYPE_H__
#define __YHC_TYPE_H__

#include <stdio.h>



typedef void            YHC_VOID;


typedef char            YHC_CHAR;
typedef char            YHC_S8;
typedef unsigned char   YHC_U8;
typedef int             YHC_S32;
typedef unsigned int    YHC_U32;
typedef long            YHC_S64;
typedef unsigned        YHC_U64;



typedef enum YHC_BOOL_E
{
    YHC_FALSE   = 0,
    YHC_TRUE    = 1,
}YHC_BOOL;





#define YHC_SUCCESS     0
#define YHC_FAILURE     -1
#define YHC_NULL        NULL


#endif /* end of __YHC_TYPE_H__ */
