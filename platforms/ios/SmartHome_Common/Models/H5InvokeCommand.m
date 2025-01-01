//
//  H5InvokeCommand.m
//  SmartHome
//
//  Created by HuangZe on 2025/1/1.
//

#import "H5InvokeCommand.h"
#import <Cordova/CDVInvokedUrlCommand.h>

@interface H5InvokeCommand ()
@property (nonatomic, assign) NSUInteger timeStamp;
@end

@implementation H5InvokeCommand

- (instancetype)initWithName:(NSString *)commandName
                  callbackId:(NSString *)backId
                        args:(NSDictionary *)args
{
    if (self = [super init]) {
        self.commandName = commandName;
        self.callbackId = backId;
        self.argDict = args;
        self.timeStamp = (NSUInteger)[NSDate.date timeIntervalSince1970];
    }
    return self;
}

+(NSArray<H5InvokeCommand *> *)commandsWithCDVCommand:(CDVInvokedUrlCommand *)urlComamnd
{
    NSMutableArray *commands = [NSMutableArray array];
    NSArray *urlArgs = [urlComamnd arguments];
    
    for (NSObject *obj in urlArgs) {
        NSDictionary *dic = (NSDictionary*)obj;
        if ([obj isKindOfClass:NSString.class]) {
            dic = [(NSString *)obj toJSONValue];
        }
        
        if (![dic isKindOfClass:NSDictionary.class]) {
            continue;;
        }
        
        H5InvokeCommand *cmd = [[H5InvokeCommand alloc] initWithName:dic[@"action"]
                                                          callbackId:urlComamnd.callbackId
                                                                args:dic];
        cmd.methodName = urlComamnd.methodName;
        cmd.className = urlComamnd.className;
        
        [commands addObject:cmd];
    }
    return commands;
}

@end
