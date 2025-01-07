//
//  DeviceWifiConfigureKL.m
//  SmartHome
//
//  Created by 泽 on 1/7/25.
//

#import "DeviceWifiConfigureKL.h"
#import "GCDAsyncUdpSocket.h"

#import <ifaddrs.h>
#import <arpa/inet.h>
#import "DirectLink.h"
#import "DirectData.h"

#define TagSearchingLan        100
#define UsleepTime            4000

@interface DeviceWifiConfigureKL () <GCDAsyncUdpSocketDelegate,DirectLinkDelegate>

@property (nonatomic) BOOL deviceFoundInLan;
@property (nonatomic) BOOL timerStarted;
@property (nonatomic) BOOL isKL4ORKL3;
@property (nonatomic) BOOL flag;
@property (nonatomic) BOOL isParseDirectString;

@property (nonatomic) dispatch_source_t timer;
@property (nonatomic) dispatch_queue_t searching_queue;
@property (nonatomic) dispatch_queue_t configure_queue;

@property (nonatomic) GCDAsyncUdpSocket *searching;
@property (nonatomic) GCDAsyncUdpSocket *configure;

@property (strong, nonatomic)DirectLink *directLink;//智能插座
@property (strong, nonatomic) DirectData *dData;

@property (nonatomic) NSInteger tag;
@property (nonatomic)  int index;
@property (nonatomic) long start;

@end

@implementation DeviceWifiConfigureKL

#pragma mark - Life Cycle

- (void)dealloc {
    [self stopConfigure];
    [_searching close];
    [_configure close];
}

#pragma mark - Public Method

- (void)startConfigure {
    NSLog(@"KL startConfigure");
    [super startConfigure];
    
    self.start = time(NULL);
    [self startKLTimer];
}

- (void)stopConfigure {
    NSLog(@"KL stopConfigure");
    [super stopConfigure];
    
    self.routerPassword = nil;
    [self stopKLTimer];
}

