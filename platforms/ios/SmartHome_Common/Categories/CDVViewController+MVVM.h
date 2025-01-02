//
//  CDVViewController+MVVM.h
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import <Cordova/Cordova.h>

NS_ASSUME_NONNULL_BEGIN

@protocol H5ViewModelProtocol;

@interface CDVViewController (MVVM)

@property (nonatomic, strong) id<H5ViewModelProtocol> h5ViewModel;

@end

NS_ASSUME_NONNULL_END
