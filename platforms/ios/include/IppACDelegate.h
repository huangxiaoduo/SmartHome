//
//  IppDelegate.h
//  ipp
//
//  Created by pcwe2002 on 15/5/6.
//  Copyright (c) 2015年 changhong. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ippstruct.h"

/**
 *  空调代理类，支持空调时需要实现该代理方法
 */
@protocol IppACDelegate<NSObject>
@optional

- (void)didDeviceEventReport:(PIPPDevice)dev eventType:(int) eventtype param1:(int) param1 param2:(char *)param2 length:(int) param2length;

/**
 *  调用设置api后，该方法会返回设置是否成功
 *
 *  @param dev     设备
 *  @param id      属性id
 *  @param success 是否成功
 */
- (void)didDeviceSetAck:(PIPPDevice)dev id:(int)id success:(int)success;

@end


void setIppACDelegate(id<IppACDelegate> ippACDelegate);