#pragma mark - Start & Stop Timer
- (void)startKLTimer {
    if (self.timerStarted) {
        return; // 如果定时器已经启动，则不重复启动
    }
    
    self.timerStarted = YES;
    
    // 设置定时器触发的间隔为 1 秒
    dispatch_source_set_timer(self.timer, DISPATCH_TIME_NOW, 1.0 * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
    dispatch_source_set_event_handler(self.timer, ^{
        [self checkKLStatus];
    });
    
    // 启动定时器
    dispatch_resume(self.timer);
}

- (void)stopKLTimer {
    if (self.timer && self.timerStarted) {
        dispatch_source_cancel(self.timer);
        self.timer = nil;
        self.timerStarted = NO;
    }
}

- (void)checkKLStatus {
    if (!self.deviceFoundInLan) {
        long offset = time(NULL) - self.start;
        if (self.start > 0 && (offset <= 10)) {
            if (self.klType != KLType5) {
                [self searchingUDP];
            }
            NSLog(@"KL WifiConfigureStepAppIsLookingForDevice");
            self.currentStep = WifiConfigureStepAppIsLookingForDevice;
        } else if (self.start > 0) {
            if (offset == 20) {
                NSLog(@"KL WifiConfigureStepRouterPasswordSent");
                self.currentStep = WifiConfigureStepRouterPasswordSent;
            }
            if (offset > 10){
                if (self.klType != KLType5) {
                    [self searchingUDP];
                }
            }
            if (offset < 60){
                if (self.klType == KLType5) {
                    //插座配网
                    [self configUDP4SmartSocket];
                } else {
                    for (int J=0; J<5; J++) {
                        [self configUDP];
                        [NSThread sleepForTimeInterval:0.1];
                    }
                }
            }
        }
    } else {
        self.currentStep = WifiConfigureStepOnlineSuccess;
        [self stopConfigure];
        NSLog(@"KL WifiConfigureStepEnded");
    }
}

#pragma mark - GCDAsyncUdpSocketDelegate

- (void)udpSocket:(GCDAsyncUdpSocket *)sock didReceiveData:(NSData *)data fromAddress:(NSData *)address withFilterContext:(id)filterContext {
    NSString * hexString = [self dataToHexString:data];
    NSLog(@"udpSocket didReceiveUdpData hexString %@",hexString);
    
    switch (self.klType) {
        case KLType2:{//冰箱，食材盒子，蛋盒
            
            NSString *msg = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            if (equal(msg, [@"CHIQ_R_" stringByAppendingString:self.sn])){
                self.deviceFoundInLan = YES;
            }
        }
            break;
        case KLType3:{//空调
            if (data) {
                if (!_isParseDirectString && !_deviceFoundInLan) {
                    _isParseDirectString = YES;
                    NSRange range1 = [data rangeOfData:[self.sn dataUsingEncoding:NSUTF8StringEncoding] options:0 range:NSMakeRange(0, data.length)];
                    if (range1.length > 0) {
                        self.deviceFoundInLan = YES;
                    }
                    _isParseDirectString = NO;
                }
            }
        }
            break;
        case KLType4:{//红外盒子
            
            NSRange range1 = [data rangeOfData:[self.sn dataUsingEncoding:NSUTF8StringEncoding] options:0 range:NSMakeRange(0, data.length)];
            if (range1.length > 0) {
                self.deviceFoundInLan = YES;
            }
        }
            break;
            
        case KLType6:{//空气净化器
            NSRange range = [data rangeOfData:[self.sn dataUsingEncoding:NSUTF8StringEncoding] options:0 range:NSMakeRange(0, data.length)];
            if (range.length > 0) {
                self.deviceFoundInLan = YES;
            }
        }
            break;
            
        case KLType7:{//燃热
            NSString *msg = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            if (equal(msg, [@"HEATER_R_" stringByAppendingString:self.sn])){
                self.deviceFoundInLan = YES;
            }
        }
            break;
        case KLType8:{//智能杀菌器
            NSString *msg = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            if (equal(msg, [@"HEALTHBOX_R_" stringByAppendingString:self.sn])){
                self.deviceFoundInLan = YES;
            }
        }
            break;
            
        default:
            break;
    }
}

- (void)udpSocket:(GCDAsyncUdpSocket *)sock didConnectToAddress:(NSData *)address{
    NSLog(@"udpSocket didConnectToAddress data %@",address);
    
}
- (void)udpSocket:(GCDAsyncUdpSocket *)sock didNotConnect:(NSError *)error{
    NSLog(@"udpSocket didNotConnect data %@",error);
    
}
- (void)udpSocket:(GCDAsyncUdpSocket *)sock didSendDataWithTag:(long)tag{
    NSLog(@"udpSocket didSendDataWithTag data %ld",tag);
}

- (void)udpSocket:(GCDAsyncUdpSocket *)sock didNotSendDataWithTag:(long)tag dueToError:(NSError *)error{
    NSLog(@"udpSocket didSendDataWithTag data %@",error);
}


- (void)udpSocketDidClose:(GCDAsyncUdpSocket *)sock withError:(NSError *)error{
    NSLog(@"udpSocketDidClose %@",error);
    
}

#pragma mark DirectLinkDelegate
//插座回调
- (void) directLink:(DirectLink *)directLink didReceiveData:(NSData *)data fromAddress:(NSData *)address
{
    if (!_isParseDirectString && !self.deviceFoundInLan) {
        _isParseDirectString = YES;
        self.dData = [DirectData new];
        NSString * hexString = [self dataToHexString:data];
        NSLog(@"hexString %@",hexString);
        [self byteArrayToHexString:data];
        _isParseDirectString = NO;
    }
}

- (BOOL) parseString:(NSString*)str{
    if (equal(str.uppercaseString,@"18")) {
        _index = 0;
        _flag = YES;
    }
    if (_flag == YES && _index < 4) {
        _dData.totalsize = [NSString stringWithFormat:@"%@%@",_dData.totalsize,str];
        _index++;
    }else if(_index >=4 && _index < 8){
        _dData.reqNum  = [NSString stringWithFormat:@"%@%@",_dData.reqNum,str];
        _index++;
    }else if(_index >=8 && _index <10){//8-9 0600
        if (!_dData.funType) {
            _dData.funType = str;
        } else {
            _dData.funType = [NSString stringWithFormat:@"%@%@",_dData.funType,str];
        }
        
        _index ++;
    }else if(_index >=10 && _index <12 ){//10-11  0100
        if (!_dData.mesType) {
            _dData.mesType = str;
        } else {
            _dData.mesType = [NSString stringWithFormat:@"%@%@",_dData.mesType,str];
        }
        _index ++;
    }else if(_index >=12 && _index <14 ){
        if(_dData.exb){
            _dData.exb = [NSString stringWithFormat:@"%@%@",_dData.exb,str];
        } else {
            _dData.exb = str;
        }
        
        _index++;
    }else if(_index >=14 && _index <16 ){
        if ( _dData.exo) {
            _dData.exo = [NSString stringWithFormat:@"%@%@",_dData.exo,str];
        } else {
            _dData.exo = str;
        }
        
        _index++;
    }else if(_index >=16 && _index <20 ){
        if (_dData.exd) {
            _dData.exd = [NSString stringWithFormat:@"%@%@",_dData.exd,str];
        } else {
            _dData.exd = str;
        }
        
        _index++;
    }else if(_index >=20 && _index <24 ){
        
        if (_dData.resd ) {
            _dData.resd = [NSString stringWithFormat:@"%@%@",_dData.resd,str];
        } else {
            _dData.resd = str;
        }
        
        _index++;
        _flag = NO;
    }
    
    if(_index == 24){
        
        if(equal(@"0600", _dData.funType)&& equal(@"0100", _dData.mesType)){
            self.deviceFoundInLan = YES;
            return YES;
        }
        _dData = nil;
        _index = 0;
    }
    
    return NO;
}

#pragma mark Byte Array to HexadecimalString

-(NSString *)dataToHexString : (NSData * )data{
    
    Byte *bytes = (Byte *)[data bytes];
    NSString *hexStr=@"";
    for(int i=0;i<[data length];i++)
    {
        NSString *newHexStr = [NSString stringWithFormat:@"%x",bytes[i]&0xff];///Hexdecimal
        if([newHexStr length]==1) {
            hexStr = [NSString stringWithFormat:@"%@0%@",hexStr,newHexStr];
        } else {
            hexStr = [NSString stringWithFormat:@"%@%@",hexStr,newHexStr];
        }
    }
    return  hexStr;
}

-(void)byteArrayToHexString : (NSData * )data{
    Byte *bytes = (Byte *)[data bytes];
    
    for(int i=0;i<[data length];i++)
    {
        NSString *newHexStr = [NSString stringWithFormat:@"%02x",bytes[i]&0xff];//%x
        if([newHexStr length]==1) {
            newHexStr = [@"0" stringByAppendingString:newHexStr];
        }
        
        if ([self parseString:newHexStr.uppercaseString]) break;
    }
}

#pragma mark - Private

- (void)searchingUDP {
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSData *klData;
        
        if(self.klType == KLType2){
            klData = [[@"CHIQ_" stringByAppendingString:self.sn] dataUsingEncoding:NSUTF8StringEncoding];
            [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
        }else if(self.klType == KLType3){
            
            NSString * kl3s = @"CHDL";
            const char *kl3Chars = (char *)[kl3s UTF8String];
            const char *snChars = (char *)[self.sn UTF8String];
            NSUInteger length1 = strlen(kl3Chars) + strlen(snChars);
            NSUInteger allDataLen = 5 + length1;
            
            unsigned char dataLen = 0x1c;
            
            char messageBytes[allDataLen];
            
            messageBytes[0] = 0xa5;
            messageBytes[1] = 0xa5;
            messageBytes[2] = 0x21;
            messageBytes[3] = 0x00;
            messageBytes[4] = dataLen;
            messageBytes[5] = kl3Chars[0];
            messageBytes[6] = kl3Chars[1];
            messageBytes[7] = kl3Chars[2];
            messageBytes[8] = kl3Chars[3];
            
            NSUInteger length = strlen(snChars);
            for(int i=0;i<length;i++){
                messageBytes[9+i]= snChars[i];
            }
            
            int total = 0;
            for (int i = 0; i < length1; i++) {
                total = total + (int) messageBytes[5 + i];
            }
            
            NSString *s = [NSString stringWithFormat:@"0x%X", total];
            unsigned result = 0;
            NSScanner *scanner = [NSScanner scannerWithString:s];
            [scanner scanHexInt:&result];
            int mask = 0xFF;
            unsigned  char  endResult = (result & mask);
            
            messageBytes[4] = endResult;
            
            klData =  [[NSData alloc] initWithBytes:messageBytes length:sizeof(messageBytes)];
            [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
            
        }else if(self.klType == KLType4){
            const char *kl4Chars = (char *)[@"CHDL" UTF8String];
            const char messageBytes [8]={0xa5,0xa5,0x08, 0x00,kl4Chars[0],kl4Chars[1],kl4Chars[2],kl4Chars[3]};
            klData =  [[NSData alloc] initWithBytes:messageBytes length:sizeof(messageBytes)];
            [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
        }else if(self.klType == KLType6){ //快连3和快连4循环发送
            if (self.isKL4ORKL3) {
                self.isKL4ORKL3 = NO;
                const char *kl4Chars = (char *)[@"CHDL" UTF8String];
                const char messageBytes [8]={0xa5,0xa5,0x08, 0x00,kl4Chars[0],kl4Chars[1],kl4Chars[2],kl4Chars[3]};
                klData =  [[NSData alloc] initWithBytes:messageBytes length:sizeof(messageBytes)];
                [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
            } else {
                self.isKL4ORKL3 = YES;
                NSString * kl3s = @"CHDL";
                const char *kl3Chars = (char *)[kl3s UTF8String];
                const char *snChars = (char *)[self.sn UTF8String];//24
                NSUInteger length1 = strlen(kl3Chars) + strlen(snChars);
                NSUInteger allDataLen = 5 + length1;
                unsigned char dataLen = 0x1c;
                char messageBytes[allDataLen];
                
                messageBytes[0] = 0xa5;
                messageBytes[1] = 0xa5;
                messageBytes[2] = 0x21;
                messageBytes[3] = 0x00;
                messageBytes[4] = dataLen;
                messageBytes[5] = kl3Chars[0];
                messageBytes[6] = kl3Chars[1];
                messageBytes[7] = kl3Chars[2];
                messageBytes[8] = kl3Chars[3];
                
                NSUInteger length = strlen(snChars);//LMJ600440400000000000001
                for(int i=0;i<length;i++){
                    messageBytes[9+i]= snChars[i];
                }
                
                int total = 0;
                for (int i = 0; i < length1; i++) {
                    total = total + (int) messageBytes[5 + i];
                }
                
                NSString *s = [NSString stringWithFormat:@"0x%X", total];\
                unsigned result = 0;
                NSScanner *scanner = [NSScanner scannerWithString:s];
                [scanner scanHexInt:&result];
                int mask = 0xFF;
                unsigned  char  endResult = (result & mask);
                
                messageBytes[4] = endResult;
                
                klData =  [[NSData alloc] initWithBytes:messageBytes length:sizeof(messageBytes)];
                
                [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
                
            }
            [NSThread sleepForTimeInterval:0.2f];
            
        }else if(self.klType == KLType7){//燃热
            klData = [[@"HEATER_" stringByAppendingString:self.sn] dataUsingEncoding:NSUTF8StringEncoding];
            [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
        }else if(self.klType == KLType8){//智能杀菌器
            klData = [[@"HEALTHBOX_" stringByAppendingString:self.sn] dataUsingEncoding:NSUTF8StringEncoding];
            [self.searching sendData:klData toHost:broadcastAddress() port:80 withTimeout:10 tag:TagSearchingLan];
        }
    });
}

typedef enum {
    I_LINK_CONNECT_ONE_KEY_STATUS_START = 0,//初始状态
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_SYNC = 101,//同步头
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_DATA_LEN = 102,//总长度
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_CMD = 103,//命令字
    
    
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_SSID_LEN = 111,//SSID长度
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_PWD_LEN = 112,//PWD密码长度
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_SECMOD = 113,//加密类型
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_SSID = 114,//SSID
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_PWD = 115,//PWD密码
    I_LINK_CONNECT_ONE_KEY_STATUS_IN_SUM = 126,//正在接收和校验---改为126
} I_LINK_CONNECT_ONE_KEY_STATUS;
typedef struct __I_LINK_CONNECT_ONE_KEY_MULTICAST_STR
{
    unsigned char Sync[5];//
    unsigned char DataLen;//
    unsigned char Cmd;            //
    unsigned char SsidLen;//
    unsigned char PwdLen;//
    unsigned char SecMod;//
    unsigned char Ssid[36];//
    unsigned char Pwd[64];//
    
    unsigned char ChkSum;//
} I_LINK_CONNECT_ONE_KEY_MULTICAST_STR, *P_I_LINK_CONNECT_ONE_KEY_MULTICAST_STR;

-(void)configUDP4SmartSocket{
    NSString *ssid = self.routerSSID;
    NSString *password = self.routerPassword;
    _isParseDirectString = NO;
    _directLink = [DirectLink sharedInstance];
    _directLink.delegate = self;
    [_directLink startWithSSID:ssid password:password];
}

- (void)configUDP {
    NSLog(@"configUDP ssid %@,password %@",self.routerSSID,self.routerPassword);
    _tag = 0;
    NSInteger intJ = 0;
    NSInteger cSum = 0;
    int intFrameNo = 0;//包序号
    NSString *multicastSendIpTemplate = @"239.%d.%d.%d";
    NSString *sendIP = @"";
    NSString *ssid = self.routerSSID;
    NSString *password = self.routerPassword;
    
    I_LINK_CONNECT_ONE_KEY_MULTICAST_STR tmpMulticastStr={0};
    
    //kl4 配置udp包不加密
    if (self.klType != KLType4) {
        
        BOOL result = [self encodeSSID:&ssid password:&password];
        if (!result) {
            NSLog(@"ssid & password 加密失败。");
            return;
        }
    }
    
    char *cSsid = (char *)[ssid UTF8String];
    char *cPwd = (char *)[password UTF8String];
    const NSUInteger PORT = 38000;
    
    //while (1)
    {
        intFrameNo = 1;//包序号
        
        //同步头
        for (intJ=0; intJ<5; intJ++)
        {
            tmpMulticastStr.Sync[intJ] = 1;
            sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_SYNC, intFrameNo, tmpMulticastStr.Sync[intJ]];
            [self doSendData:@"1" length:1 toHost:sendIP port:PORT];
            usleep(UsleepTime);
            intFrameNo++;
            cSum += tmpMulticastStr.Sync[intJ];
        }
        
        //数据包长度，去掉同步头后的长度（含校验尾）
        tmpMulticastStr.DataLen = 5+strlen(cSsid)+strlen(cPwd)+1;
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_DATA_LEN, intFrameNo, tmpMulticastStr.DataLen];
        [self doSendData:@"2" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
        cSum += tmpMulticastStr.DataLen;
        
        
        //命令号
        tmpMulticastStr.Cmd = 0x5F;//不允许修改
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_CMD, intFrameNo, tmpMulticastStr.Cmd];
        [self doSendData:@"3" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
        cSum +=  tmpMulticastStr.Cmd;
        
        //SSID长度
        tmpMulticastStr.SsidLen = strlen(cSsid);
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_SSID_LEN, intFrameNo, tmpMulticastStr.SsidLen];
        [self doSendData:@"4" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
        cSum +=  tmpMulticastStr.SsidLen;
        
        //密码长度
        tmpMulticastStr.PwdLen = strlen(cPwd);
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_PWD_LEN, intFrameNo, tmpMulticastStr.PwdLen];
        [self doSendData:@"44" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
        cSum +=tmpMulticastStr.PwdLen;
        
        //加密方式
        tmpMulticastStr.SecMod = 10;//固定
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_SECMOD, intFrameNo, tmpMulticastStr.SecMod];
        [self doSendData:@"444" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
        cSum += tmpMulticastStr.SecMod;
        
        //SSID
        for (intJ=0; intJ<strlen(cSsid); intJ++)
        {
            tmpMulticastStr.Ssid[intJ] = cSsid[intJ];
            sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_SSID, intFrameNo, tmpMulticastStr.Ssid[intJ]];
            [self doSendData:@"4444" length:1 toHost:sendIP port:PORT];
            usleep(UsleepTime);
            intFrameNo++;
            cSum += tmpMulticastStr.Ssid[intJ];
        }
        //密码
        for (intJ=0; intJ<strlen(cPwd); intJ++)
        {
            tmpMulticastStr.Pwd[intJ] = cPwd[intJ];
            sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_PWD, intFrameNo, tmpMulticastStr.Pwd[intJ]];
            [self doSendData:@"44444" length:1 toHost:sendIP port:PORT];
            usleep(UsleepTime);
            intFrameNo++;
            cSum += tmpMulticastStr.Pwd[intJ];
        }
        //校验
        tmpMulticastStr.ChkSum = cSum;//
        sendIP = [NSString stringWithFormat:multicastSendIpTemplate, I_LINK_CONNECT_ONE_KEY_STATUS_IN_SUM, intFrameNo, tmpMulticastStr.ChkSum];
        [self doSendData:@"0" length:1 toHost:sendIP port:PORT];
        usleep(UsleepTime);
        intFrameNo++;
    }
}

- (BOOL)encodeSSID:(NSString **)ssid password:(NSString **)password{
    NSString *tempSSID = *ssid;
    NSString *tempPWD = *password;
    NSString *_curSN = self.sn;
    
    if (!tempSSID || !tempPWD || !_curSN || _curSN.length < 4) {
        return NO;
    }
    NSString *suffix = [_curSN substringFromIndex:_curSN.length-4];
    
    tempSSID = [@(1).stringValue stringByAppendingFormat:@"%@%@", tempSSID, [suffix substringToIndex:2]];
    tempPWD = [tempPWD stringByAppendingString:[suffix substringFromIndex:2]];
    
    *ssid = tempSSID;
    *password = tempPWD;
    return YES;
}

- (void)doSendData:(NSString *)dataStr length:(NSInteger)length toHost:(NSString *)hostIp port:(NSUInteger)port{
    NSData *data = [dataStr dataUsingEncoding:NSUTF8StringEncoding];
    _tag++;
    [self.configure sendData:data toHost:hostIp port:port withTimeout:5 tag:_tag];
}

//Gets Local IP of the device over Wifi
//Calculates & returns broadcast Address for the network
static NSString * broadcastAddress() {
    NSString * broadcastAddr= @"Error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    
    if (success == 0) {
        temp_addr = interfaces;
        
        while(temp_addr != NULL) {
            // check if interface is en0 which is the wifi connection on the iPhone
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"])
                    broadcastAddr = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_dstaddr)->sin_addr)];
            }
            temp_addr = temp_addr->ifa_next;
        }
        
    }
    freeifaddrs(interfaces);
    return broadcastAddr;
}

