//
//  DirectLink.m
//  DirectLink
//
//  Created by GeHaitong on 15/4/21.
//  Copyright (c) 2015年 xpg. All rights reserved.
//

#import "DirectLink.h"

#include <Foundation/Foundation.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#import "GCDAsyncUdpSocket.h"

@interface DirectLink()

@property (nonatomic, assign) BOOL isStarted;

@property (strong, nonatomic) GCDAsyncUdpSocket *recvUdpSocket;

- (id)initInternal___;
- (void)setStarted:(NSNumber *)started;

@end

static DirectLink *sharedInstance = nil;
static BOOL isLoop = NO;
static unsigned char ConfigPacket[1024] = {0};
//static unsigned char DestPacket[1024] = {0};
static unsigned char ConfigPacketLen = 0;

static const unsigned char __crc8_tbl[256]=
{
    0x00,0x91,0xe3,0x72,0x07,0x96,0xe4,0x75,
    0x0e,0x9f,0xed,0x7c,0x09,0x98,0xea,0x7b,
    0x1c,0x8d,0xff,0x6e,0x1b,0x8a,0xf8,0x69,
    0x12,0x83,0xf1,0x60,0x15,0x84,0xf6,0x67,
    0x38,0xa9,0xdb,0x4a,0x3f,0xae,0xdc,0x4d,
    0x36,0xa7,0xd5,0x44,0x31,0xa0,0xd2,0x43,
    0x24,0xb5,0xc7,0x56,0x23,0xb2,0xc0,0x51,
    0x2a,0xbb,0xc9,0x58,0x2d,0xbc,0xce,0x5f,
    0x70,0xe1,0x93,0x02,0x77,0xe6,0x94,0x05,
    0x7e,0xef,0x9d,0x0c,0x79,0xe8,0x9a,0x0b,
    0x6c,0xfd,0x8f,0x1e,0x6b,0xfa,0x88,0x19,
    0x62,0xf3,0x81,0x10,0x65,0xf4,0x86,0x17,
    0x48,0xd9,0xab,0x3a,0x4f,0xde,0xac,0x3d,
    0x46,0xd7,0xa5,0x34,0x41,0xd0,0xa2,0x33,
    0x54,0xc5,0xb7,0x26,0x53,0xc2,0xb0,0x21,
    0x5a,0xcb,0xb9,0x28,0x5d,0xcc,0xbe,0x2f,
    0xe0,0x71,0x03,0x92,0xe7,0x76,0x04,0x95,
    0xee,0x7f,0x0d,0x9c,0xe9,0x78,0x0a,0x9b,
    0xfc,0x6d,0x1f,0x8e,0xfb,0x6a,0x18,0x89,
    0xf2,0x63,0x11,0x80,0xf5,0x64,0x16,0x87,
    0xd8,0x49,0x3b,0xaa,0xdf,0x4e,0x3c,0xad,
    0xd6,0x47,0x35,0xa4,0xd1,0x40,0x32,0xa3,
    0xc4,0x55,0x27,0xb6,0xc3,0x52,0x20,0xb1,
    0xca,0x5b,0x29,0xb8,0xcd,0x5c,0x2e,0xbf,
    0x90,0x01,0x73,0xe2,0x97,0x06,0x74,0xe5,
    0x9e,0x0f,0x7d,0xec,0x99,0x08,0x7a,0xeb,
    0x8c,0x1d,0x6f,0xfe,0x8b,0x1a,0x68,0xf9,
    0x82,0x13,0x61,0xf0,0x85,0x14,0x66,0xf7,
    0xa8,0x39,0x4b,0xda,0xaf,0x3e,0x4c,0xdd,
    0xa6,0x37,0x45,0xd4,0xa1,0x30,0x42,0xd3,
    0xb4,0x25,0x57,0xc6,0xb3,0x22,0x50,0xc1,
    0xba,0x2b,0x59,0xc8,0xbd,0x2c,0x5e,0xcf
};

