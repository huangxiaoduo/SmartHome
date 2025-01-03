//
//  Environment.h
//  SmartHome
//
//  Created by 泽 on 1/3/25.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, EnvironmentType) {
    EnvironmentTypeDev,
    EnvironmentTypeTest,
    EnvironmentTypeProd
};

NS_ASSUME_NONNULL_BEGIN

@interface Environment : NSObject
@property (nonatomic, assign, readonly) EnvironmentType type;

/// /saserver服务器地址
@property (nonatomic, copy, readonly) NSString *APP_URL_SERVER;

+ (instancetype)shared;
- (NSDictionary *)currentConfig;
@end

NS_ASSUME_NONNULL_END
