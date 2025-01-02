//
//  H5ViewModelProtocol.h
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import <Foundation/Foundation.h>
#import "H5CommandProtocol.h"

@class H5CommandProxy;
@class CDVCommandDelegate;
@class CDVViewController;

#define H5_Regist_Command(name, sel) \
[_h5CommandProxy registerCommandWithName:name action: sel]

NS_ASSUME_NONNULL_BEGIN

@protocol H5ViewModelProtocol <H5CommandProtocol>

@property (nonatomic, strong) H5CommandProxy *h5CommandProxy;

- (instancetype)initWithController:(CDVViewController *)controller;
@end

NS_ASSUME_NONNULL_END
