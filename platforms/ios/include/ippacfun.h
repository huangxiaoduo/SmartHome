/*
 * ipptvfun.h
 *
 *  Created on: 2012-9-29
 *      Author: jingyu.wang
 */

#ifndef IPPACFUN_H_
#define IPPACFUN_H_
/**
 * 空调风速模式
 */
typedef enum acSpeedMode {
	sm_auto = 0x01, //自动  0x01
	sm_weak = 0x02, //低风  0x02
	sm_normal = 0x03, //中风  0x03
	sm_strong = 0x04, //高风  0x04
	sm_storm = 0x05
//强力风 0x05

} ACSpeedMode;
typedef enum acSwitchMode {
	acopen = 0x01, acclose = 0x00
} ACSwitchMode;


//czb
typedef enum acSetSucceed{
	succeed = 0x01, failure = 0x00
}ACSetSuccess;

typedef enum acAirQualityLevel {
	good = 0x00, acnormal = 0x01, bad = 0x02
} ACAirQualityLevel;

/*
 * 空调工作模式
 */
typedef enum acWorkMode {
	wm_hot = 0x01, // 制热
	wm_cold = 0x02, // 制冷
	wm_dry = 0x03, // 除湿
	wm_fan = 0x04, // 送风
	wm_auto = 0x05
// 自动
} ACWorkMode;
typedef enum acSmartMode {
	wm_quxiao = 0x0, // 制热
	wm_dizao = 0x01, // 制冷
	wm_jieneng = 0x02, // 除湿
	wm_ganguang = 0x03, // 送风
	wm_rengong = 0x04
// 自动
} ACSmartMode;




typedef enum acWindMode {
	wm_cancel = 0x0, // 取消
	wm_true = 0x01, // 风随人动
	wm_false = 0x02, // 风逆人动

// 自动
} ACWindMode;

//*********************2014-2-10**add by czb*****//

typedef enum acWifiMode{
	can_not_get = 0x00, //无法获取
	ACAP  = 0x01,         //AP
	ACSTA = 0x02,         //STA
}ACWifiMode;

//***2014.04.15 zenglin**********//
typedef enum acFilterState{
	FILTER_STATE_CLEAN = 0x00, //滤网清洁
	FILTER_STATE_DIRTR_LITTLE = 0x01, //滤网有一点脏
	FILTER_STATE_DIRTR = 0x02 //滤网很脏
}ACFilterState;

typedef enum acNobodyState{
	AC_NO = 0x00, //没人
	AC_YES = 0x01 //有人
}ACNobodyState;

typedef enum acFilterMode{
	REMAIN_CANCEL	 = 0x00, //不提醒
	REMAIN_APP = 0x01, //APP提醒
	REMAIN_MSG = 0x02, // 短信提醒
}ACFilterMode;

typedef enum acFilterTime{
	FILTER_TIME_24 = 24, //24小时提醒
	FILTER_TIME_48 = 48, //48小时提醒
	FILTER_TIME_72 = 72 //72小时提醒
}ACFilterTime;

//typedef enum acVipModeSector{
//	SECTOR_1 = 0x01,
//	SECTOR_2 = 0x02,
//	SECTOR_3 = 0x03,
//	SECTOR_4 = 0x04
//}ACVipModeSector;

typedef enum acVipModePeople{
	NONE  = 0x00, //未设置
	ADULT = 0x01, //大人模式
	CHILD = 0x02 //小孩模式
}ACVipModePeople;
//****************************//
int fnACSetResetFilterReplaceTime(int id, int mode);
int
fnACSetPowerMode(int dev, int mode);
/**
 * 同步设置空调温度
 *
 * @param temp
 *            : 温度值
 * @return true :成功返回true，失败返回false
 */

int fnACSetTemprature(int dev, double temp);

/**
 * 同步设置空调温度
 *
 * @param temp
 *            : 温度值
 * @return true :成功返回true，失败返回false
 */

int fnACSetTempratureInt(int dev, int temp);

/**
 * 同步设置空调风速
 *
 * @param mode
 *            : 风速模式
 * @return true :成功返回true，失败返回false
 */
int fnACSetFanSpeedMode(int dev, ACSpeedMode mode);

/**
 * 同步设置空调水平风向
 *
 * @param mode
 *            : 水平风向模式
 * @return true :成功返回true，失败返回false
 */

int fnACSetFanDirectionHMode(int dev, ACSwitchMode mode);

