/*
 * ippstruct.h
 *
 *  Created on: 2012-9-28
 *      Author: chobit
 */

#ifndef IPPSTRUCT_H_
#define IPPSTRUCT_H_

#ifndef __cplusplus

#endif
#include "ippfunction.h"
#include "ch_home_transplant.h"
#include <pthread.h>
//#include "../relative/school.h"
//#include "../relative/area.h"
#define FUN_ID 64
#define IPP_UUID_LENGTH 128

typedef int
(*fnSet)();
typedef struct {
	uint8 doorNum[16];
	uint8 doorOnOff[16];
} IBDoorStatus, *PIBDoorStatus;
typedef struct {
	uint8 modetype;
	uint8 onoff;
} IBWorkMode, *PIBWorkMode;
typedef struct {
	uint16 onoff;
	uint8 shours;
	uint8 ssecond;
	uint8 sminute;
	uint8 ehours;
	uint8 esecond;
	uint8 eminite;

} TimeAccount, *PTimeAccount;
typedef struct {

	fnSet mfnSets[FUN_ID];
	int mFnSize;

} DeviceFun, *PDeviceFun;

typedef struct {
	short x;
	short y;
	short action;

} Mouse;
typedef struct {
	int mYears;
	int mMonths;
	int mDays;
	int mWeekDay;

} UTCDate, *PUTCDate;

typedef struct {
	int mHours;
	int mSeconds;
	int mMinutes;

} UTCTime, *PUTCTime;

typedef struct {
	//int mOperation;

	char channelName[IPP_MAX_CHAR_LENGTH];
	//需要想办法获取
	char programmerName[IPP_MAX_CHAR_LENGTH]; //多媒体已提供提供

	//下面2个时间对应多媒体 提醒时间 timer.mlStartNotifyTime
	UTCDate startNotifyDate; //需要时间转换
	UTCTime startNotifyTime; //需要时间转换
//	UTCTime durationTime; //需要时间转换
	//下面2个时间对应多媒体 提醒时间 timer.mlNotNotifyTime
	UTCDate endNotifyDate;
	UTCTime endNotifyTime;

	//多媒体里有，可能是标示，建议传输上
	int channelIndex;
	int eventIndex;
	//int type;
	//int sourceID;
	//int servicIndex;
//	int programNum;
//	char eventName[IPP_MAX_CHAR_LENGTH];

	//char strTriggerBroadCast[IPP_MAX_CHAR_LENGTH];

} IPPOrderChannel, *PIPPOrderChannel;

typedef struct {
//	int  mOperation;

	char channelName[IPP_MAX_CHAR_LENGTH];
	//需要想办法获取
	char programmerName[IPP_MAX_CHAR_LENGTH]; //多媒体已提供提供

	//下面2个时间对应多媒体 提醒时间 timer.mlStartNotifyTime
	char startNotifyDateTime[IPP_MAX_CHAR_LENGTH]; //需要时间转换

	//char durationTime[IPP_MAX_CHAR_LENGTH]; //需要时间转换
	//下面2个时间对应多媒体 提醒时间 timer.mlNotNotifyTime
	char endNotifyDateTime[IPP_MAX_CHAR_LENGTH];

	//多媒体里有，可能是标示，建议传输上
	int index;
	int type;
	int sourceID;
	int servicIndex;
	int programNum;
	char eventName[IPP_MAX_CHAR_LENGTH];

	char strTriggerBroadCast[IPP_MAX_CHAR_LENGTH];

} IPPRemoteOrderChannel, *PIPPRemoteOrderChannel;

typedef struct {
	int mEventID;
	UTCDate mStartDate;
	UTCTime mStartTime;
	UTCTime mDurationTime;
	char mEventName[96];
	char mShortText[64];
	//char mDetailText[IPP_MAX_CHAR_LENGTH];

} EPGEvent, *PEPGEvent;

