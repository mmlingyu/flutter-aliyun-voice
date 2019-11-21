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
 * Recgnizer.m
 * NlsDemo
 * Created by Songsong Shao on 2018/5/8.
 * Copyright © 2018年 Alibaba idst. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import "Recognizer.h"
#import "NlsVoiceRecorder.h"
@interface Recognizer()<NlsSpeechRecognizerDelegate,DemoVoiceRecorderDelegate>{
    Boolean recognizerStarted;
    NlsClientAdaptor *asrnlsClient;
    NlsSpeechRecognizerRequest *asrrecognizeRequest;
    DemoVoiceRecorder *voiceRecorder;
    RecognizerRequestParam *recognizeRequestParam;
}
@end

@implementation Recognizer

- (void)initASR {
    asrnlsClient = [[NlsClientAdaptor alloc]init];
     NSLog(@"asrnlsClient initASR!%@",asrnlsClient);
    recognizerStarted = false;
    //1.2 初始化录音recorder工具
    voiceRecorder = [[DemoVoiceRecorder alloc]init];
    voiceRecorder.delegate = self;
    //1.3 初始化识别参数类
    recognizeRequestParam = [[RecognizerRequestParam alloc]init];
    //1.4 设置log级别
    [asrnlsClient setLog:NULL logLevel:1];
    AccessToken *instance = [[AccessToken alloc] initWithAccessKeyId:@"LTAIRp9oYCCZGgce" andAccessSecret:@"8jAGLn8bFOyfjnDXXLy8ACFsBBKINA"];
    [instance apply];
    _token = instance.token;
}

- (void)startRecognize {
    if (recognizerStarted) {
        NSLog(@"already started!");
       // return;
    }
    //1.2 初始化录音recorder工具
   
    //2. 创建请求对象和开始识别
    if(asrrecognizeRequest!= NULL){
        [asrrecognizeRequest releaseRequest];
        asrrecognizeRequest = NULL;
    }
    //2.1 创建请求对象，设置NlsSpeechRecognizerDelegate回调
    asrrecognizeRequest = [asrnlsClient createRecognizerRequest];
    asrrecognizeRequest.delegate = self;
    
    //2.2 设置RecognizerRequestParam请求参数
    [recognizeRequestParam setFormat:@"opu"];
    //返回中间识别结果
    [recognizeRequestParam setEnableIntermediateResult:false];
    //设置文本规则，如识别'12345',如打开即识别为'12345',如设为NO则识别为'一二三四五'
    [recognizeRequestParam setEnableInverseTextNormalization:NO];
    //是否在识别结果中添加标点
    [recognizeRequestParam setEnablePunctuationPrediction:NO];
    
    //请使用https://help.aliyun.com/document_detail/72153.html 动态生成token
    [recognizeRequestParam setToken:_token];
    //或者采用本Demo的_generateTokeng方法获取token
    // <AccessKeyId> <AccessKeySecret> 请使用您的阿里云账户生成 https://ak-console.aliyun.com/
    //[_recognizeRequestParam setToken:[self _generateToken:@"AccessKeyId" withSecret:@"AccessKeyId"]];
    
    
    //请使用阿里云语音服务管控台(https://nls-portal.console.aliyun.com/)生成您的appkey
    [recognizeRequestParam setAppkey:@"dfsPYu5dBftDnSnm"];
    
    //是否开启静音检测
    [recognizeRequestParam setEnableVoiceDetection:YES];
    //允许的最大开始静音，可选，单位是毫秒，超出后服务端将会发送RecognitionCompleted事件，结束本次识别，需要先设置enable_voice_detection为true
    [recognizeRequestParam setMaxStartSilence:2000];
    //允许的最大结束静音，可选，单位是毫秒，超出后服务端将会发送RecognitionCompleted事件，结束本次识别，需要先设置enable_voice_detection为true
    [recognizeRequestParam setMaxEndSilence:800];
    
    
    //2.3 传入请求参数
    [asrrecognizeRequest setRecognizeParams:recognizeRequestParam];
    
    //2.4 启动录音和识别，将recognizerStarted置为true
    [voiceRecorder start];
    
    [asrrecognizeRequest start];
    recognizerStarted = true;
    
}

- (void)stopRecognize {
    //3 结束识别 停止录音，停止识别请求
    [voiceRecorder stop:true];
    [asrrecognizeRequest stop];
      recognizerStarted = false;
     asrrecognizeRequest = NULL;
}

/**
 *4. NlsSpeechRecognizerDelegate回调方法
 */
//4.1 识别回调，本次请求失败
-(void)OnTaskFailed:(NlsDelegateEvent)event statusCode:(NSString*)statusCode errorMessage:(NSString*)eMsg{
    [voiceRecorder stop:true];
    recognizerStarted = false;
    NSLog(@"OnTaskFailed, error message is: %@",eMsg);
}

//4.2 识别回调，服务端连接关闭
-(void)OnChannelClosed:(NlsDelegateEvent)event statusCode:(NSString*)statusCode errorMessage:(NSString*)eMsg{
    recognizerStarted = false;
    NSLog(@"OnChannelClosed, statusCode is: %@",statusCode);
    [voiceRecorder stop:true];
}

//4.3 识别回调，识别结果结束
-(void)OnRecognizedCompleted:(NlsDelegateEvent)event result:(NSString *)result statusCode:(NSString*)statusCode errorMessage:(NSString*)eMsg{
    recognizerStarted = false;
      NSLog(@"OnRecognizedCompleted, result is: %@",result);
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
    NSDictionary *ns = [self dictionaryWithJsonString:result];
    NSString * str =  [[ns objectForKey:@"payload"] objectForKey:@"result"];
    [dic setObject:str forKey:@"obj"];
    [dic setObject: [NSNumber numberWithInt:0] forKey:@"code"];
    [dic setObject: [NSNumber numberWithInt:1] forKey:@"type"];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ios.to.flutter" object:nil userInfo:dic];
}

- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString
{
    if (jsonString == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                    options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err)
    {
        NSLog(@"json解析失败：%@",err);
        return nil;
    }
    return dic;
}

//4.4 识别回调，识别中间结果
-(void)OnRecognizedResultChanged:(NlsDelegateEvent)event result:(NSString *)result statusCode:(NSString*)statusCode errorMessage:(NSString*)eMsg{
    
}

/**
 *5. 录音相关回调
 */
- (void)recorderDidStart {
    NSLog(@"Did start recorder!");
}

- (void)recorderDidStop {
    NSLog(@"Did stop recorder!");
}

- (void)voiceDidFail:(NSError *)error {
    NSLog(@"Did recorder error!");
}

//5.1 录音数据回调
- (void)voiceRecorded:(NSData *)frame {
    if (asrrecognizeRequest != nil &&recognizerStarted) {
        //录音线程回调的数据传给识别服务
        [asrrecognizeRequest sendAudio:frame length:(short)frame.length];
    }
}

- (void)voiceVolume:(NSInteger)volume {
// onVoiceVolume if you need.
}

/**
 *生成AccessToken的iOS实现
 *为安全考虑，我们建议您不要使用这个接口生成token
 *建议您采用服务端生成token，分发到服务端使用。
 *expireTime 为本次token的过期时间
 */

-(NSString*)_generateToken:(NSString*)accessKey withSecret:(NSString*)accessSecret{
    AccessToken *accessToken = [[AccessToken alloc]initWithAccessKeyId:accessKey andAccessSecret:accessSecret];
    [accessToken apply];
    NSLog(@"Token expire time is %ld",[accessToken expireTime]);
    return [accessToken token];
}


@end
