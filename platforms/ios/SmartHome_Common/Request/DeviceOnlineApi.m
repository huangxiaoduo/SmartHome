//
//  DeviceOnlineApi.m
//  SmartHome
//
//  Created by 泽 on 1/7/25.
//

#import "DeviceOnlineApi.h"

@implementation DeviceOnlineApi {
    NSString *_sn;
}

-(instancetype)initWithDeviceSN:(NSString *)sn {
    if (self = [super init]) {
        _sn = sn;
    }
    return self;
}

-(NSString *)requestUrl {
    return @"/saserver/device/isActive";
}

-(YTKRequestMethod)requestMethod {
    return YTKRequestMethodPOST;
}

-(id)requestArgument {
    return @{
        @"sn": _sn
    };
}

@end
