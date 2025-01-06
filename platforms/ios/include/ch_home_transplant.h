/********************** 文件说明性注释**********************************
 * 版权所有：长虹技术中心(2012)
 * 文件名： ch_home_transplant.h
 * 模块：
 * 概述： 为跨平台实现的部分通用函数接口定义
 * 作者： Chiming.Chin  qiming.jin@changhong.com
 * 创建时间：date 2012-12-11 上午9:22:16
 * 版本：V0.1
 * 修改历史:    修改时间        作者                      修改部分(哪个函数体等)        原因
 *
 ********************************************************************/

#ifndef CH_HOME_TRANSPLANT
#define CH_HOME_TRANSPLANT

//根据不同的编译器确定64位整数的定义

#ifdef WIN32
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef long long int int64;
typedef unsigned long long int uint64;
#endif
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef char int8;
typedef short int16;
typedef int int32;

#define i64toa(longSource, strTarget) Int64ToString((longSource), (strTarget));

#ifdef WIN32//windows
#define itoa(intSource, strTarget) itoa((intSource), (strTarget), 10);

#define __attribute__(a) 

#else//linux
#define itoa(intSource, strTarget) sprintf((strTarget), "%d", (intSource)); 

#define __attribute__(a) __attribute__(a) 

#endif 

int Int64ToString(int64 i64_Source, int8 * pc_Dest);
int64 HEXToInt64(unsigned char * pc_hex, int i_StrLen);
int Int64ToHex(int64 i64_dest, unsigned char * pc_hex);
#endif