/**
 * 同步设置空调垂直风向
 *
 * @param mode
 *            : 垂直风向模式
 * @return true :成功返回true，失败返回false
 */
int fnACSetFanDirectionVMode(int dev, ACSwitchMode mode);
/**
 * 同步设置空调除湿
 *
 * @param mode
 *            : 除湿模式
 * @return true :成功返回true，失败返回false
 */
//FIXME: 除湿是工作模式中的一种
//int fnACSetDryerMode(int dev, int mode);
/**
 * 同步设置空调辅热
 *
 * @param mode
 *            : 温度值
 * @return true :成功返回true，失败返回false
 */
int fnACSetAsistentHot(int dev, ACSwitchMode mode);

/**
 * 同步设置空调工作模式 (制冷，制热）
 *
 * @param mode
 *            : 工作模式
 * @return true :成功返回true，失败返回false
 */
int fnACSetWorkMode(int dev, ACWorkMode mode);
/**
 * 获取空调温度
 *
 *
 *
 * @return 返回空调温度
 */
int fnACGetTemprature(int dev,double* ret);

/**
 * 获取空调温度
 *
 *
 *
 * @return 返回空调温度
 */
int fnACGetTempratureInt(int dev,int* ret);

/**
 * 获取空调风速模式
 *
 *
 *
 * @return 返回空调风速模式
 */
ACSpeedMode fnACGetFunSpeedMode(int dev);
/**
 * 获取空调风向模式
 *
 *
 *
 * @return 返回空调风向模式
 */
ACSwitchMode fnACGetFanDirectionHMode(int dev);
/**
 * 获取空调风向模式
 *
 *
 *
 * @return 返回空调风向模式
 */
ACSwitchMode fnACGetFanDirectionVMode(int dev);
/**
 * 获取空调辅热模式
 *
 *
 *
 * @return 返回空调辅热模式
 */
ACSwitchMode fnACGetAsistentHot(int dev);
/**
 * 获取空调工作模式
 *
 *
 *
 * @return 返回空调工作模式
 */
ACWorkMode
fnACGetWorkMode(int dev);

/**
 * 获取设备电源模式
 *
 *
 * @return 返回设备电源模式
 */
ACSwitchMode
fnACGetPowerMode(int dev);

int fnACSetFullAutomatic(int dev, ACSwitchMode mode);//全自动
/**
 * 获取自适应模式开关
 *
 * 参数
 * 无
 *
 * 返回值
 * 0——未锁定
 * 1——锁定
 */
int fnACGetAdapterMode(int id);
/**
 * 获取儿童踢被状态
 *
 * 参数
 * 无
 *
 * 返回值
 * 0——未踢被
 * 1——踢被
 */
int fnACGetChildKickQuilt(int id);
/**
 * 获取儿童锁定状态
 *
 * 参数
 * 无
 *
 * 返回值
 * 0——未锁定
 * 1——锁定
 */
int fnACGetChildLockMode(int id);
/**
 * 获取红外阵列参数
 *
 * 参数
 * 无
 *
 * 返回值
 *
 * char
 */
char* fnACGetIRArrayParameters(int id);
//设置空气自动清洁开启
int fnACSetAutoAirFresh(int id, int onoff);
//获取空气自动清洁状态
int fnACGetAutoAirFresh(int id);
//设置空气自动清洁运行时间
int fnACSetAirFreshTime(int id, float* value);
//获取空气自动清洁运行时间
float* fnACGetAirFreshTime(int id);
//获取空气自动清洁运行剩余时间
int fnACGetAirFreshLastTime(int id);
//设置自启动PM2.5门限
int fnACSetAutoPMRange(int id, int value);
//获取自启动PM2.5门限
int fnACGetAutoPMRange(int id);
//获取PM2.5值
int fnACGetPMLevel(int id);
/**
 * 获取功能状态 0x0565
 *
 * 参数
 * 无
 *
 * 返回值
 *
 * char
 */
char* fnACGetFunctionStatus(int id);
int fnACSetFreshAir(int dev, ACSwitchMode mode);//空气清新
int fnACSetSleep(int dev, ACSwitchMode mode);//睡眠
int fnACSetAntiCondensation(int dev, ACSwitchMode mode);//防凝露
int fnACSetTimingPowerOnStatus(int dev, ACSwitchMode mode);//定时开机状态
int fnACSetTimingShutDonwStatus(int dev, ACSwitchMode mode);//定时关机状态
int fnACSetPowerOnTime(int dev, int time);//定时开机状态
int fnACSetShutDonwTime(int dev, int time);//定时关机时间
int fnACSetWindAsPeopleMove(int dev, ACWindMode mode);//风随人动


