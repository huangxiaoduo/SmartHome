//
//  CDVViewController+MVVM.m
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import "CDVViewController+MVVM.h"
#import "H5ViewModelProtocol.h"
#import <objc/runtime.h>

char H5ControllerViewModelKey;

@implementation CDVViewController (MVVM)

-(void)setH5ViewModel:(id<H5ViewModelProtocol>)h5ViewModel
{
    if ([h5ViewModel conformsToProtocol: @protocol(CDVCommandDelegate)]) {
        _commandDelegate = (id<CDVCommandDelegate>)h5ViewModel;
    }
    
    if (!h5ViewModel) {
        _commandDelegate = nil;
    }
    
    objc_setAssociatedObject(self, &H5ControllerViewModelKey, h5ViewModel, OBJC_ASSOCIATION_RETAIN);
}

-(id<H5ViewModelProtocol>)h5ViewModel
{
    return objc_getAssociatedObject(self, &H5ControllerViewModelKey);
}

@end
