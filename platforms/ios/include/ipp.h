//
//  ipp.h
//  ipp
//
//  Created by pcwe2002 on 15/4/30.
//  Copyright (c) 2015年 changhong. All rights reserved.
//

#ifndef __ipp__ipp__
#define __ipp__ipp__

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ippstruct.h"

typedef  void(*IppStatusEvent)(char*,char*);
typedef void(*IppDeviceEvent)(PIPPDevice);
typedef void(*IppCommonEvent)(PIPPDevice,const char *,int);

//add by yw
typedef void(*IppHighStatusEvent)(int, PIPPHIGHHOCOSTATUS);
typedef void(*IppSendStatusEvent)(int, PIPPHOCOSTATUS);
typedef void(*IppSendEvent)(int, int, int);
typedef void(*IppDeviceEventReport)(PIPPDevice, int, int, char *, int);
typedef void(*IppDeviceSetAck)(PIPPDevice, int, int);
    
/**
 事件响应
*/
void jniOnReportStatus( char *uuid, char* status);
void onIPPDeviceAdd(PIPPDevice dev);
void onIPPDeviceRemove(PIPPDevice dev);
void onIPPNetworkDisconnect();
void onIppDeviceEvent(PIPPDevice dev, const char *param, int length);
void onIppDeviceEvent2(PIPPDevice dev, const char *data, int length);
    
//add by yw
void onDeviceEventReport(PIPPDevice dev, int eventtype, int param1, char *param2, int param2length);
void onIPPDeviceSetAck(PIPPDevice dev, int id, int success);
void registerACCallBack(IppDeviceEventReport ippDeviceReport,IppDeviceSetAck ippSetAck);
    
// IPP操作函数定义
void sendCommand(int id, const char *cmd, int length);
int getStatus(int id, char *status);
void *ippCreate();
void ippDestroy(void* ipp);
void registerCallback(IppDeviceEvent ippDeviceAdd, IppDeviceEvent ippDeviceRemove, IppStatusEvent ippReportStatus, IppCommonEvent ippCommonEvent);
void setWifiSSIDAndPassword(int id, const char *ssid,const char *password);
void setIPPOnlineDeviceType(int type);
    
#pragma mark 烟机相关函数
void registerSmokeCallback(IppHighStatusEvent ippHighStatus,            IppSendStatusEvent ippSendStatus,IppSendEvent ippSendError, IppSendEvent ippSendcookerTotaltime, IppSendEvent ippSendCookerTimeLeft);
//add by yw
void jniOnSendHighStatus(int id, PIPPHIGHHOCOSTATUS status);
void jniOnSendStatus(int id, PIPPHOCOSTATUS status);
void jniOnSendError(int id, int error, int errorvalue);
void jniOnSendCookerTotalTime(int id, int cookernum, int totaltime);
void jniOnSendCookerTimeLeft(int id, int timenum, int timeleft);
#ifdef __cplusplus
}
#endif

#endif //__ipp__ipp__