int fnACSetIntelligentMode(int dev, ACSwitchMode mode);//智能模式



int fnACSetResetFilterReplaceTime( int dev, int mode);
int fnACSetWIFISSID(int dev, char* ssid,int length);

int fnACSetWIFIPWD( int dev, char* pwd,int length);

int fnACSetActivatonCode( int dev, char* pwd,int length);

ACSwitchMode fnACGetFullAutomatic(int dev);//全自动
ACSwitchMode fnACGetFreshAir(int dev);//空气清新
ACSwitchMode fnACGetSleep(int dev);//睡眠
ACSwitchMode fnACGetAntiCondensation(int dev);//防凝露
ACSwitchMode fnACGetTimingPowerOnStatus(int dev);//定时开机状态
ACSwitchMode fnACGetTimingShutDonwStatus(int dev);//定时关机状态
int fnACGetPowerOnTime(int dev);//定时开机状态  // 0x00SSMMHH;
int fnACGetShutDonwTime(int dev);//定时关机时间// 0x00SSMMHH;
ACSwitchMode fnACGetWindAsPeopleMove(int dev);//风随人动
int fnACGetRoomTemperature(int dev,double* ret);//室内温度
int fnACGetRoomTemperatureInt(int dev,int* ret);//室内温度
int fnACGetElecCurrent(int dev,double* ret);//电流值
int fnACGetElecCurrentInt(int id, int* ret);

int fnACGetTotalPower(int dev);//总功
int fnACGetAvaragePower(int dev);//功率


int fnACGetAirQuality(int dev);//空气质量
int fnACGetIllumination(int dev);//光照
int fnACGetHumidity(int dev);//湿度
ACSwitchMode fnACGetIntelligentMode(int dev);//智能模式
ACAirQualityLevel fnACGetAirQualityLevel(int dev);//空气质量等级
int fnACGetFilterReplaceTime(int dev);//滤网更换剩余时间
double fnACGetOutdoorTemperature(int dev,double* ret);//室外温度
int fnACGetOutdoorTemperatureInt(int dev,int* ret);//室外温度



//******************2014-2-10 add by czb*************************//
/**
 * 获取空调wifi模式
 * @return 返回空调wifi模式
 */
ACWifiMode fnACGetWIFIMode(int id);

/**
 * 获取低噪状态
 * @return 返回低噪状态开关值
 */
ACSwitchMode fnACGetLowSignalNoise(int id);
/**
 * 获取节能状态开关
 *
 *
 *
 * @return 返回获取节能状态开关值
 */
ACSwitchMode fnACGetEnergySaving(int id) ;
/**
 * 获取光感状态开关
 *
 *
 *
 * @return 返回获取光感状态开关值
 */
ACSwitchMode fnACGetLightSensation(int id);
/**
 * 获取人工状态开关
 * @return 返回获取人工状态开关值
 */
ACSwitchMode fnACGetManualWork(int id);
/**
 * 获取无人状态开关
 * @return 返回获取无人状态开关值
 */
ACSwitchMode fnACGetManualWork(int id);
/**
 * 获取定时开机重复
 * @return 返回获取定时开机重复开关值
 */
ACSwitchMode fnACGetTimingPowerOn(int id);
/**
 * 获取定时关机重复
 * @return 返回获取定时关机重复开关值
 */
ACSwitchMode fnACGetTimingPowerOff(int id);
/**
 * 获取实际电加热
 * @return 返回获取实际电加热开关值
 */
ACSwitchMode fnACGetActualAssistentHot(int id);
/**
 * 报警摄像头开关状态
 * @return 报警摄像头开关状态开关值
 */
ACSwitchMode fnACGetAlarmCameralSwitchState(int id);
/**
 * 报警时段结束
 * @return 报警时段结束值
 */
int fnACGetAlarmTimeEnd(int id);
/**
 * 报警时段开始
 * @return 报警时段开始值
 */
int fnACGetAlarmTimeBegin(int id);
/**
 * 联网低耗模式开关状态
 * @return 联网低耗模式开关状态开关值
 */
