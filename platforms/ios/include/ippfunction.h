/*
 * ippfunction.h
 *
 *  Created on: 2012-9-28
 *      Author: chobit
 */

#ifndef IPPFUNCTION_H_
#define IPPFUNCTION_H_
//#define ANDROID
#include "tools_link.h"
#ifdef ANDROID
#include <android/log.h>
#endif
#define IPP_ERROR_SUCCESS 1
#define IPP_ERROR_FAILE -1

#define IPP_LAN 1
#define IPP_WAN 2

#define IPP_MAX_GOODS  256

#define IPP_MAX_CHAR_LENGTH 256
#define IPP_MAX_CHAR_LENGTHJSON IPP_MAX_CHAR_LENGTH*10
#define IPP_MAX_COMMENT_LENGTH 2560
#define IPP_MAX_EXTRA_PAC_LENGTH 71
/**IPP 空调设备功能码-温度  */
#define IPP_AC_TMP              1

/**IPP 空调设备功能码-风速  */
#define IPP_AC_FUNSPEED         2
/**IPP 空调设备功能码-工作模式  */
#define IPP_AC_MODE             4
/**IPP 空调设备功能码-风向  */
#define IPP_AC_FUNDIRECTION_V   8

/**IPP 空调设备功能码-风向  */
#define IPP_AC_FUNDIRECTION_H   16
/**IPP 空调设备功能码-除湿  */
#define IPP_AC_DRYER            32
/**IPP 空调设备功能码-加热  */
#define IPP_AC_HOT              64
/**IPP 空调设备功能码-电源  */
#define IPP_AC_Power            128

/**IPP 冰箱设备功能码-冷藏室温度  */
#define IPP_IB_COLDTMP          1
/**IPP 冰箱设备功能码-冷藏室温度  */
#define IPP_IB_FREEZETMP        2
/**IPP 冰箱设备功能码-冷冻室温度  */
#define IPP_IB_VARIABLETMP      4
/**IPP 冰箱设备功能码-食品识别  */
#define IPP_IB_FOODS            8
/**IPP 冰箱设备功能码-电源  */
#define IPP_IB_Power            16

#define IPP_DMR_SETSTATE        1
#define IPP_DMR_SEEK            2
#define IPP_DMR_SETVOL          4
#define IPP_DMR_GETMEDIAINFO    8
#define IPP_DMR_SETURI          16
#define IPP_DMR_GETTIME         32




#define IPP_TV_SETCHANNELADD    1
#define IPP_TV_SETCHANNELMINUTE 2
#define IPP_TV_SETVOLUMEADD     (2<<2)
#define IPP_TV_SETVOLUMEMINUTE  (2<<3)
#define IPP_TV_SETVOLMODE       (2<<4)
#define IPP_TV_SETPICMODE       (2<<5)
#define IPP_TV_SETMUTE          (2<<6)
#define IPP_TV_SET3D            (2<<7)
#define IPP_TV_SET3DDEEP        (2<<8)
#define IPP_TV_SETKEY           (2<<9)
#define IPP_TV_SETSIGNALSRC     (2<<10)
#define IPP_TV_GETDISPLAY       (2<<11)
#define IPP_TV_Power            (2<<12)
#define IPP_TV_GETPROGRAM       (2<<13)
#define IPP_TV_GETCHANNELID     (2<<14)
#define IPP_TV_GETCHANNELNAME   (2<<15)
#define IPP_TV_SETINPUTSTRING   (2<<16)
#define IPP_TV_SETMOUSE         (2<<17)

#define IPP_DEVICE_TV           0x0101
#define IPP_DEVICE_DMR          0x0104

#define IPP_DEVICE_IB           0x0301

#define IPP_DEVICE_AC           0x0501
		/////////////////////@@@@@@@@@@@@@@@@@@///////////////////////////////////
#define IPP_DEVICE_HOCO_HEATER	0X0801
#define IPP_DEVICE_HOCO			0x0708
#define IPP_DEVICE_WATER_CLEAN	0X0807

#define IPP_DEVICE_EGBOX		0x400

//add by yw for eeprom
#define IPP_DEVICE_EEPROM		0X0901