typedef struct {
	int mChannelIndex;
	char mChanneName[32];
	int mServiceTpye;
	int mScramble;
	int mAudioMode;
	char mRate[8];
	int mBalenceVolume;
	int mLock;
	int mSkip;
	int mFav;
	int mEventNum;
	EPGEvent mEvent[0];

} DTVChannelInfo, *PDTVChannelInfo;

typedef struct {
	char mUsername[IPP_MAX_CHAR_LENGTH];
	unsigned int mUserID;
	unsigned int mID;
	unsigned int mType;
	unsigned int mCtrFlag;
	long long mFunctionID;

	PIPPNodeHead mUsers;
	char mName[IPP_MAX_CHAR_LENGTH];
	char mPosition[IPP_MAX_CHAR_LENGTH];
	char mAttrib[IPP_MAX_CHAR_LENGTH];
	char mUUID[IPP_MAX_CHAR_LENGTH];
	char status[IPP_MAX_CHAR_LENGTH];
	char keyinfo[IPP_MAX_CHAR_LENGTH];
	char sn[IPP_MAX_CHAR_LENGTH];
	char devicetype[IPP_MAX_CHAR_LENGTH];
	char deviceip[IPP_MAX_CHAR_LENGTH];
	//char mac[20];
	int mProtocol;
	void* mNet;
	int mOnlinestate; //设备上线状态
	int mSetAck;
	int mShow;
	pthread_mutex_t contentLok;

	//add by yw, for an ios crash
	pthread_t deviceOnlie_Pthread_id;
} IPPDevice, *PIPPDevice;
typedef struct {
	IPPDevice mBaseInfo;
	PDeviceFun mSetFun;
	double mTemprature;
	int mFanSpeedMode;

	int mDryerMode;
	int mAsistentHot;
	int mPowerMode;
	int mWorkMode;
	int mFanDirectionH;
	int mFanDirectionV;

	//czb  2014-2-10
	int mWifiMode;

	char mVersion[IPP_MAX_CHAR_LENGTH];
	char mSocVersion[IPP_MAX_CHAR_LENGTH];
	char mSerialNumber[IPP_MAX_CHAR_LENGTH];
	char mSoftwareVersion[IPP_MAX_CHAR_LENGTH];
	char mCameralIP[IPP_MAX_CHAR_LENGTH];

	int mLowSignalNoise;
	int mEnergySaving;
	int mLightSensation;
	int mManualWork;
	int mUNManed;
	int mTimingPowerON;
	int mTimingPowerOff;
	int mActualAssistentHot;
	int mAlarmCameralState;

	int mAlarmTimeBegin;
	int mAlarmTimeEnd;

	int mVoiceRemindSwitchState;
	int mConnectedLowConsumptionMode;
	double mGetPower;
	int mwifiAP;
//
	int SystermTime;
//	int mVoiceTransfer;//








	////////////////////

	int mFullAutomatic; //全自动
	int mFreshAir; //空气清新
	int mSleep; //睡眠
	int mAntiCondensation; //防凝露

	int mTimingPowerOnStatus; //定时开机状态
	int mPowerOnTime; //定时开机时间
	int mTimingShutDonwStatus; //定时关机状态
	int mShutDonwTime; //定时关机时间

	int mWindAsPeopleMove; //风随人动
	double mRoomTemperature; //室内温度
	double mElecCurrent; //电流值
	int mAirQuality; //空气质量
	int mIllumination; //光照
	int mHumidity; //湿度
	int mIntelligentMode; //智能模式
	int mAirQualityLevel; //空气质量等级
	int mFilterReplaceTime; //滤网更换剩余时间
	double mOutdoorTemperature; //室外温度
	int mAvaragePower; //平均功率
	int mTotalPower; //总功
	//********************************************2014.04.15   zenglin*************************************//
	int mFilterState; //空调滤网的清洁程度
	int mNobodyState;//房间无人状态
	int mFilterMode;//空调滤网的提醒方式
	int mFilterTime;//空调滤网的提醒时间
	int mFixWindMode;//空调修正风速的开关
	int mChildPrect;//空调儿童保护模式
	int mComfortAdj;//空调动态分区模式
	int mPopDynident;//空调家庭聚会模式
	int mVipMode;//空调VIP模式
	int mVipModeAngle[4];//空调VIP模式各分区的模式
//*****************************************2014.04.22              zenglin*****************************//
	char mIRlist[4096];//红外阵列参数
	int mChildKickQuilt; //儿童踢被参数
	int mChildLock;//锁定儿童参数
	int mAdapterMode;//自适应模式
//***********************************2014.04.29                  zenglin*******************************//
	int mAutoAirFresh;//空气自动清洁
	float mAirFreshTime;//空气自动清洁运行时间
	int mAirFreshLast;//空气自动清洁运行剩余时间
	int mAutoPMRange;//自动PM2.5门限
	int mPMLevel;//PM2.5值
	char mFunctionStatus[IPP_MAX_CHAR_LENGTH];//功能状态

	//ghy 20140706

	char mVoiceType[16];
	int mVoiceVolume;
	int mVoiceSwitch;


} IPPAC, *PIPPAC;
typedef struct {
	IPPDevice mBaseInfo;
	PDeviceFun mSetFun;
	int mPowerMode;
	int mVolume;
	int mMute;
	int mPictureMode;
	int mSoundMode;
	int mMode;

	int mChannelID;
	int mBrightNess;
	int mContrast;
	int mSignalSRC;
	int m3DDeep;
	int mSleep;
	int mZoomMode;

	char mDisplay[IPP_MAX_CHAR_LENGTH];
	char mChannelName[IPP_MAX_CHAR_LENGTH];
	char* data;
	int datalen;
	int mPicSock;
	PIPPNodeHead mEPGChannel;
	PIPPNodeHead mOderList;
	int epgtotalsize;
} IPPTV, *PIPPTV;

