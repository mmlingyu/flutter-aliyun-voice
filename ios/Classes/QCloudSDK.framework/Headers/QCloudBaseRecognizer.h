//
//  QCloudBaseRecognizer.h
//  QCloudSDK
//
//  Created by Sword on 2019/2/27.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class QCloudAudioRecorder;
@class QCloudConfig;

@interface QCloudBaseRecognizer : NSObject

@property (nonatomic, strong, readonly) QCloudConfig *config;

/**
 * 初始化方法，使用内置录音器采集音频
 * @param config 配置参数，详见QCloudConfig定义
 */
- (instancetype)initWithConfig:(QCloudConfig *)config;
/**
 * 通过appId secretId secretKey初始化
 * @param appid     腾讯云appId        基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretId  腾讯云secretId     基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretKey 腾讯云secretKey    基本概念见https://cloud.tencent.com/document/product/441/6194
 */
- (instancetype)initWithAppId:(NSString *)appid secretId:(NSString *)secretId secretKey:(NSString *)secretKey;

@end

NS_ASSUME_NONNULL_END
