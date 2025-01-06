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
 *  IPP代理，使用IPP时，需要在自己的类中实现该代理
 */
@protocol IppDelegate<NSObject>
@optional

/**
 *  设备发现事件
 *
 *  @param dev 设备
 */
- (void)didDeviceAdd:(PIPPDevice)dev;

/**
 *  设备掉线事件
 *
 *  @param dev 设备
 */
- (void)didDeviceRemove:(PIPPDevice)dev;

/**
 *  事件上报，小家电需要实现该事件
 *
 *  @param uuid   设备uuid
 *  @param status 上报状态
 */
- (void)didReport:(NSString *)uuid status:(NSString*) status;

/**
 *  设备上报事件
 *
 *  @param dev  设备
 *  @param data 事件数据
 */
- (void)didDeviceEvent:(PIPPDevice)dev data:(NSData *)data;

@end


void setIppDelegate(id<IppDelegate> ippDelegate);