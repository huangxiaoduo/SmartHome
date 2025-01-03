//
//  Environment.m
//  SmartHome
//
//  Created by HuangZe on 2025/1/2.
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
    });
    return env;
}

- (void)loadConfiguration {
    NSString *path = [NSBundle.mainBundle pathForResource:@"Environment" ofType:@"plist"];
    NSDictionary *config = [NSDictionary dictionaryWithContentsOfFile:path];
    [self setupWithConfiguration:config ?: @{}];
}

- (void)setupWithConfiguration:(NSDictionary *)config {
    _configDict = [config copy];
    _APP_URL = config[@"APP_URL"];
}

- (NSDictionary *)currentConfig {
    return [self.configDict copy];
}

@end
