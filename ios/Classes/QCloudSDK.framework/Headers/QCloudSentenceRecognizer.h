//
//  QCloudSentenceRecognizer.h
//  QCloudSDK
//
//  Created by Sword on 2019/2/27.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "QCloudBaseRecognizer.h"

NS_ASSUME_NONNULL_BEGIN

@class QCloudSentenceRecognizer;

@protocol QCloudSentenceRecognizerDelegate <NSObject>

@required
/**
 * 一句话识别回调delegate
 * @param text 识别结果文本，error=nil此字段才存在值
 * @param error 错误信息，详细错误信息见error.domain和error.userInfo字段
 * @param resultData 识别原始数据
 */
- (void)oneSentenceRecognizerDidRecognize:(QCloudSentenceRecognizer *)recognizer text:(nullable NSString *)text error:(nullable NSError *)error resultData:(nullable NSDictionary *)resultData;

@optional
/**
 * 开始录音回调
 */
- (void)oneSentenceRecognizerDidStartRecord:(QCloudSentenceRecognizer *)recognizer error:(nullable NSError *)error;
/**
 * 结束录音回调, SDK通过此方法回调后内部开始上报语音数据进行识别
 */
- (void)oneSentenceRecognizerDidEndRecord:(QCloudSentenceRecognizer *)recognizer;
/**
 * 录音音量实时回调用
 * @param recognizer 实时语音识别实例
 * @param volume 声音音量，取值范围（-40-0)
 */
- (void)oneSentenceRecognizerDidUpdateVolume:(QCloudSentenceRecognizer *)recognizer volume:(float)volume;


@end

@class QCloudSentenceRecognizeParams;

@interface QCloudSentenceRecognizer : QCloudBaseRecognizer

@property (nonatomic, weak) id<QCloudSentenceRecognizerDelegate> delegate;
@property (nonatomic, assign, readonly) float volume;
/**
 * 通过sdk内置录音器开始一句话识别，录音时长超过60秒或音频数据超过1m，自动调用stopRecognizeWithRecorder结束录音。
 * 开始录音后，可以直接调用stopRecognizeWithRecorder结束录音, SDK会回调识别结果
 */
- (void)startRecognizeWithRecorder;
/**
 * 通过sdk内置录音器开始一句话识别，调用此方法主动停止录音后，SDK会自动上报录音语音数据进行识别
 */
- (void)stopRecognizeWithRecorder;
/**
 * 通过语音url进行一句话识别的快捷入口
 * @param url 资源url 如http://www.qq.music/hello.mp3
 * @param voiceFormat 语音数据格式，取值见kQCloudVoiceFormat定义
 * @param frequence 语音数据采样率，取值见kQCloudEngSerViceType定义
 * @return YES 本地参数校验通过，成功发起请求 NO:参数校验不通过
 */
- (BOOL)recoginizeWithUrl:(NSString *)url voiceFormat:(kQCloudVoiceFormat)voiceFormat frequence:(kQCloudEngSerViceType)frequence;
/**
 * 通过语音数据进行一句话识别的快捷入口
 * @param audioData 语音数据
 * @param voiceFormat 语音数据格式，取值见kQCloudVoiceFormat定义
 * @param frequence 语音数据采样率，取值见kQCloudEngSerViceType定义
 * @return YES 本地参数校验通过，成功发起请求 NO:参数校验不通过
 */
- (BOOL)recoginizeWithData:(NSData *)audioData voiceFormat:(kQCloudVoiceFormat)voiceFormat frequence:(kQCloudEngSerViceType)frequence;
/**
 * 获取通用参数，调用者只需关注需要修改的参数
 */
- (QCloudSentenceRecognizeParams *)defaultRecognitionParams;
/**
 * 通过QCloudOneSentenceRecognitionParams调用一句话识别, 调用[QCloudCommonParams defaultRequestParams]方法获取默认参数，然后根据需求设置参数
 * @return YES:本地参数校验通过，成功发起请求 NO:参数校验不通过
 */
- (BOOL)recognizeWithParams:(QCloudSentenceRecognizeParams *)params;

@end

NS_ASSUME_NONNULL_END
