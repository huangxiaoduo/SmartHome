 	 #ifndef IPPHOCOFUN_H_
#define IPPHOCOFUN_H_

#include "ippstruct.h"

/*
 * 烟机风力
 */
typedef enum hocoWindLevel {
	wl_shutdown = 0x00, //关闭  0x00
	wl_weak = 0x01, //低风  0x01
	wl_normal = 0x02, //中风  0x02
	wl_strong = 0x03,//高风  0x03
} HOCOWindLevel;

/*
 * 开关模式
 */
typedef enum hocoSwitchMode {
	hoco_open = 0x01,
	hoco_close = 0x00
} HOCOSwitchMode;

/*
 *烟灶火力
 */
typedef enum hocoFireLevel {
	fl_shutdown = 0x00, //关火
	fl_levelone = 0x01, //一级火力（最小）
	fl_leveltwo = 0x02, //二级火力
	fl_levelthree = 0x03, //三级火力
	fl_levelfour = 0x04, //四级火力
	fl_levelfive = 0x05 //五级火力（最大）
} HOCOFireLevel;
/*
 * 烟灶选择
 */
typedef enum cooker {
	c_left = 0, //左灶
	c_right = 1 //右灶
}HOCOCooker;

typedef enum wifimode {
	AP = 0, //左灶
	STA = 1 //右灶
}WIFIMODE;

//typedef enum hocoError {
//	e_hoodsocerror = 0x0100, //烟机SOC故障
//	e_hoodsocerror = 0x0200, //烟机SOC故障
//	e_cookererror = 0x0300 //智能灶故障
//} HOCOError;
//
//typedef enum hocoErrorValue {
//	e_serialerror = 1, //串口通信故障
//	e_wifierror = 2, //wifi模块异常
//	e_filestorealarm = 4, //文件存储空间报警
//	e_smokealarm = 1, //烟雾报警
//	e_illunimationalarm = 2, //照明报警
//	e_fanerror = 4, //风机运行故障
//	e_smokesensorerror = 8, //烟雾传感器故障
//	e_rferror = 16, //RF通信故障
//	e_gasleak = 1, //燃气泄漏
//	e_ignitionfailure = 2, //点火失败
//	e_flameout = 4, //意外熄火
//	e_gassensorerror = 8, //燃气传感器故障
//}HOCOErrorValue;
/**
 * 设置烟机开关
 */
int fnHOCOSetPower(int id,int onoff);
int OnSendHocoStatus(int id, PIPPHOCOSTATUS status);
/*
 * 设置风力
 */
int fnHOCOSetWind(int id, int windlevel);
/*
 * 设置照明
 */
int fnHOCOSetIllumination(int id, HOCOSwitchMode illumination);
/*
 * 设置风随烟动
 */
int fnHOCOSetWindBySmoke(int id, HOCOSwitchMode windbysmoke);
/*
 * 设置火力
 */
int fnHOCOSetFireLevel(int id, HOCOCooker cookernum, HOCOFireLevel firelevel);
/*
 * 设置火力定时
 */
int fnHOCOSetFireTime(int id, HOCOCooker cookernum, PIPPFIRETIME time, char *recipe, int length);
/*
 * 获取烟灶当前时间
 */
int fnHOCOGetTime(int id, PIPPDTime time);

/*
 * 获取烟灶状态
 */
int fnHOCOGetStatus(int id, PIPPHOCOSTATUS status);
/*
 * 获取烟灶状态
 */
int fnHOCOGetHighStatus(int id, PIPPHIGHHOCOSTATUS status);
/*
 * 推送食谱
 */
int fnHOCOSendRecipe(int id, char *url, int length);
/*
 * 手机向热水器发送命令
 */
void fnHOCOSendCommand(int id, const char *string, int length);
/*
 * 发送验证码
 */
int fnHOCOVerifyCodeSend(int id, char *verifycode, int length);
/*
 * 修改验证码
 */
int fnHOCOVerifyCodeChange(int id, char *verifycode, int length);
/**
 * 获取验证码
 */
int fnHOCOGetVerifyCode(int id, char *verifycode);

/**
 * 获取热水器状态
 */
int fnHOCOGetHeaterStatus(int id, char *heaterstatus);
/**
 * 获取验证码
 */
int fnHOCOGetPowerStatus(int id, char *powerStatus);

/*
 * 设置自动清洗开关
 * */
int fnHOCOSetAutoClean(int id, HOCOSwitchMode onoff);
/*
 * 设置蒸汽洗开关 0x0716
 */
int fnHOCOSetSteamClean(int id, HOCOSwitchMode onoff);
/*
 * 设置风力同步开关 0x0715
 */
int fnHOCOSetWindSync(int id, HOCOSwitchMode onoff);
/*
 * 设置右风力 0x0714
 */
int fnHOCOSetWindRight(int id, HOCOWindLevel windlevel);
/*
 * 设置左风力 0x0713
 */
int fnHOCOSetWindLeft(int id, HOCOWindLevel windlevel);
/*
 * 設置空调wifi模块模式 0x0712
 */
int fnHOCOSetWifiMode(int id, WIFIMODE mode);
/*
 * 设置昵称 0x0711
 */
int fnHOCOSetNickName(int id, char *nickname, int length);
/*
 * 设置激活码 0x0710
 */
int fnHOCOSetActiveCode(int id, char *code, int length);
/*
 * 设置BSSID 0x070E
 */
int fnHOCOSetBSSID(int id, char *ssid, int length);
/*
 * 低成本设置火力定时 0x0706
 */

int fnHOCOSetLowFireTime(int id, HOCOCooker cookernum, PIPPFIRETIME time, PIPPLOWFIRETIME lowtime, char* recipe, int length) ;

#endif
