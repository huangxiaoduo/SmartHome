//
//  Request.m
//  SmartHome
//
//  Created by 泽 on 1/6/25.
//

#import "Request.h"

@implementation Request

/**
 * 重写判断方法，如果code不是1000，走失败的回调
 */
- (id)jsonValidator {
    NSString *code = self.responseObject[@"code"];
    if (![code isEqualToString:@"1000"]) {
        return @{ @"NOT_1000":[NSObject class] };
    }
    
    return @{
        @"code": NSString.class,
        @"data": NSObject.class
    };
}

/// 设置请求序列化类型
- (YTKRequestSerializerType)requestSerializerType{
    return YTKRequestSerializerTypeJSON;
}

/// 设置响应序列号类型
-(YTKResponseSerializerType)responseSerializerType {
    return YTKResponseSerializerTypeJSON;
}

@end