typedef struct {
	IPPDevice mBaseInfo;
	PDeviceFun mSetFun;
	unsigned char mPlayInfo[IPP_MAX_CHAR_LENGTH];
	unsigned char mURI[IPP_MAX_CHAR_LENGTH];
	//FIXME: playState 最好使用枚举型
	unsigned int mPlayState;
	unsigned int mTime;
	float mSpeed;
	unsigned int mVolume;
	unsigned int mDuraton;
} IPPDMR, *PIPPDMR;

typedef struct {
	IPPDevice mBaseInfo;
	PDeviceFun mSetFun;
	//FIXME: PowerMode 改为枚举型
	int mPowerMode;
	int mColdTemprature;
	int mFreezeTemprature;
	int mVariableTemprature;
	int mOutDoorTemprature;
	int mSensorColdTemprature;
	int mSensorFreezeTemprature;
	int mSensorVariableTemprature;
	IBDoorStatus mDoors;
	int mWorkMode[16];
	unsigned int mFoods[IPP_MAX_GOODS];
	unsigned int mLowTimeStart;
	unsigned int mLowTimeEnd;

} IPPIB, *PIPPIB;

typedef struct {

	PDeviceFun mSetFun;
} IPPEvent, *PIPPEvent;

typedef struct {
	PDeviceFun mSetFun;
} IPPEventMsg, *PIPPEventMsg;

typedef struct {
	PDeviceFun mSetFun;
} IPPVer, *PIPPVer;

typedef struct {
	PDeviceFun mSetFun;
} IPPHabit, *PIPPHabit;

typedef struct {
	fnSet mPush;
	fnSet mPop;

} IPPCtrlCoreFun, *PIPPCtrlFun;
typedef struct {
	int mcurver;
	int compatiblever;

} IPPVersion, *PIPPVersion;
typedef struct {
	PIPPCtrlFun mSetFun;
	IPPVersion mver;
	PIPPNodeHead mEvents;
	PIPPNodeHead mDevices;

} IPPCtrlCore, *PIPPCtrlCore;

