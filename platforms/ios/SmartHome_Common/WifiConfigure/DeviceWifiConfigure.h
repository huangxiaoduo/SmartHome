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
    WifiConfigureStepStarted,//1
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
@optional
- (void)wifiConfigure:(DeviceWifiConfigure *_Nonnull)wifiConfigure
        continueToStep:(WifiConfigureStep)step;

- (void)wifiConfigure:(DeviceWifiConfigure *_Nonnull)wifiConfigure
       continueToStep:(WifiConfigureStep)step
            andObject:(id _Nullable )obj
            withError:(NSError *_Nullable)error;

@end


NS_ASSUME_NONNULL_BEGIN

@interface DeviceWifiConfigure : NSObject
/// 设备唯一标识
@property (nonatomic, copy) NSString *sn;

- (void)startConfigure;
- (void)stopConfigure;

+ (NSString *)currentSSID;

@end

NS_ASSUME_NONNULL_END