/*   NST_GetCrc8   */
/*-------------------------------------------------------------------------
	Description:
 calculate crc8 for input data
 
	Arguments:
 ptr - input data buffer
 len - input data length
 
	Return Value:
 crc8 result
 
	Note:
 -------------------------------------------------------------------------*/
static unsigned char NST_GetCrc8(unsigned char *ptr, unsigned int len)
{
    unsigned char crc8,data;
    
    crc8=0;
    while(len--!=0)
    {
        data = *ptr++;
        crc8=__crc8_tbl[crc8^data];
    }
    return crc8;
}

/*   NST_BuildConfigPacket   */
/*-------------------------------------------------------------------------
	Description:
 build Packet with config information
 
	Arguments:
 Ssid - network ssid, 0 ~ 32 ascii bytes
 Key - network key, 0 ~ 64 ascii bytes
 
	Return Value:
 
	Note:
 -------------------------------------------------------------------------*/
static void NST_BuildConfigPacket(const char *Ssid, const char *Key)
{
    unsigned char * Ptr = ConfigPacket;
    unsigned char SsidLen = 0;
    unsigned char KeyLen = 0;
    unsigned char Crc8 = 0;
    
    memset(ConfigPacket, 0, sizeof(ConfigPacket));
    memset(Ptr, 0x04, 8);
    Ptr += 8;
    
    *Ptr++ = 0x05;
    *Ptr++ = 0x06;
    *Ptr++ = 0x07;
    *Ptr++ = 0x08;
    
    // ssid len
    if (Ssid != NULL)
        SsidLen = (unsigned char)strlen(Ssid);
    *Ptr++ = SsidLen;
    
    // ssid
    if (SsidLen != 0)
    {
        memcpy(Ptr, Ssid, SsidLen);
        Ptr += SsidLen;
    }
    
    // key len
    if (Key != NULL)
        KeyLen = (unsigned char)strlen(Key);
    *Ptr++ = KeyLen;
    
    // key
    if (KeyLen != 0)
    {
        memcpy(Ptr, Key, KeyLen);
        Ptr += KeyLen;
    }
    
    // crc8
    Crc8 = (unsigned char)NST_GetCrc8((ConfigPacket + 12), (unsigned int)(Ptr - ConfigPacket - 12));
    *Ptr++ = (Crc8 & 0xF0) >> 4;
    *Ptr++ = Crc8 & 0x0F;
    
    *Ptr++ = 0x09;
    *Ptr++ = 0x0A;
    *Ptr++ = 0x0B;
    *Ptr++ = 0x0C;
    
    ConfigPacketLen = (unsigned char)(Ptr - ConfigPacket);
}

/*   NST_SendPacket   */
/*-------------------------------------------------------------------------
	Description:
 send config packet
 
	Arguments:
 
	Return Value:
 
	Note:
 -------------------------------------------------------------------------*/
