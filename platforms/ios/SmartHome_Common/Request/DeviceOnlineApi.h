//
//  DeviceOnlineApi.h
//  SmartHome
//
//  Created by 泽 on 1/7/25.
//

#import "Request.h"

NS_ASSUME_NONNULL_BEGIN

@interface DeviceOnlineApi : Request

- (instancetype)initWithDeviceSN:(NSString *)sn;
@end

NS_ASSUME_NONNULL_END