ACSwitchMode fnACGetConnectedLowConsumptionMode(int id);
/**
 * 获取设备电量
 *
 *
 * @return 返回设备设备电量
 */
double fnACGetPower(int id);

/**
 * 获取设备电量
 *
 *
 * @return 返回设备设备电量
 */
int fnACGetPowerInt(int id);

/**
 * 获取空调版本
 *
 *
 *
 * @return 返回空调版本
 */
char* fnACGetType(int id);
/**
 * 获取空调序列号
 *
 *
 *
 * @return 返回空调序列号
 */
char* fnACGetSerialNumber(int id);

/**
 * 获取空调Soc版本
 *
 *
 *
 * @return 返回空调Soc版本
 */
char* fnACGetSocVersion(int id);
/**
 * 获取空调软件版本
 *
 *
 *
 * @return 返回空调软件版本
 */
char* fnACGetSoftwareVersion(int id);
/**
 * 获取空调软件版本
 *
 *
 *
 * @return 返回空调软件版本
 */
char* fnACGetSoftwareVersion(int id);
/**
 * 获取空调摄像头ip
 *
 *
 *
 * @return 返回空调摄像头ip
 */
char* fnACGetCameraIP(int id);
/**
 * 设置空调低噪开关
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetLowSignalNoise(int id, ACSwitchMode onoff);
/**
 * 设置空调节能开关
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetEnergySaving(int id, ACSwitchMode onoff);
/**
 * 设置空调光感开关
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetLightSensation(int id, ACSwitchMode onoff);
/**
 * 设置空调人工开关
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetManualWork(int id, ACSwitchMode onoff);
/**
 * 获取无人状态开关
 * @return 返回获取无人状态开关值
 */
ACSwitchMode fnACGetUNManed(int id);
/**
 * 设置空调无人开关
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetUNManed(int id, ACSwitchMode onoff);
/**
 * 设置空调定时开机重复
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetTimingPowerOn(int id, ACSwitchMode onoff);

/**
 * 设置空调定时开机重复
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetTimingPowerOff(int id, ACSwitchMode onoff);
/**
 * 设置空调定时关机
 *
 * 机重复
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetActualAssistentHot(int id, ACSwitchMode onoff);
/**
 * 设置空调报警摄像头开关状态
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetAlarmCameralSwitchState(int id, ACSwitchMode onoff);
/**
 * 设置空调报警时段开始
 *
 * @param mode
 *            : 报警时段开始time
 * @return true :成功返回true，失败返回false
 */
int fnACSetAlarmTimeBegin(int id, int mtime);
/**
 * 设置空调报警时段end
 *
 * @param mode
 *            : 报警时段end time
 * @return true :成功返回true，失败返回false
 */
int fnACSetAlarmTimeEnd(int id, int mtime);
/**
 * 语音提醒开关状态
 *
 * @param
 *            : 开关
 * @return true :成功返回true，失败返回false
 */
int fnACSetVoiceRemindSwitchState(int id, ACSwitchMode onoff);
/**
 *联网低耗模式开关状态
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetConnectedLowConsumptionMode(int id, ACSwitchMode onoff);
/**
 *复位WIFI AP
 *
 * @param mode
 *            : 开关状态
 * @return true :成功返回true，失败返回false
 */
int fnACSetResetWifiAP(int id, ACSetSuccess value);
/**
 *传送语音信息
 *
 * @param
 * @return true :成功返回true，失败返回false
 */
int fnACSetTransferVoice(int id, char* content, int length);

//*****************************************************************2014.04.15     zenglin*****************************************************************************//
/**
 * 设置自适应模式开关
 *
 * 参数 onoff
 * 0——关
 * 1——开
 *
 * 返回值
 * 0——成功
 * 1——失败
 */