#pragma mark - Property

- (void)setRouterPassword:(NSString *)routerPassword {
    self.routerPassword = routerPassword.copy;
    self.start = routerPassword ? time(NULL) - 6 : 0;
}

- (dispatch_source_t)timer {
    return _timer ?: (_timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)));
}

- (dispatch_queue_t)searching_queue {
    return _searching_queue ?: (_searching_queue = dispatch_queue_create("com.changhong.udp.searching", DISPATCH_QUEUE_SERIAL));
}

- (dispatch_queue_t)configure_queue {
    return _configure_queue ?: (_configure_queue = dispatch_queue_create("com.changhong.udp.configure", DISPATCH_QUEUE_SERIAL));
}

- (GCDAsyncUdpSocket *)searching {
    if (!_searching) {
        NSError *error = nil;
        _searching = [[GCDAsyncUdpSocket alloc] initWithDelegate:self
                                                   delegateQueue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
                                                     socketQueue:self.searching_queue];
        
        [_searching enableBroadcast:YES error:&error];
        if (error) {
            NSLog(@"UDP广播失败!");
        }
        if (self.klType == KLType2 || self.klType == KLType7 || self.klType == KLType8) {
            [_searching bindToPort:10086 error:nil];
        } else {
            [_searching bindToPort:8089 error:nil];
        }
        if (![_searching beginReceiving:&error])
        {
            NSLog(@"Error beginReceiving: %@", error);
        }
    }
    return _searching;
}

- (GCDAsyncUdpSocket *)configure {
    if (!_configure) {
        _configure = [[GCDAsyncUdpSocket alloc] initWithDelegate:nil
                                                   delegateQueue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
                                                     socketQueue:self.configure_queue];
    }
    return _configure;
}

@end
