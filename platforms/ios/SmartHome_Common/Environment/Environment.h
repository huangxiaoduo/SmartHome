//
//  Environment.h
//  SmartHome
//
//  Created by HuangZe on 2025/1/2.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Environment : NSObject

/// 服务器地址
@property (nonatomic, copy, readonly) NSString *APP_URL;

+ (instancetype)shared;

- (NSDictionary *)currentConfig;

@end

NS_ASSUME_NONNULL_END