typedef struct {

	unsigned char mVersion;

	unsigned short mFrameLength; //short int
	unsigned short mFramenum; //short int

	unsigned char mSrcID[16];
	unsigned char mDesID[16];
	unsigned char mSafeFrameType;

	unsigned char encrpytTag[6];

	unsigned char* mAppFrameData;
	unsigned int mAppFrameLength;
	unsigned char mDigitalSign[20];

} IPPMsg, *PIPPMsg;

extern const char* FAMILYROLENAME[10];
extern const char* FAMILYROLENAMEcn[10];

typedef struct familiRole {
	int id;
	char name[IPP_MAX_CHAR_LENGTH];
	char description[IPP_MAX_CHAR_LENGTH];
} FamilyRole, *PFamilyRole;

typedef struct {
	double longitude;
	double latitude;
} GPSPosition, *PGPSPosition;

typedef struct {
	char id[IPP_MAX_CHAR_LENGTH];
	//姓名
	char name[IPP_MAX_CHAR_LENGTH];
	//昵称
	char nickname[IPP_MAX_CHAR_LENGTH];
	//登录名
	char loginName[IPP_MAX_CHAR_LENGTH];
	//用户ID    通信协议适用的UUID
	char uuid[IPP_MAX_CHAR_LENGTH];
	//密码
	char password[IPP_MAX_CHAR_LENGTH];

	char callnum[IPP_MAX_CHAR_LENGTH];
	;
	char callname[IPP_MAX_CHAR_LENGTH];
	;

	char schoolinfo[IPP_MAX_CHAR_LENGTH];
	;
	char sexinfo[IPP_MAX_CHAR_LENGTH];
	;
	char ageinfo[IPP_MAX_CHAR_LENGTH];
	;
	char birthdayinfo[IPP_MAX_CHAR_LENGTH];
	;
	char signinfo[IPP_MAX_CHAR_LENGTH];
	;

	//性别
	uint8 sex;
	//家庭角色    爸爸、妈妈、儿子、女儿、爷爷、奶奶、孙儿、孙女、单身
	PFamilyRole role;
	//手机号码
	long long mobile;
	//毕业学校（小学）
//	School gradeSchool;
//	//毕业学校（初中）
//	School juniorSchool;
//	//毕业学校（高中）
//	School seniorSchool;
//	//毕业学校（大学）
//	School unversity;
//	//毕业学校（研究生）
//	School postgraduateUniv;
//	//籍贯
//	City nativePlace;
	//位置信息    坐标？
	GPSPosition position;

	char remark[IPP_MAX_CHAR_LENGTH];
} IPPUser, *PIPPUser;

typedef struct relationship {
	int id;
	char* name;
	char* decription;
} Relationship, *PRelationship;

typedef struct {
	int id; //编号
	IPPUser initiator; //发起者
	IPPUser receiver; //接收者
	Relationship relationship; //申请关系
} IPPEstablishRelationsRequest, *PIPPEstablishRelationsRequest;

typedef enum {
	Owner, User, Guest
} DeviceRelationship;

typedef struct {
	int id; //编号
	PIPPUser initiator; //发起者
	PIPPUser receiver; //接收者
	int deviceid; //关联设备
	DeviceRelationship relationship;
} IPPDeviceRelationsRequest, *PIPPDeviceRelationsRequest;

