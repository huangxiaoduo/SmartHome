//
//  ToNativeBridge.m
//  SmartHome
//
//  Created by HuangZe on 2024/12/31.
//

#import "ToNativeBridge.h"
#import "H5CommandProtocol.h"
#import "CDVViewController+MVVM.h"
#import "H5InvokeCommand.h"

@implementation ToNativeBridge

#pragma mark - Plugin Method

- (void)initData:(CDVInvokedUrlCommand*)command {
#ifdef DEBUG
    NSLog(@"%s __ %@", __PRETTY_FUNCTION__, command.arguments);
#endif
    
    [self invokeCommand:command];
}

- (void)sendDataToNative:(CDVInvokedUrlCommand*)command {
    
#ifdef DEBUG
    NSLog(@"%s __ %@", __PRETTY_FUNCTION__, command.arguments);
#endif
    
    [self invokeCommand:command];
}

#pragma mark - Private

- (void)invokeCommand:(CDVInvokedUrlCommand *)command
{
    NSCParameterAssert([self.viewController isKindOfClass:CDVViewController.class]);
    
    id<H5CommandProtocol> h5Command = (id<H5CommandProtocol>)((CDVViewController *)self.viewController).h5ViewModel;
    
    if (!h5Command) return;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSArray *commands = [H5InvokeCommand commandsWithCDVCommand:command];
        
        for (H5InvokeCommand *cmd in commands) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [h5Command invokeH5CommandWithName:cmd.commandName args:cmd];
            });
        }
    });
}
@end
