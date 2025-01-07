//
//  DeviceWifiConfigure.h
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import <Foundation/Foundation.h>

@class DeviceWifiConfigure;

typedef NS_ENUM(NSUInteger, WifiConfigureStep) {
    WifiConfigureStepUnknown = 0,
    WifiConfigureStepStarted,               // 调用startConfigure
    
    WifiConfigureStepAppIsLookingForDevice, // 第一代AP配网，didDeviceAdd:(PIPPDevice)dev还未上报deviceMID.
    WifiConfigureStepRouterPasswordSent,    // 第一代AP配网，路由器信息已发送，调用了ipp的setWifiSSIDAndPassword.
    WifiConfigureStepShouldGotoSettingApp,  // 第一代AP配网，还未连接设备热点发送路由信息
    WifiConfigureStepWaitingOnLineNotice,
    
    WifiConfigureStepOnlineSuccess,         // 设备配网成功
    WifiConfigureStepOnlineFailure,         // 设备配网失败
    WifiConfigureStepBindSuccess,           // 设备绑定成功
    WifiConfigureStepBindFailure,           // 设备绑定失败
    
    WifiConfigureStepEnded                  // 配网结束
};


/**
 *  Consumer should implement this protocol to get notified by events
 */
@protocol DeviceWifiConfigureConsumerDelegate <NSObject>

/**
 *  Notified by configure events
 *
 *  @param wifiConfigure Wifi Configure Object
 *  @param step          Current step in wifi configuration, shared in varies of wifi configure objects
 */
- (void)wifiConfigure:(DeviceWifiConfigure *_Nonnull)wifiConfigure
        continueToStep:(WifiConfigureStep)step;

@end


NS_ASSUME_NONNULL_BEGIN

@interface DeviceWifiConfigure : NSObject
/// 设备唯一标识
@property (nonatomic, copy) NSString *sn;
/// 路由器名称
@property (nonatomic, copy) NSString *routerSSID;
/**
 *  IMPORTANT: routerPassword can be \@"", it means no password for router;
 *    if routerPassword is nil, it means user has not configure router info yet
 */
@property (nonatomic, copy) NSString *routerPassword;

/// 代理对象
@property (nonatomic, weak) id<DeviceWifiConfigureConsumerDelegate> delegate;

/// 当前配网步骤
@property (nonatomic) WifiConfigureStep currentStep;

/// 是否正在配网
@property (nonatomic, assign) BOOL isDoingJoinNet;

/// 开始配网
- (void)startConfigure;

/// 停止配网
- (void)stopConfigure;

/// 获取当前连接路由器名称
+ (NSString *)currentSSID;

@end

NS_ASSUME_NONNULL_END
