//
//  H5CommandProtocol.h
//  SmartHome
//
//  Created by HuangZe on 2025/1/1.
//

#import <Foundation/Foundation.h>

@class H5InvokeCommand;
@class WKWebView;

NS_ASSUME_NONNULL_BEGIN

@protocol H5CommandProtocol <NSObject>

@required
- (void)invokeH5CommandWithName:(NSString *)name args:(id)object;

- (BOOL)hasH5CommandForName:(NSString *)commandName;

@optional
/// 是否允许重复命令
- (BOOL)shouldRunRepeatedCommand:(H5InvokeCommand *)cmd;

- (void)setWebViewDidFinishLoad:(WKWebView *)theWebview;

@end

NS_ASSUME_NONNULL_END
