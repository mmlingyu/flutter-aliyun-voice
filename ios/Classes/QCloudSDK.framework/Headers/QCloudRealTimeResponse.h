//
//  QCloudRealTimeResponse.h
//  QCloudSDK
//
//  Created by Sword on 2019/4/3.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, QCloudRealTimeResponseCode) {
    QCloudRealTimeResponseCodeNone = -1,                 //未知
    QCloudRealTimeResponseCodeOk = 0,                    //成功
    QCloudRealTimeResponseCodeGetAudioSliceError = 100,  //获取语音分片信息失败
    QCloudRealTimeResponseCodeAudioSliceTooBig = 101,    //语音分片过大
    QCloudRealTimeResponseCodeInvalidParams = 102,       //参数不合法
    QCloudRealTimeResponseCodeAccessDBError = 103,       //访问数据库失败
    QCloudRealTimeResponseCodeWrongAppid = 104,          //appid未注册
    QCloudRealTimeResponseCodeTemplateNotExist = 105,    //模版不存在
    QCloudRealTimeResponseCodeUnusedTemplate = 106,      //模版停用
    QCloudRealTimeResponseCodeAuthencationError = 107,   //鉴权失败
    QCloudRealTimeResponseCodeSignError = 108,           //拼接签名串失败
    QCloudRealTimeResponseCodeGetIPPortError = 109,      //获取ip port失败
    QCloudRealTimeResponseCodeNeedRealodUpload = 110,    //后台识别服务器故障，请求seq=0重传
    QCloudRealTimeResponseCodeDataFormatError = 111,     //后台识别模块回包格式错误
    QCloudRealTimeResponseCodeNullAudio = 112,           //语音分片为空
    QCloudRealTimeResponseCodeServerTimeout = 113,       //后台识别服务超时
    QCloudRealTimeResponseCodeNoNetwork = -1009,
    QCloudRealTimeResponseCodeClientTimeout = -1001,     //手机网路存在问题，请求超时
};

/**
 * 语音识别请求回包的基类
 */
@interface QCloudRealTimeResponse : NSObject

/** 任务描述代码，为retCode = 0时标示成功，其他表示为失败 */
@property (nonatomic, assign) QCloudRealTimeResponseCode code;
/** code对应的描述信息 */
@property (nonatomic, strong) NSString *message;
/** 语音流的识别id */
@property (nonatomic, strong) NSString *voiceId;          
/** 当前语音流的识别结果 */
@property (nonatomic, strong) NSString *text;
/** 语音包序列号，注意:不是语音流序列号*/
@property (nonatomic, assign) NSInteger seq;
/** 识别到的总文本 */
@property (nonatomic, strong) NSString *recognizedText;
/** 语音分片请求参数 */
@property (nonatomic, strong) NSDictionary *requestParameters;

- (instancetype)initWithDictionary:(NSDictionary *)dic requestParameters:(NSDictionary *)requestParameters;

- (NSError *)getError;
- (BOOL)isEnd;

@end

NS_ASSUME_NONNULL_END

