//
//  DeviceWifiConfigureSoftAP.m
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import "DeviceWifiConfigureSoftAP.h"
#import "ipp.h"
#import "IppDelegate.h"
#import "CmdCommon.h"

@interface DeviceWifiConfigureSoftAP ()<IppDelegate>
/// 定时器用于查询当前状态
@property (nonatomic) dispatch_source_t timer;
/// 定时器是否开启
@property (nonatomic) BOOL timerStarted;
/// 路由器信息已发送，调用了ipp的setWifiSSIDAndPassword.
@property (nonatomic) BOOL passwordSentToRouter;
@property (nonatomic) int deviceMID;
@property (nonatomic, copy) NSString *mName;
@property (nonatomic, copy) NSString *mUUID;
@end

@implementation DeviceWifiConfigureSoftAP {
    void *_IPPHandler;
}

- (void)startConfigure {
    NSLog(@"%s", __FUNCTION__);
    [super startConfigure];
    
    [self ippStart];
    setIppDelegate(self);
    
    // 启动定时器
    [self startStatusTimer];

}

- (void)stopConfigure {
    NSLog(@"%s", __FUNCTION__);
    [super stopConfigure];
    
    [self stopStatusTimer];
    
    setIppDelegate(nil);
    [self ippClose];
}

#pragma mark - Start & Stop Timer
- (void)startStatusTimer {
    if (self.timerStarted) {
        return; // 如果定时器已经启动，则不重复启动
    }

    self.timerStarted = YES;
    
    // 设置定时器触发的间隔为 1 秒
    dispatch_source_set_timer(self.timer, DISPATCH_TIME_NOW, 1.5 * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
    dispatch_source_set_event_handler(self.timer, ^{
        [self checkWifiStatus];
    });

    // 启动定时器
    dispatch_resume(self.timer);
}

- (void)stopStatusTimer {
    if (self.timer && self.timerStarted) {
        dispatch_source_cancel(self.timer);
        self.timer = nil;
        self.timerStarted = NO;
    }
}

#pragma mark - Methods
- (void)checkWifiStatus {
    // 1. 检查当前设备的SSID和Router的SSID是否匹配
    if ([self.sn isEqualToString:DeviceWifiConfigure.currentSSID]) {
        if (!self.deviceMID) {
            self.currentStep = WifiConfigureStepAppIsLookingForDevice;
            NSLog(@"%s  WifiConfigureStepAppIsLookingForDevice", __FUNCTION__);
        } else {
            NSLog(@"%s  WifiConfigureStepRouterPasswordSent，ssid：%@，password：%@", __FUNCTION__, self.routerSSID, self.routerPassword);
            setWifiSSIDAndPassword(self.deviceMID, self.routerSSID.UTF8String, self.routerPassword.UTF8String);
            self.passwordSentToRouter = YES;
            self.currentStep = WifiConfigureStepRouterPasswordSent;
        }
    } else if ([self.routerSSID isEqualToString:DeviceWifiConfigure.currentSSID]) {
        if (!self.passwordSentToRouter) {
            NSLog(@"%s  WifiConfigureStepShouldGotoSettingApp", __FUNCTION__);
            self.currentStep = WifiConfigureStepShouldGotoSettingApp;
        } else {
            NSLog(@"%s  WifiConfigureStepWaitingOnLineNotice", __FUNCTION__);
            self.currentStep = WifiConfigureStepWaitingOnLineNotice;
        }
    }
    
    // delegate
    self.currentStep = WifiConfigureStepRouterPasswordSent;
    if ([self.delegate conformsToProtocol:@protocol(DeviceWifiConfigureConsumerDelegate)]) {
        [self.delegate wifiConfigure:self continueToStep:self.currentStep];
    }
}

#pragma mark - IppDelegate
- (void)ippStart {
    if (_IPPHandler) {
        ippDestroy(_IPPHandler);
        _IPPHandler = ippCreate();
    }
}

- (void)ippClose {
    if (_IPPHandler) {
        ippDestroy(_IPPHandler);
        _IPPHandler = NULL;
    }
}

- (void)didDeviceAdd:(PIPPDevice)dev {
    self.deviceMID = dev->mID;
    
    NSString *ssid = DeviceWifiConfigure.currentSSID;
    NSString *uuid = [[NSString alloc] initWithCString:(const char*)dev->mUUID encoding:NSASCIIStringEncoding];
    NSString *name = [[NSString alloc] initWithCString:(const char*)dev->mName encoding:NSASCIIStringEncoding];
    
    NSLog(@"%s ===name: %@", __FUNCTION__, name);
    NSLog(@"%s ===uuid: %@", __FUNCTION__, uuid);
    
    /**
     * 入网第一次接收回调消息
     */
    if ([ssid isEqualToString:self.sn]) {
        if (name) {
            _mName = name;
        }
        if (uuid) {
            _mUUID = uuid;
        }
    }
    
    /**
     * 入网第二次接收回调消息
     */
    if (self.currentStep == WifiConfigureStepWaitingOnLineNotice) {
        if ([_mUUID isEqualToString:uuid] &&
            [uuid isEqualToString:self.sn] &&
            [_mName isEqualToString:name]) {
            NSLog(@"%s ===_mName: %@", __FUNCTION__, _mName);
            NSLog(@"%s ===_mUUID: %@", __FUNCTION__, _mUUID);
            _mName = nil;
            _mUUID = nil;
            
            self.currentStep = WifiConfigureStepOnlineSuccess;
            if ([self.delegate conformsToProtocol:@protocol(DeviceWifiConfigureConsumerDelegate)]) {
                [self.delegate wifiConfigure:self continueToStep:self.currentStep];
            }
            
            [self stopConfigure];
        }
    }
}

- (void)didDeviceRemove:(PIPPDevice)dev {
    NSLog(@"Device: %s disconnected", dev->mName);
}

- (void)didReport:(NSString *)uuid status:(NSString*) status {
    NSLog(@"%s %s %@ %@", __FILE__, __PRETTY_FUNCTION__, uuid, status);
}

#pragma mark - Property

- (dispatch_source_t)timer {
    return _timer ?: (_timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)));
}

@end
