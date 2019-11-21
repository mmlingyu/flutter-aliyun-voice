//
//  QCloudConfig.h
//  QCloudSDK
//
//  Created by Sword on 2019/3/29.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QCloudConfig : NSObject

//通用配置参数
@property (nonatomic, strong, readonly) NSString *appId;        //腾讯云appId     基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, strong, readonly) NSString *secretId;     //腾讯云secretId  基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, strong, readonly) NSString *secretKey;    //腾讯云secretKey 基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, assign, readonly) NSInteger projectId;    //腾讯云projectId 基本概念见https://cloud.tencent.com/document/product/441/6194

//实时语音识别相关参数

@property (nonatomic, assign) BOOL usingSSL;                                  //默认NO 是否使用https, 由于NSURLSession存在ssl内存问题，开启后内层增长严重
@property (nonatomic, assign) BOOL enableDetectVolume;                        //是否检测录音音量的变化, 开启后sdk会实时回调音量变化
@property (nonatomic, assign) BOOL endRecognizeWhenDetectSilence;             //识别到静音是否结束识别, 默认YES
@property (nonatomic, assign) float silenceDetectDuration;                    //最大静音时间阈值, 超过silenceDetectDuration时间不说话则为静音, 单位:秒
@property (nonatomic, assign) BOOL enableDebugLog;                            //是否打开调试log, 默认YES
@property (nonatomic, assign) NSInteger sliceTime;                            //分片时间, 此参数影响语音分片长度, 单位:毫秒, 默认600ms
@property (nonatomic, strong) kQCloudASRRealTimeEngineModelType engineType;   //引擎识别类型, 见kQCloudASRRealTimeEngineModelType定义
@property (nonatomic, assign) float sensitive;                                //vad灵敏度，取值范围[1-5]，默认2.0
@property (nonatomic, assign) NSInteger flowSilenceTimeout;                   //vad超时时间，单位:毫秒, 取值范围(0-3000], 默认500
@property (nonatomic, assign) NSInteger requestTimeout;                       //网络请求超时时间，单位:秒, 取值范围[5-60], 默认20

/**
 * 初始化方法
 * @param appid     腾讯云appId     基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretId  腾讯云secretId  基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretKey 腾讯云secretKey 基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param projectId 腾讯云projectId 基本概念见https://cloud.tencent.com/document/product/441/6194
 */
- (instancetype)initWithAppId:(NSString *)appid
                     secretId:(NSString *)secretId
                    secretKey:(NSString *)secretKey
                    projectId:(NSInteger)projectId;

@end

NS_ASSUME_NONNULL_END
