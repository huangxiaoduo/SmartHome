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

@interface DeviceWifiConfigureSoftAP ()
@property (nonatomic) int deviceMID;
@property (nonatomic, copy) NSString *mName;
@property (nonatomic, copy) NSString *mUUID;
@end

@implementation DeviceWifiConfigureSoftAP {
    void *_IPPHandler;
}

- (void)startConfigure {
    
}

- (void)stopConfigure {
    
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
    
    NSLog(@"%s === %@", __FUNCTION__, name);
    NSLog(@"%s === %@", __FUNCTION__, uuid);
}

@end
