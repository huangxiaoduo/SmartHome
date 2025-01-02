//
//  AFHTTPSessionManager+ReactiveCocoa.h
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import <AFNetworking/AFNetworking.h>

typedef NS_ENUM(NSUInteger, RequestType) {
    RequestTypeNormal,
    RequestTypeCUC
};

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

- (NSString *)urlWith:(NSString *)path;

- (RACSignal *)rac_reqeustMethod:(NSString *)method
                            path:(NSString *)path
                      parameters:(id)parameters;

@end

UIKIT_EXTERN NSString* pkgName(void);

@protocol BaseAPIProtocol <NSObject>

@required
- (NSString *)baseURLString;
- (RequestType)requestType;

@optional
- (NSString *)serverPathString;
- (NSString *)resultCode;
- (void)dealBadCode:(NSString *)code;

@end

NS_ASSUME_NONNULL_END
