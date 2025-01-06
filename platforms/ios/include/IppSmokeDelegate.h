//
//  IppDelegate.h
//  ipp
//
//  Created by pcwe2002 on 15/5/6.
//  Copyright (c) 2015年 changhong. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ippstruct.h"

@protocol IppSmokeDelegate<NSObject>
@optional

- (void) didSend:(int)dev highstatus:(PIPPHIGHHOCOSTATUS) status;
- (void) didSend:(int)dev status:(PIPPHOCOSTATUS) status;
- (void) didsend:(int)dev error:(int) error errorvalue:(int) errorvalue;
- (void) didSend:(int)dev cookernum:(int)cookernum totaltime:(int)totaltime;
- (void) didSend:(int)dev cooker:(int) timenum timeleft:(int) timeleft;


@end


void setIppSmokeDelegate(id<IppSmokeDelegate> ippSmokeDelegate);