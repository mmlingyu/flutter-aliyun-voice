//
//  QCloudFileParams.h
//  QCloudSDK
//
//  Created by Sword on 2019/8/8.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <QCloudSDK/QCloudSDK.h>

@interface QCloudFileRecognizeParams : QCloudCommonParams

@property (nonatomic, assign) NSInteger channelNum;
@property (nonatomic, strong) kQCloudASRRealTimeEngineModelType engineModelType;
/*
 * 可选,识别结果回调URL，用户自行搭建的用于接收识别结果的服务器地址， 长度小于2048字节
 */
@property (nonatomic, strong) NSString *callbackUrl;
@property (nonatomic, strong) NSString *requestId;
/*
 * 语音数据来源 QCloudAudioSourceTypeUrl:语音URL, QCloudAudioSourceTypeAudioData:语音数据（post body）。
 */
@property (nonatomic, assign) QCloudAudioSourceType sourceType;
/*
 * sourceType=QCloudAudioSourceTypeUrl时，必填
 */
@property (nonatomic, strong) NSString *audioUrl;
/*
 * sourceType=QCloudAudioSourceTypeAudioData时，必填
 */
@property (nonatomic, strong) NSData *audioData;
@property (nonatomic, assign, readonly) NSInteger resTextFormat;
@property (nonatomic, assign, readonly) NSInteger subServiceType;      //子服务类型。0：录音文件识别

@end
