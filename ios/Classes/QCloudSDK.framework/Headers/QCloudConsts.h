//
//  QCloudConsts.h
//  QCloudSDK
//
//  Created by Sword on 2019/2/27.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef QCloudConsts_h
#define QCloudConsts_h

FOUNDATION_EXPORT NSString *const kQCloudDomainOneSentenceURL;
FOUNDATION_EXPORT NSString *const kQCloudDomainASRRealTimeURL;

typedef NS_ENUM(NSInteger, QCloudAudioSourceType) {
    QCloudAudioSourceTypeNone = -1,          //未知
    QCloudAudioSourceTypeUrl = 0,            //语音url
    QCloudAudioSourceTypeAudioData,          //语音数据
};

typedef NSString *kQCloudVoiceFormat NS_TYPED_ENUM;
typedef NSString *kQCloudEngSerViceType NS_TYPED_ENUM;
typedef NSString *kQCloudAudioSubServiceType NS_TYPED_ENUM;

FOUNDATION_EXPORT kQCloudVoiceFormat const kQCloudVoiceFormatWAV;
FOUNDATION_EXPORT kQCloudVoiceFormat const kQCloudVoiceFormatMP3;
FOUNDATION_EXPORT kQCloudEngSerViceType const kQCloudEngSerViceType8k;
FOUNDATION_EXPORT kQCloudEngSerViceType const kQCloudEngSerViceType16k;

#pragma mark - asr real time
typedef NS_ENUM(NSInteger, QCloudASRRealTimeServiceType) {
    QCloudASRRealTimeServiceTypeNone = -1,              //未知
    QCloudASRRealTimeServiceTypeFull = 0,               //全文转写
    QCloudASRRealTimeServiceTypeStream,                 //实时流式识别
};

typedef NS_ENUM(NSInteger, QCloudASRRealTimeAudioType) {
    QCloudASRRealTimeAudioTypeNone = -1,
    QCloudASRRealTimeAudioTypeWAV = 1,
    QCloudASRRealTimeAudioTypeSpeex = 4,
    QCloudASRRealTimeAudioTypeSilk = 6
};

typedef NS_ENUM(NSInteger, QCloudASRRealTimeResultTextFormat) {
    QCloudASRRealTimeResultTextFormatNone = -1,
    QCloudASRRealTimeResultTextFormatUTF8 = 0,
    QCloudASRRealTimeResultTextFormatGB2312 = 1,
    QCloudASRRealTimeResultTextFormatBIG5 = 2,
    QCloudASRRealTimeResultTextFormatGBK = 3,
};

typedef NSString *kQCloudASRRealTimeEngineModelType NS_TYPED_ENUM;

typedef NS_ENUM(NSInteger, QCloudASRRealTimeRecognizeState) {
    QCloudASRRealTimeRecognizeStateNone = 0,
    QCloudASRRealTimeRecognizeStateStart,
    QCloudASRRealTimeRecognizeStateStop,
    QCloudASRRealTimeRecognizeStateRecognizing
};

FOUNDATION_EXPORT kQCloudASRRealTimeEngineModelType const kQCloudASRRealTimeEngineModelType_8k_0;           //8k通用
FOUNDATION_EXPORT kQCloudASRRealTimeEngineModelType const kQCloudASRRealTimeEngineModelType_16k_0;          //16k通用
FOUNDATION_EXPORT kQCloudASRRealTimeEngineModelType const kQCloudASRRealTimeEngineModelType_16k_en;         //16k英文
FOUNDATION_EXPORT kQCloudAudioSubServiceType const kQCloudAudioSubServiceTypeOneSentence;
FOUNDATION_EXPORT kQCloudAudioSubServiceType const kQCloudAudioSubServiceTypeRecordFile;

#endif