static void NST_SendPacket()
{
    int SendSocket = 0;
    struct sockaddr_in RecvAddr;
    int Port = 60001;
    int i, j, k, l;
    int so_broadcast=1;
    
    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(SendSocket < 0)
        NSLog(@"Error: socket invalid");
    
    // Set socket option, enable broadcast
    if (0 > setsockopt(SendSocket, SOL_SOCKET, SO_NOSIGPIPE, &so_broadcast, sizeof(so_broadcast)))
        NSLog(@"Set broadcast error.");
    
    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // and the specified port number.
    memset(&RecvAddr, 0, sizeof(struct sockaddr_in));
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("239.1.2.110");//
    
    //---------------------------------------------
    // Send a datagram to the receiver
    printf("Sending datagram to the receiver...\n");
    [[DirectLink sharedInstance] performSelectorOnMainThread:@selector(setStarted:) withObject:@YES waitUntilDone:YES];
    while (isLoop)
    {
        k = 1;
        for (i = 0; i < ConfigPacketLen; i++)
        {
            l = ConfigPacket[i];
            l = l ? l : 129;
            l = k ? (156 + l) : (156 - l);
            k = 1 - k;
            
            for (j = 0; j < 20; j++)
            {
             long result =   sendto(SendSocket,
                       (char *)ConfigPacket,
                       l,
                       0,
                       (struct sockaddr *) &RecvAddr,
                       sizeof(RecvAddr));
                
                if (result == -1) {
                     NSLog(@"did not send, error=%s",strerror(errno));
                    [[DirectLink sharedInstance] performSelectorOnMainThread:@selector(setStarted:) withObject:@NO waitUntilDone:NO];
                    [[DirectLink sharedInstance] performSelectorOnMainThread:@selector(stop) withObject:nil waitUntilDone:NO];
                    close(SendSocket);
                    return;
                    
                }
                usleep(3000);		// wait 3 ms
            }
            usleep(30000);		// wait 30 ms
        }
    }
    [[DirectLink sharedInstance] performSelectorOnMainThread:@selector(setStarted:) withObject:@NO waitUntilDone:NO];
    
    //---------------------------------------------
    // When the application is finished sending, close the socket.
    printf("Finished sending. Closing socket.\n");
    close(SendSocket);
    
    //---------------------------------------------
    // quit.
    printf("Exiting.\n");
}

/*   NST_PushConfig   */
/*-------------------------------------------------------------------------
	Description:
 push the input config information to the direct config peer
 
	Arguments:
 Ssid - network ssid, 0 ~ 32 ascii bytes, set null to use default ssid (current network ssid)
 Key - network key, 0 ~ 64 ascii bytes, set null to use no encryption mode
 
	Return Value:
 
	Note:
 -------------------------------------------------------------------------*/
static void NST_PushConfig(const char *Ssid, const char *Key)
{
    NST_BuildConfigPacket(Ssid, Key);
    
    NST_SendPacket();
}

@implementation DirectLink

+ (instancetype)sharedInstance
{
    if(nil == sharedInstance)
    {
        sharedInstance = [[DirectLink alloc] initInternal___];
    }
    return sharedInstance;
}

- (id)initInternal___
{
    self = [super init];
    return self;
}

- (void)startWithSSID:(NSString *)ssid password:(NSString *)password
{
    if(!self.isStarted)
    {
        //等待接收插座反馈的udp广播
        NSError *error = nil;
         _recvUdpSocket = nil;
        if (![self.recvUdpSocket beginReceiving:&error])
        {
            NSLog(@"Error starting server (recv): %@", error);
        }
        
        isLoop = YES;
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NST_PushConfig([ssid UTF8String], [password UTF8String]);
        });
    }
}

- (void)stop
{
    isLoop = NO;
    
    [self.recvUdpSocket close];
    self.recvUdpSocket = nil;
}

- (void)setStarted:(NSNumber *)started
{
    self.isStarted = [started boolValue];
}

//用于接收UDP数据报的Socket
- (GCDAsyncUdpSocket *) recvUdpSocket
{
    if(!_recvUdpSocket)
    {
        _recvUdpSocket = [[GCDAsyncUdpSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)];
        
        NSError *error = nil;
        
        if (![_recvUdpSocket bindToPort:60002 error:&error])
        //if (![_recvUdpSocket bindToPort:7788 error:&error])
        {
            NSLog(@"Error starting server (bind): %@", error);
            _recvUdpSocket = nil;
        }
    }
    return _recvUdpSocket;
}

#pragma mark GCDAsyncUdpSocketDelegate

- (void)udpSocket:(GCDAsyncUdpSocket *)sock didReceiveData:(NSData *)data
      fromAddress:(NSData *)address
withFilterContext:(id)filterContext
{
    if([self.delegate respondsToSelector:@selector(directLink:didReceiveData:fromAddress:)])
    {
        [self.delegate directLink:self didReceiveData:data fromAddress:address];
    }
}

@end
