//
//  crypt.h
//  uecc-sdk
//
//  Created by CH on 16/4/27.
//  Copyright © 2016年 chang hong. All rights reserved.
//

#ifndef crypt_h
#define crypt_h

#include "uECC.h"

#define PUBKEY_LEN uECC_BYTES + 1
#define SCRECT_LEN uECC_BYTES

/**
 * @brief 调用此方法来初始化ECC密钥信息，生成ECC的私钥和公钥，默认使用uECC_secp160r1
 * @return 1: 生成成功 0:生成失败
 */
int chcrypt_context_init();

/**
 * @brief  获取自己的公钥
 * @param  pubKey 自己的公钥(压缩后的公钥)存放地址
 */
void chcrypt_get_pubkey(uint8_t *pubKey);

/**
 * @brief  计算共享密钥（用于aes加／解密的密钥）
 * @param  pubKeyPeerC 对方的公钥（压缩后的公钥），生成的共享密钥放置于_g_ekey.secretKey中
 * @param  screctKey   存放共享密钥的地址（用于AES加／解密的密钥）, 长度应该为
 */
void chcrypt_generate_screctkey(const uint8_t *pubKeyPeerC, uint8_t *screctKey);

/**
 * @brief 加密数据
 * @param screct      密钥
 * @param pIn         待加密的数据
 * @param len         待加密数据的长度
 * @param pOut        加密后的数据
 * @param max_len     加密后数据的最大长度
 * @return            加密后数据的长度
 */
int chcrypt_encrypt(uint8_t *screct, const char *pIn, unsigned int len, char *pOut, unsigned int max_len);

/**
 * @brief 解密数据
 * @param screct      密钥
 * @param pIn         待解密的数据
 * @param len         待解密数据的长度
 * @param pOut        解密后的数据
 * @param max_len     解密后数据的最大长度
 * @return            解密后数据的长度
 */
int chcrypt_decrypt(uint8_t *screctKey, const char *pIn, unsigned int len, char *pOut, unsigned int max_len);


#endif /* crypt_h */
