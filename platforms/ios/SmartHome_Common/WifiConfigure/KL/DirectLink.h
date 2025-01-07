//
//  DirectLink.h
//  DirectLink
//
//  Created by GeHaitong on 15/4/21.
//  Copyright (c) 2015年 xpg. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DirectLink;

@protocol DirectLinkDelegate <NSObject>

@optional

- (void)directLink:(DirectLink *)directLink didReceiveData:(NSData *)data fromAddress:(NSData *)address;

@end

@interface DirectLink : NSObject

@property (nonatomic, assign, readonly) BOOL isStarted;

@property (nonatomic, weak) id <DirectLinkDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)sharedInstance;

- (void)startWithSSID:(NSString *)ssid password:(NSString *)password;
- (void)stop;

@end
