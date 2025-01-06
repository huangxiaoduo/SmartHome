//
//  CmdCommon.h
//  ipptest
//
//  Created by CH on 15/6/18.
//  Copyright (c) 2015年 changhong. All rights reserved.
//

#ifndef ipptest_CmdCommon_h
#define ipptest_CmdCommon_h

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef TYPEDEF_UINT8
    typedef unsigned char	uint8;
#endif
    
#ifndef TYPEDEF_UINT16
    typedef unsigned short	uint16;
#endif
    
#ifndef TYPEDEF_UINT32
    typedef unsigned int	uint32;
#endif
    
#ifndef TYPEDEF_UINT64
    typedef unsigned long long uint64;
#endif
    
    
    typedef struct
    {
        short head;
        short cmdtype;
        short cmd;
        char valuetype;
        short len;
    }CmdHead;
    
    enum GeyserCmdType{
        MSG_HEART = 0,
        MSG_SHAKE = 1,
        MSG_ORDER = 2,
        MSG_REORDER = 3,
        MSG_STATUS = 4,
        MSG_RESTATUS = 5,
        MSG_REPORT = 6,
        MSG_SCHEDULE = 7,
        MSG_ERROR = 8,
    };
    
    enum ValueType{
        CHAR_TYPE = 1,
        SHORT_TYPE = 2,
        INT_TYPE = 3,
        DOUBLE_TYPE = 4,
        STRING_TYPE = 5,
        CHARARRAY_TYPE = 6,
        OBJECT_TIME_TYPE = 7,
    };
    
    size_t encodeCommand_short(uint16 cmd, uint16 cmdtype, uint16 value, char *buf, uint32 length);
    
    size_t encodeCommand_str(uint16 cmd, uint16 cmdtype,const char* value, char *out,uint32 length);
    
    size_t encodeCommand_char(uint16 cmd, uint16 cmdtype, char value, char *out, uint32 length);
    
    size_t encodeCommand_int(uint16 cmd, uint16 cmdtype, int value, char *out, uint32 length);
    
    
    /*
     检查状态，返回1正常
     */
    int checkHead(const char *str, CmdHead *cmdhead);
    void genhead(char *buf, short cmd, short type, char valuetype);
    
    void sendWifiSSIDAndPwd(int sn, const char* ssid, const char *password);
    
#ifdef __cplusplus
}
#endif

#endif
