#import <AVFoundation/AVAudioSession.h>
#import "Aliyun.h"
#import "QCloudTTS.h"


@interface Aliyun() <QCloudTTSDelegate>
@end
@implementation Aliyun;

QCloudTTS * apiObj;

- (void) initTTS{
    apiObj= [[QCloudTTS alloc] initWithAppId:@"1258066428" secretId:@"AKIDP6c0BBIbyEHDzmg2OdgcQ6FIAqOlC97e" secretKey:@"rvlts33rUaWHiy50kNr7Cya2INI6g7HH"];
    apiObj.ttsDelegate = self;
    
    QCloudTTSConfig *config = [QCloudTTSConfig getInstance];
    config.projectId = 1160443;
    config.volume = VolumeLevelThree;
    config.speed = SpeedTypeNormal;
    config.voiceType = VoiceTypeAffinityFemale;
    config.language = PrimaryChinese;
}

-(void)pauseOrResume : (NSString*) isPause{
   // NSLog(@"转换的时间戳=%f",isPause);
    bool pause = [isPause isEqualToString : @"pause"];
    if(pause){
        [apiObj pauseTTS];
    }else{
        [apiObj resumeTTS];
    }
}


- (void)stop{
    [apiObj stopTTS];
}


- (void)releaseIt{
    [apiObj stopTTS];
}

- (void)speak :(NSString*)content  {
    _content = content;
    [apiObj startTTS:content fail:^(NSString *code, NSString *errMsg) {
        //接口异常处理
       // NSLog("@error:%@“,errMsg);
    }];

}

//开始播放
- (void) onTTSPlayStart{
    
    NSLog(@"onTTSPlayStart");
    
}

//音频缓冲中

- (void) onTTSPlayWait{
    
    NSLog(@"onTTSPlayWait");
    
}

//缓冲完成，继续播放

- (void) onTTSPlayContinue{
    
    NSLog(@"onTTSPlayContinue");
    
}

//播放中止

- (void) onTTSPlayStop{
    
    NSLog(@"onTTSPlayStop");
    
}

//播放结束

- (void) onTTSPlayEnd{
    
    NSLog(@"onTTSPlayEnd");
    [apiObj startTTS:_content fail:^(NSString *code, NSString *errMsg) {
        //接口异常处理
        // NSLog("@error:%@“,errMsg);
    }];
}

@end