typedef struct {
	char* key;
	int valueType;
	char* value;
} IPPKeyValue, *PIPPKeyValue;
typedef struct {

	int mMsgID;
	char mFromID[IPP_MAX_CHAR_LENGTH];
	char mTargetID[IPP_MAX_CHAR_LENGTH];
	int mAutoDestroy;

	int mMsgClass;
	char mSendNickName[IPP_MAX_CHAR_LENGTH];
	char mReceiverName[IPP_MAX_CHAR_LENGTH];
	char mSendNum[IPP_MAX_CHAR_LENGTH];
	char mReceiverNum[IPP_MAX_CHAR_LENGTH];
	char mMsgTitle[IPP_MAX_CHAR_LENGTH];
	char mMsgTime[IPP_MAX_CHAR_LENGTH];
	char mMsgContent[IPP_MAX_CHAR_LENGTH];
	char mAuthDevSN[IPP_MAX_CHAR_LENGTH];
	char mTimeTriger[IPP_MAX_CHAR_LENGTH];
	int mAuthLevel;

} IPPNotifyMsg, *PIPPNotifyMsg;
typedef struct {

	int id;
	char msgtype[IPP_MAX_CHAR_LENGTH];
	char msg4[IPP_MAX_CHAR_LENGTH];
	int msg4id;
	char msg2[IPP_MAX_CHAR_LENGTH];
	char msgtitle[IPP_MAX_CHAR_LENGTH];
	char msginfo[IPP_MAX_CHAR_LENGTH];
	char dateinfo[IPP_MAX_CHAR_LENGTH];
	int mAuthdevid;
	int mAuthlevel;

} IPPMsgTO, *PIPPMsgTO;

typedef struct {

	char firendnickname[IPP_MAX_CHAR_LENGTH];
	char friendid[IPP_MAX_CHAR_LENGTH];
	char friendphonenum[IPP_MAX_CHAR_LENGTH];
	char userid[IPP_MAX_CHAR_LENGTH];
	char onlinestate[IPP_MAX_CHAR_LENGTH];
	int friendship;
	PIPPNodeHead deviceauthto;
	PIPPNodeHead deviceauthfrom;

} IPPFriendTO, *PIPPFriendTO;

typedef struct {
	int id;
	char devicetype[IPP_MAX_CHAR_LENGTH];
	char sn[IPP_MAX_CHAR_LENGTH];
	char nickname[IPP_MAX_CHAR_LENGTH];
	char status[IPP_MAX_CHAR_LENGTH];
	char keyinfo[IPP_MAX_CHAR_LENGTH];
} IPPDeviceTO, *PIPPDeviceTO;
/*
 (r, g, m,Ts,Te, d, pri, a),
 resource r can be accessed by users in group g,
 using module m,
 in the time window from Ts to Te,
 on day of the week d,
 with priority pri
 and access mode a
 */

typedef struct {
	int id; //编号
	PIPPUser user; //用户
	int deviceType; //设备类型
	time_t timeStart; //开始时间
	time_t timeEnd; //结束时间
	int weekday; //星期几，可以是组合，位操作方式
	int priority; //优先级
	int accessMode; //访问模式，
	int functionNo; //功能编号
	PIPPKeyValue parameters; //功能参数数组，根据功能编号可以查到功能的参数数量
} IPPUserHabit, *PIPPUserHabit;

typedef enum {
	Monday = 0x01,
	Tuesday = 0x02,
	WednesDay = 0x04,
	ThursDay = 0x08,
	Friday = 0x10,
	Staturday = 0x20,
	Sunday = 0x40,
} WeekDay;

typedef struct {
	int id;
	char program[IPP_MAX_CHAR_LENGTH];
	char comment[IPP_MAX_COMMENT_LENGTH];
	PIPPUser submitUser;
	char submtTime[IPP_MAX_CHAR_LENGTH];
} IPPProgramComment, *PIPPProgramComment;

typedef struct {

	char mChannelName[IPP_MAX_CHAR_LENGTH];

	char mProgramName[IPP_MAX_CHAR_LENGTH];

	int mFavouriteRate;

} FavouriteProgram, *PFavouriteProgram;
/**——————————————————————————————————————
 * 智能烟灶
 *——————————————————————————————————————
 */
/**
 *
 */
typedef struct {
	unsigned int mFireLevel; //火力大小
	unsigned int mTimeStart; //开始时间
	unsigned int mTimeEnd; //结束时间
}IPPLOWCOTIME, *PIPPLOWCOTIME; //低成本定时时间段结构体

