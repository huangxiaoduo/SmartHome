//
//  Environment.m
//  SmartHome
//
//  Created by 泽 on 1/3/25.
//

#import "Environment.h"

@interface Environment ()
@property (nonatomic, strong) NSDictionary *configDict;
@end

@implementation Environment

+ (instancetype)shared {
    static Environment *env = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        env = [[self alloc] init];
        [env loadConfiguration];
    });
    return env;
}

- (void)loadConfiguration {
    // 获取Info.plist路径
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
    if (!path) {
        NSLog(@"Info.plist文件未找到");
        return;
    }
    
    // 读取plist内容
    NSDictionary *config = [NSDictionary dictionaryWithContentsOfFile:path];
    if (!config) {
        NSLog(@"Info.plist内容读取失败");
        return;
    }
    
    [self setupWithConfiguration:config[@"Config"] ?: @{}];
}

- (void)setupWithConfiguration:(NSDictionary *)config {
    _configDict = [config copy];
    
    // 使用 KVC 自动设置类的属性
    [self setValuesForKeysWithDictionary:config];
    
    // 解析环境类型并设置
    NSString *envTypeString = config[@"ENV"] ?: @"Dev";
    if ([envTypeString isEqualToString:@"Test"]) {
        _type = EnvironmentTypeTest;
    } else if ([envTypeString isEqualToString:@"Prod"]) {
        _type = EnvironmentTypeProd;
    } else {
        _type = EnvironmentTypeDev;
    }
}

// 重写 setValue:forUndefinedKey: 方法，避免因缺少字段而抛出异常
- (void)setValue:(id)value forUndefinedKey:(NSString *)key {
    NSLog(@"Environment 未定义的字段: %@", key);
}

- (void)setNilValueForKey:(NSString *)key {
    NSLog(@"Environment 中字段：%@的值为空", key);
}

- (NSDictionary *)currentConfig {
    return [self.configDict copy];
}
@end
