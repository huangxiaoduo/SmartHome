//
//  H5InvokeCommand.h
//  SmartHome
//
//  Created by HuangZe on 2025/1/1.
//

#import <Foundation/Foundation.h>

@class CDVInvokedUrlCommand;

NS_ASSUME_NONNULL_BEGIN

@interface H5InvokeCommand : NSObject

@property (nonatomic, copy) NSString *commandName;
@property (nonatomic, copy) NSString *callbackId;
@property (nonatomic, copy) NSString *className;
@property (nonatomic, copy) NSString *methodName;

@property (nonatomic, assign, readonly) NSUInteger timeStamp;
@property (nonatomic, strong) NSDictionary *argDict;

+ (NSArray<H5InvokeCommand *> *)commandsWithCDVCommand:(CDVInvokedUrlCommand *)urlComamnd;

@end

NS_ASSUME_NONNULL_END
