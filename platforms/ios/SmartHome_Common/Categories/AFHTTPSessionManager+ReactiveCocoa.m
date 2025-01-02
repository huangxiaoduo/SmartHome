//
//  AFHTTPSessionManager+ReactiveCocoa.m
//  SmartHome
//
//  Created by 泽 on 1/2/25.
//

#import "AFHTTPSessionManager+ReactiveCocoa.h"
#import <objc/message.h>
#import <objc/runtime.h>

/// 网路请求超时时间
#define Timeout 10

NSString *const RACAFNResponseObjectErrorKey = @"responseObject";

static const int AF_RAC_KEY;

@implementation AFHTTPSessionManager (ReactiveCocoa)

#pragma mark - Association

- (void)setChild:(AFHTTPSessionManager<BaseAPIProtocol> *)child {
    objc_setAssociatedObject(self, &AF_RAC_KEY, child, OBJC_ASSOCIATION_ASSIGN);
}

- (AFHTTPSessionManager<BaseAPIProtocol> *)child {
    return objc_getAssociatedObject(self, &AF_RAC_KEY);
}

#pragma mark - Life Cycle

+ (void)load {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Class class = [self class];

        SEL o_dealloc = NSSelectorFromString(@"dealloc");
        SEL af_rac_dealloc = @selector(af_rac_dealloc);

        Method om_dealloc = class_getInstanceMethod(class, o_dealloc);
        Method af_racm_dealloc = class_getInstanceMethod(class, af_rac_dealloc);

        BOOL a_dealloc = class_addMethod(class, af_rac_dealloc, method_getImplementation(af_racm_dealloc), method_getTypeEncoding(af_racm_dealloc));

        if (a_dealloc) {
            class_replaceMethod(class, af_rac_dealloc, method_getImplementation(om_dealloc), method_getTypeEncoding(om_dealloc));
        } else {
            method_exchangeImplementations(om_dealloc, af_racm_dealloc);
        }

        SEL o_init = NSSelectorFromString(@"init");
        SEL af_rac_init = @selector(init_af_rac);

        Method om_init = class_getInstanceMethod(class, o_init);
        Method af_racm_init = class_getInstanceMethod(class, af_rac_init);

        BOOL a_init = class_addMethod(class, af_rac_init, method_getImplementation(af_racm_init), method_getTypeEncoding(af_racm_init));

        if (a_init) {
            class_replaceMethod(class, af_rac_init, method_getImplementation(om_init), method_getTypeEncoding(om_init));
        } else {
            method_exchangeImplementations(om_init, af_racm_init);
        }
    });
}

- (instancetype)init_af_rac {
    if ((self = [self init_af_rac])) {
        [self setChild:(AFHTTPSessionManager<BaseAPIProtocol>*)self];
        self.requestSerializer = [AFHTTPRequestSerializer serializer];
        self.responseSerializer = [AFHTTPResponseSerializer serializer];
    }
    return self;
}

- (void)af_rac_dealloc {
    [self setChild:nil];
    [self af_rac_dealloc];
}

#pragma mark - Public
-(RACSignal *)rac_POST:(NSString *)path parameters:(id)parameters {
    return [[self rac_reqeustMethod:@"POST" path:path parameters:parameters] setNameWithFormat:@"%@ -rac_POST: %@, parameters: %@", self.class, path, parameters];
}

-(RACSignal *)rac_GET:(NSString *)path parameters:(id)parameters {
    return [[self rac_reqeustMethod:@"GET" path:path parameters:parameters] setNameWithFormat:@"%@ -rac_GET: %@, parameters: %@", self.class, path, parameters];
}

-(RACSignal *)rac_reqeustMethod:(NSString *)method
                           path:(NSString *)path
                     parameters:(id)parameters {
    return [RACSignal createSignal:^RACDisposable * _Nullable(id<RACSubscriber>  _Nonnull subscriber) {
        NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:[self urlWith:path]]
                                                               cachePolicy:NSURLRequestReloadIgnoringLocalCacheData
                                                           timeoutInterval:Timeout];
        [request setHTTPMethod:method];
        [self configureRequest:request path:path parameters:parameters];
        
        NSURLSessionDataTask *task = [self __dataTaskWithRequest:request subscriber:subscriber];
        [task resume];
        
        return [RACDisposable disposableWithBlock:^{
            [task cancel];
        }];
    }];
}

- (NSURLSessionDataTask *)__dataTaskWithRequest:(NSURLRequest *)request
                                     subscriber:(id<RACSubscriber>)subscriber
{
    return [self dataTaskWithRequest:request
                      uploadProgress:^(NSProgress * _Nonnull uploadProgress) {}
                    downloadProgress:^(NSProgress * _Nonnull downloadProgress) {}
                   completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if (error) {
            NSMutableDictionary *userInfo = [error.userInfo mutableCopy];
            if (responseObject) {
                userInfo[RACAFNResponseObjectErrorKey] = responseObject;
            }
            
            NSError *errorWithRes = [NSError errorWithDomain:error.domain code:error.code userInfo:userInfo.copy];
            [subscriber sendError:errorWithRes];
        } else {
            NSDictionary *dic    = [self parseResponseObject:responseObject response:response];
            NSString *resultCode = [self resultCode];
            NSString *code       = dic[resultCode];
            
            if ([self.child respondsToSelector:@selector(dealBadCode:)]) {
                [self.child dealBadCode:code];
            }
            
            [subscriber sendNext:RACTuplePack(dic, response)];
            [subscriber sendCompleted];
        }
    }];
}

- (NSDictionary *)parseResponseObject:(id)responseObj response:(NSURLResponse *)request {
    return [responseObj objectFromJSONData];
}

- (void)configureRequest:(NSMutableURLRequest *)request
                    path:(NSString *)path
              parameters:(id)parameters {
    if (!parameters || [parameters isKindOfClass:NSNull.class]) {
        parameters = @{};
    }
    
    NSCParameterAssert([parameters respondsToSelector:@selector(toJSONValue)]);
    
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    
    /// GET 不能设置Body，应该放在URL中
    if ([request.HTTPMethod isEqualToString:@"POST"]) {
        NSString *data = [[parameters toJSONValue] stringByReplacingOccurrencesOfString:@"\n" withString:@""];
        [request setHTTPBody:[[NSString stringWithUTF8String:data.UTF8String] dataUsingEncoding:NSUTF8StringEncoding]];
    }
}

#pragma mark - Private

- (NSString *)urlWith:(NSString *)path {
    if ([path.lowercaseString hasPrefix:@"http:"] || [path.lowercaseString hasPrefix:@"https:"]) {
        return [path stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet URLQueryAllowedCharacterSet]];
    }
    
    // TODO
}

- (NSString *)resultCode {
    return @"resultcode";
}

inline NSString* pkgName(void) {
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleIdentifier"];
}

@end
