//
//  QCloudCommonParamters.h
//  QCloudSDK
//
//  Created by Sword on 2019/2/26.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/* 详见 https://cloud.tencent.com/document/api/441/17365 签名方法 v1
 * 使用 HmacSHA1 和 HmacSHA256 签名方法时，公共参数需要统一放到请求串中，如下
 * 参数名称            类型      必选    描述
 * Action             String   是     具体操作的指令接口名称，例如想要调用云服务器的查询实例列表接口，则 Action 参数即为 DescribeInstances 。
 * Region             String   是     地域参数，用来标识希望操作哪个地域的数据。
 * Timestamp          Integer  是     当前 UNIX 时间戳，可记录发起 API 请求的时间。例如1529223702，如果与当前时间相差过大，会引起签名过期错误。
 * Nonce              Integer  是     随机正整数，与 Timestamp 联合起来，用于防止重放攻击。
 * SecretId           String   是     在云API密钥上申请的标识身份的 SecretId，一个 SecretId 对应唯一的 SecretKey ，而 SecretKey 会用来生成请求签名 Signature。
 * Signature          String   是     请求签名，用来验证此次请求的合法性，需要用户根据实际的输入参数计算得出。具体计算方法参见接口鉴权文档。
 * Version            String   是     API 的版本。例如 2017-03-12。
 * SignatureMethod    String   否     签名方式，目前支持 HmacSHA256 和 HmacSHA1。只有指定此参数为 HmacSHA256 时，才使用 HmacSHA256 算法验证签名，其他情况均使用 HmacSHA1 验证签名。
*/

NS_ASSUME_NONNULL_BEGIN

@interface QCloudCommonParams : NSObject

@property (nonatomic, strong) NSString *appid;
@property (nonatomic, assign) NSInteger projectId;   //optional 腾讯云项目 ID，可填 0，总长度不超过 1024 字节。
@property (nonatomic, strong) NSString *action;
@property (nonatomic, strong) NSString *region;
@property (nonatomic, assign) NSInteger timestamp;
@property (nonatomic, assign) NSInteger nonce;
@property (nonatomic, strong) NSString *secretId;
@property (nonatomic, strong) NSString *secretKey;
@property (nonatomic, strong) NSString *signature;
@property (nonatomic, strong) NSString *version;
@property (nonatomic, strong) NSString *signatureMethod;

@property (nonatomic, assign) BOOL usingSSL;

+ (instancetype)defaultRequestParams;

/**
 V3鉴权通用参数
 @return V3通用参数
 */
- (NSDictionary *)commonParamsForV3Authentication;

/**
 V1鉴权通用参数

 @return V1通用参数
 */
- (NSDictionary *)commonParamsForV1Authentication;

/**
 是否使用V3接口鉴权，默认NO

 @return 返回一个Bool值表示是否使用V3鉴权
 */
- (BOOL)usingV3Authentication;

@end

NS_ASSUME_NONNULL_END
