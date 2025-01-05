//
//  DeviceInfoApi.m
//  SmartHome
//
//  Created by HuangZe on 2025/1/4.
//

#import "DeviceInfoApi.h"

@implementation DeviceInfoApi {
    NSString *_sn;
}

-(instancetype)initWithDeviceSN:(NSString *)sn {
    if (self = [super init]) {
        _sn = sn;
    }
    return self;
}

-(NSString *)requestUrl {
    return @"/saserver/devModel/sn/v1";
}

-(YTKRequestMethod)requestMethod {
    return YTKRequestMethodPOST;
}

-(id)requestArgument {
    return @{
        @"sn": _sn
    };
}

- (YTKRequestSerializerType)requestSerializerType{
    return YTKRequestSerializerTypeJSON;
}
@end
