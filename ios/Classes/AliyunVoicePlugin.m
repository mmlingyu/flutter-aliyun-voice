#import "AliyunVoicePlugin.h"
#import "Synthesizer.h"
#import "Aliyun.h"
#import "Recognizer.h"
@implementation AliyunVoicePlugin{
    Aliyun *aliyun;
    Recognizer *asr;
}
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"aliyun_voice"
            binaryMessenger:[registrar messenger]];
  AliyunVoicePlugin* instance = [[AliyunVoicePlugin alloc] init];
  [registrar addMethodCallDelegate:instance channel:channel];
}
//@dynamic <#property#> Synthesizer* ;
//Synthesizer *aliyun;

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result{
    if(aliyun == NULL){
        aliyun=  [[Aliyun alloc] init];
    }
    if(asr == NULL){
        asr = [[Recognizer alloc] init];
    }
  if ([@"getPlatformVersion" isEqualToString:call.method]) {
    result([@"iOS " stringByAppendingString:[[UIDevice currentDevice] systemVersion]]);
  } else if ([@"initTTS" isEqualToString:call.method]) {
      [aliyun initTTS];
      [asr initASR];
      result(@"success");
  } else if ([@"speak" isEqualToString:call.method]) {
      [aliyun speak:call.arguments[@"content"]];
      //[aliyun startSynthesizer:call.arguments[@"content"]];
      result(@"success");
  }else if ([@"stop" isEqualToString:call.method]) {
     // [[Baidu CDSingletonBaidu] stop];
      [aliyun stop];
  }else if ([@"release" isEqualToString:call.method]) {
      [aliyun stop];
  }else if ([@"pauseOrResume" isEqualToString:call.method]) {
      [aliyun pauseOrResume:call.arguments[@"status"]];
      // [aliyun stop];
  }else if ([@"startASR" isEqualToString:call.method]) {
      [asr startRecognize];
  }else if ([@"stopASR" isEqualToString:call.method]) {
      [asr stopRecognize];
      // [aliyun stop];
  }
    

    
  else {
    result(FlutterMethodNotImplemented);
  }
}

@end
