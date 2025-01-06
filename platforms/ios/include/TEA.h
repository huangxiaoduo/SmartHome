//
//  TEA.h
//  IPP
//
//  Created by YangHaiLong on 19/5/15.
//  Copyright (c) 2015年 changhong. All rights reserved.
//

#ifndef IPP_TEA_h
#define IPP_TEA_h

	// warning these 2 methods has memory leak
char* encry_tea(const char* content,const char* key,unsigned int rounds);
char* decry_tea(const char* encrypt,const char* key,unsigned int rounds);

#endif