#define IPP_HOCO_WINDLEVEL 		1
#define IPP_HOCO_ILLUMINATION 	2
#define IPP_HOCO_WINDBYSMOKE 	(2<<2)
#define IPP_HOCO_FIRELEVEL 			(2<<3)
#define IPP_HOCO_FIRETIME 				(2<<4)
#define IPP_HOCO_GETTIME 				(2<<5)
#define IPP_HOCO_GETSTATUS 			(2<<6)
#define IPP_HOCO_RECIPE 				(2<<7)
#define IPP_HOCO_SENDCODE 			(2<<8)
#define IPP_HOCO_CHANGECODE 		(2<<9)
#define IPP_HOCO_GETATTRIB 			(2<<10)
		/////////////////////@@@@@@@@@@@@@@@@@@///////////////////////////////////

#define IPP_DEVICE_POWER        0x0901
#define IPP_DEVICE_LIGHT        0x0904
#define IPP_DEVICE_CURTAIN      0x0907

#define fnGetFunIndexByFunID(ID)   ((int)(log(ID)/log(2)) )

void log_null();
////////////////////@@@@@@@@@@@@@@@@@@@////////////////////////////////////////

#define APP_FRAME_DEVICE_SEARCH 0x01//设备搜索消息
#define APP_FRAME_DEVICE_ONLINE 0x02//设备在线宣告消息
#define APP_FRAME_GET_DEVICE_XML 0x03//获取设备描述文件消息
#define APP_FRAME_GET_DEVICE_XML_ACK 0x04//返回设备描述文件消息
#define APP_FRAME_SET 0x05//功能调用请求消息
#define APP_FRAME_SET_ACK 0x06//功能调用响应消息
#define APP_FRAME_GET 0x07//状态获取请求消息
#define APP_FRAME_GET_ACK 0x08//状态获取响应消息
#define APP_FRAME_STATUS_SET 0x09//状态设置请求消息
#define APP_FRAME_STATUS_SET_ACK 0x0A//状态设置响应消息
#define APP_FRAME_SUBSCRIBE 0x0B//事件订阅请求消息
#define APP_FRAME_SUBSCRIBE_ACK 0x0C//事件订阅响应消息
#define APP_FRAME_SUBSCRIBE_CANCEL 0x0D//事件订阅取消消息
#define APP_FRAME_EVENT_NOTICE 0x0F//事件通知消息
#define APP_FRAME_HEART 0xEE//0xEE	心跳消息
#define APP_FRAME_DEVICE_OFFLINE 0xEF//设备离线宣告消息

#define APP_FRAME_COMMON_EVENT 0x88
////////////////////@@@@@@@@@@@@@@@@@@@////////////////////////////////////////


//#define APP_FRAME_SET_ACK 0x08
#define APP_FRAME_GET_STATE 0x06
#define APP_FRAME_UPDATE_DEVICEEVENT 0x09
#define APP_FRAME_RETURN_DEVICEEVENT 0x0A
#define APP_FRAME_NET_HEART 0XEE
#define APP_FRAME_NET_ERROR 0xFF

#define AIIP_LOG

//ios去掉log,便于调试
#ifdef IOS
#undef AIIP_LOG
#endif

#ifdef AIIP_LOG
#define LOG_TAG "IPPCore"

#ifdef ANDROID
#define LOGV(...) log_null()//__android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) log_null()//__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else
#define LOGV printf
#define LOGD printf
#define LOGI printf
#define LOGE printf
#define LOGW printf

#endif

#else

#define LOGV(...) log_null()
#define LOGD(...) log_null()
#define LOGI(...) log_null()
#define LOGE(...) log_null()
#define LOGW(...) log_null()

#endif

#define IPP_INT8    0x01
#define IPP_UINT8   0x02
#define IPP_INT16   0x03
#define IPP_UINT16  0x04
#define IPP_INT32   0x05
#define IPP_UINT32  0x06
#define IPP_FLOAT   0x07
#define IPP_STRING  0x08
#define IPP_HHMMSS 0x09
#define IPP_YYMMDD 0x0A
#define IPP_UINT32ARRAY 0x0B
#define IPP_BINARY 0X0C
#define IPP_DTVCHANNELTYPE 0xa1
#define IPP_DTVODERLIST 0xa2
#define IPP_IBDOORSSTATUS 0xb2
/////////////////////@@@@@@@@@@@@@@@@@@///////////////////////////////////
#define IPP_DTIME 0x0D
#define IPP_LIST 0x0E
/////////////////////@@@@@@@@@@@@@@@@@@///////////////////////////////////
#endif /* IPPFUNCTION_H_ */
