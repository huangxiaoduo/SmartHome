//
//  H5CommandProxy.m
//  SmartHome
//
//  Created by HuangZe on 2025/1/1.
//

#import "H5CommandProxy.h"
#import "H5InvokeCommand.h"

@interface H5CommandProxy ()

@property (nonatomic, strong) NSMutableDictionary<NSString *, NSValue *> *commandMap;
@property (nonatomic, weak)   NSObject<H5CommandProtocol> *target;
@property (nonatomic, strong) H5InvokeCommand *lastCommand;

@end

@implementation H5CommandProxy

- (instancetype)initWithTarget:(NSObject<H5CommandProtocol> *)target
{
    if (self = [super init]) {
        self.target = target;
    }
    return self;
}

-(BOOL)hasH5CommandForName:(NSString *)commandName
{
    return [self.commandMap objectForKey:commandName] != nil;
}

-(void)invokeH5CommandWithName:(NSString *)name args:(id)object
{
    NSValue *value = [self.commandMap objectForKey:name];
    
    if (!value) {
        NSLog(@"找不到命令：%@", name);
        return;
    }
    
    H5InvokeCommand *cmd = (H5InvokeCommand *)object;
    if (_lastCommand && cmd.timeStamp - _lastCommand.timeStamp < 3 &&
        [_lastCommand.commandName isEqualToString:cmd.commandName]) {
        NSLog(@"============发现重复Invoke命令:%@ timeSpam, last:%li , now:%li", name, _lastCommand.timeStamp, cmd.timeStamp);
        
        BOOL bRun = [self.target shouldRunRepeatedCommand:cmd];
        if (!bRun) {
            NSLog(@"============已过滤重复Invoke命令:%@ timeSpam, last:%li , now:%li", name, _lastCommand.timeStamp, cmd.timeStamp);
            return;
        }
    }
    
    SEL sel = (SEL)[value pointerValue];
    [self.target performSelector:sel withObject:object afterDelay:0];
    _lastCommand = cmd;
}

- (void)registerCommandWithName:(NSString *)name action:(SEL)selector
{
    NSValue *value = [NSValue valueWithPointer:selector];
    [self.commandMap setValue:value forKey:name];
}

#pragma mark - Getters & Setters
- (NSMutableDictionary *)commandMap
{
    if (!_commandMap) {
        _commandMap = [NSMutableDictionary dictionary];
    }
    return _commandMap;
}

@end