typedef struct {
	unsigned int size;
	IPPLOWCOTIME cotime[3];
}IPPLOWFIRETIME, *PIPPLOWFIRETIME; //低成本定时结构体

typedef struct {
	unsigned int mLeftFireStatus; //左灶火力状态
	unsigned int mRightFireStatus; //右灶火力状态
	IPPLOWFIRETIME mLeftTime; //左灶火力定时
	IPPLOWFIRETIME mRightTime; //右灶火力定时
	char recipe_left[128]; //左灶当前食谱
	char recipe_right[128]; //右灶当前食谱
	unsigned int mCleanMode;//清洁模式
	unsigned int mWindLevel[3]; //风力：0总 1左 2右
	unsigned int mIllumination; //照明
	unsigned int mSmokeLevel; //烟雾浓度
	unsigned int mWindBySmoke; //风随烟动
	unsigned int mErrorDetection; //故障监测
	unsigned int mAntiDryDetection[2];	//防干烧监测
	unsigned int mGasLeakDetection; //煤气泄漏监测
	unsigned int mHoodUsedTime; //烟机累计使用时间（小时）
	unsigned int mCookerUsedTime; //灶具累计使用时间（小时）
	unsigned int mSteamClean;//蒸汽洗
	unsigned int mWindSync;//风力同步开关
	unsigned int mAutoClean;//自动清洁开关

	unsigned int mLeftBanTimingOff;//左灶台是否禁止MCU端定时关火
	unsigned int mLeftTimingOffTime;//左灶台定时关火时间
	unsigned int mRightBanTimingOff;//右灶台是否禁止MCU端定时关火
	unsigned int mRightTimingOffTime;//右灶台定时关火时间
}IPPLOWHOCOSTATUS, *PIPPLOWHOCOSTATUS; //低成本烟灶所有状态结构体
/**
 *
 */
typedef struct{
	unsigned int mTimeZone; //时区
	unsigned int mYear; //年
	unsigned int mMouth; //月
	unsigned int mDay; //日
	unsigned int mHour; //时
	unsigned int mMinute; //分
	unsigned int mSecond; //秒
}IPPDTime, *PIPPDTime;

typedef struct {
	unsigned int mFireLevel; //火力大小
	IPPDTime mTimeStart; //开始时间
	IPPDTime mTimeEnd; //结束时间
}IPPCOTIME, *PIPPCOTIME; //定时时间段结构体

typedef struct {
	unsigned int size;
	IPPCOTIME cotime[10];
}IPPFIRETIME, *PIPPFIRETIME; //定时结构体

typedef struct {
	unsigned int mWindLevel[3]; //风力：0总 1左 2右
	unsigned int mIllumination; //照明
	unsigned int mWindBySmoke; //风随烟动
	unsigned int mSmokeLevel; //烟雾浓度
	unsigned int mErrorDetection; //故障监测
	unsigned int mUsedTime; //累计使用时间
} IPPHOOD, *PIPPHOOD; //烟机结构体

typedef struct {
	unsigned int mFireStatus; //火力状态
	IPPFIRETIME mTime; //火力定时
	unsigned int mErrorDetection; //故障监测
	unsigned int mAntiDryDetection; //防干烧监测
	unsigned int mGasLeakDetection; //煤气泄漏监测
	unsigned int mUsedTime; //累计使用时间
	char recipe[IPP_MAX_CHAR_LENGTH];//当前食谱
	unsigned int totaltime;//本次开火燃烧累计时间

} IPPCOOKER, *PIPPCOOKER; //燃气灶口结构体

