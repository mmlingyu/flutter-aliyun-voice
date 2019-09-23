#import "AliyunVoicePlugin.h"
#import "Baidu.h"
#import "Synthesizer.h"

@implementation AliyunVoicePlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"aliyun_voice"
            binaryMessenger:[registrar messenger]];
  AliyunVoicePlugin* instance = [[AliyunVoicePlugin alloc] init];
  [registrar addMethodCallDelegate:instance channel:channel];
}
//@dynamic <#property#> Synthesizer* ;
Synthesizer *aliyun;

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if(aliyun == NULL){
        aliyun=  [[Synthesizer alloc] init];
    }
  if ([@"getPlatformVersion" isEqualToString:call.method]) {
    result([@"iOS " stringByAppendingString:[[UIDevice currentDevice] systemVersion]]);
  } else if ([@"initTTS" isEqualToString:call.method]) {
      [aliyun initTTS];
      result(@"success");
  } else if ([@"speak" isEqualToString:call.method]) {
      //[Baidu speak:call.arguments[@"content"]];
      [aliyun startSynthesizer:call.arguments[@"content"]];
      result(@"success");
  }else if ([@"stop" isEqualToString:call.method]) {
     // [[Baidu CDSingletonBaidu] stop];
      [aliyun stop];
  }else if ([@"release" isEqualToString:call.method]) {
      [aliyun stop];
  }else if ([@"pauseOrResume" isEqualToString:call.method]) {
      NSString* string = call.arguments[@"status"];
      bool pause = [string isEqualToString : @"pause"];
      //[Baidu pauseOrResume :  &pause];
       [aliyun stop];
  }

    
  else {
    result(FlutterMethodNotImplemented);
  }
}

@end