ACSetSuccess fnACSetAdapterMode(int id, ACSwitchMode onoff);
/**
  * 获取空调滤网的清洁程度
  *
  * 参数
  * 无
  *
  * 返回值
  * FILTER_STATE_CLEAN			0x00 滤网清洁
  * FILTER_STATE_DIRTR_LITTLE	0x01 滤网有一点脏
  * FILTER_STATE_DIRTR			0x02 滤网很脏
  *
  */
 int fnACGetFilterState(int id);

 /**
  * 获取房间无人状态
  *
  * 参数
  * 无
  *
  * 返回值
  * 0--无人
  * 1--有人
  *
  */
 int fnACGetNobodyState(int id);


 /**
  * 获取空调滤网的提醒方式
  *
  * 参数
  * 无
  *
  * 返回值
  * REMAIN_CANCEL		0x00 不提醒
  * REMAIN_APP			0x01 APP提醒
  * REMAIN_MSG			0x02 短信提醒
  *
  */
 int fnACGetFilterMode(int id);

 /**
  * 设置空调滤网的提醒方式
  *
  * 参数
  * value
  * REMAIN_CANCEL		0x00 不提醒
  * REMAIN_APP			0x01 APP提醒
  * REMAIN_MSG			0x02 短信提醒
  *
  * 返回值
  * OK - 0x01 成功
  * FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetFilterMode(int id, ACFilterMode value);

 /**
  * 设置空调滤网提醒时间
  *
  * 参数
  * value
  * FILTER_TIME_24		24 24小时提醒
  * FILTER_TIME_48		48 48小时提醒
  * FILTER_TIME_72		72 72小时提醒
  *
  * 返回值
  * OK - 成功
  * FAILED - 失败
  *
  */
 ACSetSuccess fnACSetFilterTime(int id, ACFilterTime value);

 /**
  * 获取空调滤网的提醒方式
  *
  * 参数
  * 无
  *
  * 返回值
  * FILTER_TIME_24		24 每24小时提醒
  * FILTER_TIME_48		48 每48小时提醒
  * FILTER_TIME_72		72 每72小时提醒
  *
  */
 int fnACGetFilterTime(int id);

 /**
  * 设置空调修正风速的开关
  *
  * 参数
  * onoff
  * WIND_FIXWIND_OFF		0x00 关闭
  * WIND_FIXWIND_ON		0x01 打开
  *
  * 返回值
  * OK - 0x01 成功
  * FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetFixWindMode(int id, ACSwitchMode onoff);

 /**
  * 获取空调修正风速的开关
  *
  * 参数
  * 无
  *
  * 返回值
  * WIND_FIXWIND_OFF		0x00 关闭
  * WIND_FIXWIND_ON		0x01 打开
  *
  */
 int fnACGetFixWindMode(int id);

 /**
  * 设置空调儿童保护模式
  *
  * 参数
  * onoff
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  * 返回值
  * OK - 0x01 成功
  * FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetChildPrect(int id, ACSwitchMode onoff);

 /**
  * 获取空调儿童保护模式
  *
  * 参数
  * 无
  *
  * 返回值
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  */
 int fnACGetChildPrect(int id);

 /**
  * 设置空调动态分区模式
  *
  * 参数
  * onoff
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  * 返回值
  * OK - 0x01 成功
  * FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetComfortAdj(int id, ACSwitchMode onoff);

 /**
  * 获取空调动态分区模式
  *
  * 参数
  * 无
  *
  * 返回值
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  */
 int fnACGetComfortAdj(int id);

 /**
  * 设置空调家庭聚会模式
  *
  * 参数
  * onoff
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  * 返回值
  * RETURN_OK - 0x01成功
  * RETURN_FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetPopDynident(int id, ACSwitchMode onoff);

 /**
  * 获取空调家庭聚会模式
  *
  * 参数
  * 无
  *
  * 返回值
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  */
 int fnACGetPopDynident(int id);

 /**
  * 设置空调VIP模式
  *
  * 参数
  * onoff
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  * 返回值
  * RETURN_OK - 0x01 成功
  * RETURN_FAILED - 0x00 失败
  *
  */
 ACSetSuccess fnACSetVipMode(int id, ACSwitchMode onoff);

 /**
  * 获取空调VIP模式
  *
  * 参数
  * 无
  *
  * 返回值
  * MODE_OFF		0x00 关闭
  * MODE_ON			0x01 打开
  *
  */
 int fnACGetVipMode(int id);

// /**
//  * 设置空调VIP模式各分区的模式
//  *
//  * 参数
//  * sector
//  * 1/2/3/4/各个分区号
//  * 参数
//  * peoplecategory
//  * 0--未设置
//  * 1--大人模式
//  * 2--小孩模式
//  *
//  * 返回值
//  * OK - 成功
//  * FAILED - 失败
//  *
//  */
//ACSetSuccess fnACSetVipModeAngle(int id, ACVipModeSector sector, ACVipModePeople peoplecategory);
//
// /**
//  * 获取空调VIP模式第一分区的模式
//  *
//  * 参数
//  * sector
//  * 1/2/3/4/各个分区号
//  *
//  * 返回值
//  * 0--未设置
//  * 1--大人模式
//  * 2--小孩模式
//  *
//  */
//int fnACGetVipModeAngle(int id, ACVipModeSector sector);

