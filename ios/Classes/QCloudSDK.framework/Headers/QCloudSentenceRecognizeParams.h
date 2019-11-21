//
//  QCloudOneSentenceRecognitionParameters.h
//  QCloudSDK
//
//  Created by Sword on 2019/2/26.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "QCloudCommonParams.h"

NS_ASSUME_NONNULL_BEGIN


@interface QCloudSentenceRecognizeParams : QCloudCommonParams

@property (nonatomic, strong) kQCloudEngSerViceType engSerViceType;     //引擎类型。8k：电话 8k 通用模型；16k：16k 通用模型。只支持单声道音频识别。
@property (nonatomic, strong) kQCloudVoiceFormat voiceFormat;           //识别音频的音频格式（支持mp3,wav）。
@property (nonatomic, assign) QCloudAudioSourceType sourceType;         //语音数据来源。0：语音 URL；1：语音数据（post body）。

@property (nonatomic, strong) NSString *url;                            //语音URL，公网可下载。当 SourceType 值为 QCloudAudioSourceTypeUrl 时须填写该字段，为 QCloudAudioSourceTypeAudioData 时不填；URL 的长度小于2048字符，音频时间长度要小于60s
@property (nonatomic, strong) NSData *data;                             //语音数据，语音数据格式必须与voiceFormat匹配。当SourceType为QCloudAudioSourceTypeAudioData时必须填写，为QCloudAudioSourceTypeUrl可不写。

@property (nonatomic, strong) NSString *usrAudioKey;                    //用户端对此任务的唯一标识，用户自助生成，用于用户查找识别结果
@property (nonatomic, assign) NSInteger subServiceType;                 //子服务类型。2:一句话识别，固定值。

@end

NS_ASSUME_NONNULL_END
