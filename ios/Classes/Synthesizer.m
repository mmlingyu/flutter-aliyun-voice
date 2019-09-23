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
 * Synthesizer.m
 * NlsDemo
 * Created by Songsong Shao on 2018/6/27.
 * Copyright © 2018年 Alibaba idst. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "Synthesizer.h"
#import "AccessToken.h"

@interface Synthesizer()<NlsSpeechSynthesizerDelegate,NLSPlayAudioDelegate>{
   
}
@end

@implementation Synthesizer

-(void)initTTS
{
//    [super viewDidLoad];
    //1. 全局参数初始化操作
    //1.1 初始化语音合成客户端
    _nlsClient = [[NlsClientAdaptor alloc]init];
    
    AccessToken *instance = [[AccessToken alloc] initWithAccessKeyId:@"LTAIRp9oYCCZGgce" andAccessSecret:@"8jAGLn8bFOyfjnDXXLy8ACFsBBKINA"];
    [instance apply];
    _token = instance.token;
     NSLog(@"andAccessSecret, token is: %@--%li--%li",instance.token,instance.expireTime,[self getTime]);
    //1.3 初始化合成参数类
    _requestParam = [[SynthesizerRequestParam alloc]init];
    //1.4 设置log级别
    [_nlsClient setLog:NULL logLevel:LOGINFO];
}

-(long )getTime{
   
    return [self getDateTimeTOMilliSeconds:[NSDate date]];

}

-(NSDate *)getDateTimeFromMilliSeconds:(long long) miliSeconds

{
    
    NSTimeInterval tempMilli = miliSeconds;
    
    NSTimeInterval seconds = tempMilli/1000.0;//这里的.0一定要加上，不然除下来的数据会被截断导致时间不一致
    
    NSLog(@"传入的时间戳=%f",seconds);
    
    return [NSDate dateWithTimeIntervalSince1970:seconds];
    
}

//将NSDate类型的时间转换为时间戳,从1970/1/1开始

-(long long)getDateTimeTOMilliSeconds:(NSDate *)datetime

{
    
    NSTimeInterval interval = [datetime timeIntervalSince1970];
    
    NSLog(@"转换的时间戳=%f",interval);
    
    long long totalMilliseconds = interval ;
    
    NSLog(@"totalMilliseconds=%llu",totalMilliseconds);
    
    return totalMilliseconds;
    
}

-(void)startSynthesizer : (NSString*)content {
    
    //2. 创建请求对象和开始语音合成
    if(_synthesizerRequest!= NULL){
        _synthesizerRequest = NULL;
    }
    //2.1 初始化语音播放类
    [_nlsAudioPlayer cleanup];
    _nlsAudioPlayer = [[NLSPlayAudio alloc]init];
    _nlsAudioPlayer.delegate = self;
    
    //2.2 创建请求对象，设置NlsSpeechSynthesizerRequest回调
    _synthesizerRequest = [_nlsClient createSynthesizerRequest];
    _synthesizerRequest.delegate = self;
    
    //2.3 获取页面合成文本
   // NSString *inputText = [textViewSynthesizer text];
    _content = content;
    //2.4 设置SynthesizerRequestParam请求参数
    [_requestParam setFormat:@"pcm"];
    [_requestParam setText:content];
    //请使用https://help.aliyun.com/document_detail/72153.html 动态生成token
    // <AccessKeyId> <AccessKeySecret> 请使用您的阿里云账户生成 https://ak-console.aliyun.com/
    [_requestParam setToken:_token];
    //请使用阿里云语音服务管控台(https://nls-portal.console.aliyun.com/)生成您的appkey
    [_requestParam setAppkey:@"dfsPYu5dBftDnSnm"];
    
    //2.5 传入请求参数
    [_synthesizerRequest setSynthesizerParams:_requestParam];
    
    //2.6 开始语音合成
    [_synthesizerRequest start];
    
    
}

-(void)cancelSynthsizer{
    [_synthesizerRequest cancel];
    [_nlsAudioPlayer cleanup];
}

-(void)stop{
    [self cancelSynthsizer];
}

/**
 *3. NlsSpeechSynthesizerDelegate接口回调
 */

//3.1 本次请求失败
- (void)OnTaskFailed:(NlsDelegateEvent)event statusCode:(NSString *)statusCode errorMessage:(NSString *)eMsg {
    NSLog(@"OnTaskFailed, statusCode is: %@ error message ：%@",statusCode,eMsg);
}

//3.2 服务端连接关闭
- (void)OnChannelClosed:(NlsDelegateEvent)event statusCode:(NSString *)statusCode errorMessage:(NSString *)eMsg {
    NSLog(@"OnChannelClosed, statusCode is: %@",statusCode);
}

//3.3 回调合成语音数据，通过NlsAudioPlayer工具播放
- (void)OnBinaryDataReceived:(NlsDelegateEvent)event voiceData:(Byte *)data length:(NSInteger)length{
    NSLog(@"Received voice data length %lu", length);
    [_nlsAudioPlayer process:data length:length];
}

//3.4 合成结束
- (void)OnSynthesizerCompleted:(NlsDelegateEvent)event result:(NSString *)result statusCode:(NSString *)statusCode errorMessage:(NSString *)eMsg {
    [_nlsAudioPlayer finishFeed:YES];
}

//3.5 合成开始
- (void)OnSynthesizerStarted:(NlsDelegateEvent)event result:(NSString *)result statusCode:(NSString *)statusCode errorMessage:(NSString *)eMsg {
}

- (void)playDone {
    //播放结束的回调
    //需要在OnSynthesizerCompleted 中调用[_nlsAudioPlayer finishFeed:YES];
    [self startSynthesizer:_content];
}

@end
