/*
 * Copyright 2015 Alibaba Group Holding Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * NlsRequest.h
 * NlsSdk
 * Created by Songsong Shao on 2018/5/8.
 * Copyright © 2018年 Alibaba idst. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface RecognizerRequestParam: NSObject

@property(nonatomic) NSString *serviceUrl;

/**
 * @brief 设置语音识别的appkey
 * @note 用于区分语音识别的模型类型
 */
@property(nonatomic) NSString *appkey;

/**
 * @brief 设置调用阿里云语音识别的accessToken
 * @note 鉴权使用 token不通过返回403错误。
 */
@property(nonatomic) NSString *token;

/**
 * @brief 设置语音格式
 * @note 默认opu，一般无需更改。
 */
@property(nonatomic) NSString *format;

/**
 * @brief 是否开启中间识别结果的输出 
 * @note 默认False
 */
@property(nonatomic) Boolean enableIntermediateResult;

/**
 * @brief 是否在后处理中添加标点，可选
 * @note 默认是False
 */
@property(nonatomic) Boolean enablePunctuationPrediction;

/**
 * @brief 是否在后处理中执行ITN
 * @note ，默认是False
 */
@property(nonatomic) Boolean enableInverseTextNormalization;

/**
 * @brief 是否启动云端静音检测(vad)
 * @note 默认是False
 */
@property(nonatomic) Boolean enableVoiceDetection;

/**
 * @brief 设置前置静音检测时间
 * @note 可选，单位是毫秒，超出后服务端将会发送RecognitionCompleted事件，结束本次识别，需要先设置enable_voice_detection为true
 */
@property(nonatomic) NSInteger maxStartSilence;

/**
 * @brief 设置后置静音检测时间
 * @note 可选，单位是毫秒，超出后服务端将会发送RecognitionCompleted事件，结束本次识别，需要先设置enable_voice_detection为true
 */
@property(nonatomic) NSInteger maxEndSilence;

/**
 * @brief 定制模型id,可选。如您通过POP API创建定制模型，通过本接口设置id。
 * @note 默认为null
 */
@property(nonatomic) NSString *customizationId;

/**
 * @brief 定制泛热词id,可选。如您通过POP API创建定制泛热词，通过本接口设置id。
 * @note 默认为null
 */
@property(nonatomic) NSString *vocabularyId;

/**
 * @brief 用户自定义字段值
 * @note ，可选
 */
@property(nonatomic) NSDictionary *params;

@end
