//
//  ToNativeBridge.m
//  SmartHome
//
//  Created by HuangZe on 2024/12/31.
//

#import "ToNativeBridge.h"

@implementation ToNativeBridge

#pragma mark - Plugin Method

- (void)initData:(CDVInvokedUrlCommand*)command {
#ifdef DEBUG
    NSLog(@"%s __ %@", __PRETTY_FUNCTION__, command.arguments);
#endif
    
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"init data ===="] callbackId:command.callbackId];
}




- (void)sendDataToNative:(CDVInvokedUrlCommand*)command {
    
#ifdef DEBUG
    NSLog(@"%s __ %@", __PRETTY_FUNCTION__, command.arguments);
#endif
    
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"send data to native ===="] callbackId:command.callbackId];
}


@end
