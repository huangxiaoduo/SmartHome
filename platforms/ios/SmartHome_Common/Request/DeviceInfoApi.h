//
//  DeviceInfoApi.h
//  SmartHome
//
//  Created by HuangZe on 2025/1/4.
//

#import "Request.h"

NS_ASSUME_NONNULL_BEGIN

@interface DeviceInfoApi : Request

- (instancetype)initWithDeviceSN:(NSString *)sn;

@end

NS_ASSUME_NONNULL_END
