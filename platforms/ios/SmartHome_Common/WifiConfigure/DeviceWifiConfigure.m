//
//  DeviceWifiConfigure.m
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import "DeviceWifiConfigure.h"
#import <SystemConfiguration/CaptiveNetwork.h>
#import "DeviceOnlineApi.h"

@interface DeviceWifiConfigure ()
/// 定时器，调接口查询设备是否在线
@property (nonatomic) dispatch_source_t onlineTimer;
/// 定时器是否开启
@property (nonatomic) BOOL onlineTimerStarted;
@end

@implementation DeviceWifiConfigure

- (void)startConfigure {
    
    // 默认实现抛出异常
    [NSException raise:NSInternalInconsistencyException
                format:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)];
}

- (void)stopConfigure {
    // 默认实现抛出异常
    [NSException raise:NSInternalInconsistencyException
                format:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)];

#pragma mark - Start & Stop Timer
- (void)startQueryOnlineTimer {
    if (self.onlineTimerStarted) {
        return; // 如果定时器已经启动，则不重复启动
    }

    self.onlineTimerStarted = YES;
    
    // 设置定时器触发的间隔为 1 秒
    dispatch_source_set_timer(self.onlineTimer, DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
    dispatch_source_set_event_handler(self.onlineTimer, ^{
        [self queryDeviceOnline];
    });

    // 启动定时器
    dispatch_resume(self.onlineTimer);
}

- (void)stopQueryOnlineTimer {
    if (self.onlineTimer && self.onlineTimerStarted) {
        dispatch_source_cancel(self.onlineTimer);
        self.onlineTimer = nil;
        self.onlineTimerStarted = NO;
    }
}

}

+ (NSString *)currentSSID {
    NSString *wifiName = nil;
    NSArray *ifs = (__bridge_transfer  id)CNCopySupportedInterfaces();
    
    for (NSString *ifname in ifs) {
        NSDictionary *info = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)ifname);
        if (info[@"SSID"]) wifiName = info[@"SSID"];
    }
    return wifiName;
}


#pragma mark - Property

- (dispatch_source_t)onlineTimer {
    return _onlineTimer ?: (_onlineTimer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)));
}
@end
