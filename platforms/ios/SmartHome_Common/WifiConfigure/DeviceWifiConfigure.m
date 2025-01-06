//
//  DeviceWifiConfigure.m
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import "DeviceWifiConfigure.h"
#import <SystemConfiguration/CaptiveNetwork.h>

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

@end
