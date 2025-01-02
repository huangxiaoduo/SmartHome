//
//  AFHTTPSessionManager+ReactiveCocoa.h
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import <AFNetworking/AFNetworking.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Subclass MUST conforms to BaseAPIProtocol, and NEVER override public methods in Baseclass.
 */
@interface AFHTTPSessionManager (ReactiveCocoa)

// ❗❗❗IMPORTANT: DO NOT OVERRIDE FOLLOWING 2 METHODS
- (RACSignal *)rac_POST:(NSString *)path parameters:(id)parameters;
- (RACSignal *)rac_GET: (NSString *)path parameters:(id)parameters;

@end

@interface AFHTTPSessionManager (Protected)

- (void)configureRequest:(NSMutableURLRequest *)request
                    path:(NSString *)path
              parameters:(id)parameters;

- (NSDictionary *)parseResponseObject:(id)responseObj
                             response:(NSURLResponse *)request;



@end

NS_ASSUME_NONNULL_END