/**
* 设置空调VIP模式1分区的模式
*
* 参数
*
* 参数
* peoplecategory
* 0--未设置
* 1--大人模式
* 2--小孩模式
*
* 返回值
* OK - 成功
* FAILED - 失败
*
*/
ACSetSuccess fnACSetVipModeAngle1(int id, ACVipModePeople peoplecategory);

/**
* 获取空调VIP模式第1分区的模式
*
* 参数
*
*
* 返回值
* 0--未设置
* 1--大人模式
* 2--小孩模式
*
*/
int fnACGetVipModeAngle1(int id);

/**
* 设置空调VIP模式2分区的模式
*
* 参数
*
* 参数
* peoplecategory
* 0--未设置
* 1--大人模式
* 2--小孩模式
*
* 返回值
* OK - 成功
* FAILED - 失败
*
*/
ACSetSuccess fnACSetVipModeAngle2(int id, ACVipModePeople peoplecategory);

/**
* 获取空调VIP模式第2分区的模式
*
* 参数
*
*
* 返回值
* 0--未设置
* 1--大人模式
* 2--小孩模式
*
*/
int fnACGetVipModeAngle2(int id);


/**
 * 设置空调VIP模式3分区的模式
 *
 * 参数
 *
 * 参数
 * peoplecategory
 * 0--未设置
 * 1--大人模式
 * 2--小孩模式
 *
 * 返回值
 * OK - 成功
 * FAILED - 失败
 *
 */
ACSetSuccess fnACSetVipModeAngle3(int id, ACVipModePeople peoplecategory);

/**
 * 获取空调VIP模式第3分区的模式
 *
 * 参数
 *
 *
 * 返回值
 * 0--未设置
 * 1--大人模式
 * 2--小孩模式
 *
 */
int fnACGetVipModeAngle3(int id);

/**
  * 设置空调VIP模式4分区的模式
  *
  * 参数
  *
  * 参数
  * peoplecategory
  * 0--未设置
  * 1--大人模式
  * 2--小孩模式
  *
  * 返回值
  * OK - 成功
  * FAILED - 失败
  *
  */
ACSetSuccess fnACSetVipModeAngle4(int id, ACVipModePeople peoplecategory);

 /**
  * 获取空调VIP模式第4分区的模式
  *
  * 参数
  *
  *
  * 返回值
  * 0--未设置
  * 1--大人模式
  * 2--小孩模式
  *
  */
int fnACGetVipModeAngle4(int id);


/**
 * 语音提醒开关状态
 * @return 语音提醒开关状态开关值
 */
ACSwitchMode fnACGetVoiceRemindSwitchState(int id);

/**
 * 设置系统时间
 * @parm:
 *         time
 *  @return 返回时间值
 */
int fnACSetSystermTime(int id,int mtime);

/**
 * 设置动态分区角度
 *
 * 参数
 * int angle
 *
 * 返回值
 * RETURN_OK - 0x01 成功
 * RETURN_FAILED - 0x00 失败
 *
 */
ACSetSuccess fnACSetComfortAdjAngle(int id, int angle);

/**
 * 设置动态分区距离
 *
 * 参数
 * int distance
 *
 *
 * 返回值
 * OK - 成功
 * FAILED - 失败
 *
 */
ACSetSuccess fnACSetComfortAdjDistance(int id, int distance);

/**
 * 设置自适应模式开关
 *
 * 参数 onoff
 * 0——关
 * 1——开
 *
 * 返回值
 * 0——成功
 * 1——失败
 */
ACSetSuccess fnACSetAdapterMode(int id, ACSwitchMode onoff);

//ghy----20150706 fngetVoiceType

int fnsetVoiceType(int id,char* VoiceType,int VoiceTypelen);
int fnSetVoiceVolume(int id,int VoiceVolume);
int fnSetVoiceSwitch(int id,int VoiceSwitch);//
char* fnGetVoiceType(int id);
int fnGetVoiceVolume(int id);
int fnGetVoiceSwitch(int id);
void fnSendCommand(int id, const char *string, int length);













//*********************************//




#endif /* IPPTVFUN_H_ */