typedef struct {
	unsigned int mLeftFireStatus; //左灶火力状态
	unsigned int mRightFireStatus; //右灶火力状态
	IPPFIRETIME mLeftTime; //左灶火力定时
	IPPFIRETIME mRightTime; //右灶火力定时
	char recipe_left[IPP_MAX_CHAR_LENGTH]; //左灶当前食谱
	char recipe_right[IPP_MAX_CHAR_LENGTH]; //右灶当前食谱
	unsigned int mCleanMode;
	unsigned int mWindLevel[3]; //风力：0总 1左 2右
	unsigned int mIllumination; //照明
	unsigned int mSmokeLevel; //烟雾浓度
	unsigned int mWindBySmoke; //风随烟动
	unsigned int mErrorDetection; //故障监测(相同)
	unsigned int mAntiDryDetection[2];	//防干烧监测
	unsigned int mGasLeakDetection; //煤气泄漏监测
	unsigned int mHoodUsedTime; //烟机累计使用时间（小时）
	unsigned int mCookerUsedTime; //灶具累计使用时间（小时）
	unsigned int mSteamClean;//蒸汽洗
	unsigned int mWindSync;//风力同步开关
	unsigned int mAutoClean;//自动清洁开关

	unsigned int mLeftBanTimingOff;//左灶台是否禁止MCU端定时关火
	unsigned int mLeftTimingOffTime;//左灶台定时关火时间
	unsigned int mRightBanTimingOff;//右灶台是否禁止MCU端定时关火
	unsigned int mRightTimingOffTime;//右灶台定时关火时间
}IPPHOCOSTATUS, *PIPPHOCOSTATUS; //烟灶所有状态结构体，包括总体状态和细节状态
typedef struct {
	unsigned int mLeftFireStatus; //左灶火力状态
	unsigned int mRightFireStatus; //右灶火力状态
	IPPFIRETIME mLeftTime; //左灶火力定时
	IPPFIRETIME mRightTime; //右灶火力定时
	char recipe_left[IPP_MAX_CHAR_LENGTH]; //左灶当前食谱
	char recipe_right[IPP_MAX_CHAR_LENGTH]; //右灶当前食谱
	unsigned int mCleanMode;
	unsigned int mWindLevel;
//	unsigned int mWindLevel[3]; //风力：0总 1左 2右
	unsigned int mIllumination; //照明
	unsigned int mSmokeLevel; //烟雾浓度
	unsigned int mWindBySmoke; //风随烟动
	unsigned int mErrorDetection; //故障监测(相同)
	unsigned int mAntiDryDetection[2];	//防干烧监测
	unsigned int mGasLeakDetection; //煤气泄漏监测
	unsigned int mHoodUsedTime; //烟机累计使用时间（小时）
	unsigned int mCookerUsedTime; //灶具累计使用时间（小时）
//	unsigned int mOnoff;//烟机开关
//	unsigned int mSteamClean;//蒸汽洗
//	unsigned int mWindSync;//风力同步开关
//	unsigned int mAutoClean;//自动清洁开关
//
//	unsigned int mLeftBanTimingOff;//左灶台是否禁止MCU端定时关火
//	unsigned int mLeftTimingOffTime;//左灶台定时关火时间
//	unsigned int mRightBanTimingOff;//右灶台是否禁止MCU端定时关火
//	unsigned int mRightTimingOffTime;//右灶台定时关火时间
}IPPHIGHHOCOSTATUS, *PIPPHIGHHOCOSTATUS; //烟灶所有状态结构体，包括总体状态和细节状态
typedef struct {
	IPPDevice mBaseInfo;
	PDeviceFun mSetFun;
	IPPHOOD hood; //烟机
	IPPCOOKER cooker[2]; //size为2,0为左灶，1为右灶
	IPPDTime hocotime;
	IPPHOCOSTATUS status;
	IPPLOWHOCOSTATUS lowstatus;
	//yw integraed from ippsmok
	IPPHIGHHOCOSTATUS highstatus;
	unsigned int mResult;
	unsigned int mError;
	unsigned int mErrorValue;
	char heaterstatus[1024];
	char verifycode[1024];
	
	//
	char powerStatus[10];
	//char uuid[128];
}IPPHOCO, *PIPPHOCO; //通用结构体

#endif /* IPPSTRUCT_H_ */
