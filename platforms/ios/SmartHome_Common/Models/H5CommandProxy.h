//
//  H5CommandProxy.h
//  SmartHome
//
//  Created by HuangZe on 2025/1/1.
//

#import <Foundation/Foundation.h>
#import "H5CommandProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface H5CommandProxy : NSObject <H5CommandProtocol>

- (instancetype)initWithTarget:(NSObject<H5CommandProtocol> *)target;
- (void)registerCommandWithName:(NSString *)name action:(SEL)selector;

@end

NS_ASSUME_NONNULL_END
