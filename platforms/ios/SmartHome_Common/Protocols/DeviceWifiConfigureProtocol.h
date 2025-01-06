//
//  DeviceWifiConfigureProtocol.h
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, WifiConfigureStep) {
    WifiConfigureStepUnknow = 0,
    WifiConfigureStepStarted,
};

NS_ASSUME_NONNULL_BEGIN

@protocol DeviceWifiConfigureConsumerDelegate <NSObject>
/**
 * Notified by configure events
 *
 * @param wifiConfigure Wifi Configure Object
 * @param step          Current step in wifi configuration, shared in varies of wifi configure objects.
 */
- (void)wifiConfigure:(id<DeviceWifiConfigureProtocol>)wifiConfigure continueToStep:(WifiConfigureStep)step;
@end

@protocol DeviceWifiConfigureProtocol <NSObject>

/**
 * Consumer do not implement this protocol, use it as wifi configure object
 */
@property (nonatomic, copy) NSString *sn;
@property (nonatomic, weak) id<DeviceWifiConfigureConsumerDelegate> delegate;

- (void)startConfigure;
- (void)stopConfigure;
@end

NS_ASSUME_NONNULL_END
