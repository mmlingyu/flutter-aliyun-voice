//
//  Generated file. Do not edit.
//

#import "Baidu.h"
#import "BDSSpeechSynthesizer.h"
#import <AVFoundation/AVFoundation.h>
@implementation Baidu


NSString* APP_ID = @"17281319";
NSString* API_KEY = @"Fb3KjlOUaxYx1LmvzkA7WEcQ";
NSString* SECRET_KEY = @"Nz6P6gL2k3d3GXZshkGnfsqknjepeizx";


+ (Baidu *)CDSingletonBaidu
{
    static Baidu * cdSingle= nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        cdSingle = [[Baidu alloc] init];
    });
    return cdSingle;
}

+ (void) initTTS {
    NSLog(@"开始初始化");
    //[[BDSSpeechSynthesizer sharedInstance] setApiKey:API_KEY withSecretKey:SECRET_KEY];
    
    //[[AVAudioSession sharedInstance]setCategory:AVAudioSessionCategoryPlayback error:nil];
    //[[BDSSpeechSynthesizer sharedInstance] setSynthParam:@(BDS_SYNTHESIZER_SPEAKER_FEMALE) forKey:BDS_SYNTHESIZER_PARAM_SPEAKER];
    
    //[[BDSSpeechSynthesizer sharedInstance] setSynthesizerDelegate:self];
     [BDSSpeechSynthesizer setLogLevel:BDS_PUBLIC_LOG_VERBOSE];
    //[[BDSSpeechSynthesizer sharedInstance] setSynthesizerDelegate:self];
    [self configureOnlineTTS];
   // [self configureOfflineTTS];
}

+(void)configureOnlineTTS{
    
    [[BDSSpeechSynthesizer sharedInstance] setApiKey:API_KEY withSecretKey:SECRET_KEY];
    
    [[AVAudioSession sharedInstance]setCategory:AVAudioSessionCategoryPlayback error:nil];
    [[BDSSpeechSynthesizer sharedInstance] setSynthParam:@(BDS_SYNTHESIZER_SPEAKER_FEMALE) forKey:BDS_SYNTHESIZER_PARAM_SPEAKER];
    //    [[BDSSpeechSynthesizer sharedInstance] setSynthParam:@(10) forKey:BDS_SYNTHESIZER_PARAM_ONLINE_REQUEST_TIMEOUT];
    
}

-(void)configureOfflineTTS{
    
    NSError *err = nil;
    // 在这里选择不同的离线音库（请在XCode中Add相应的资源文件），同一时间只能load一个离线音库。根据网络状况和配置，SDK可能会自动切换到离线合成。
    NSString* offlineEngineSpeechData = [[NSBundle mainBundle] pathForResource:@"Chinese_And_English_Speech_Female" ofType:@"dat"];
    
    NSString* offlineChineseAndEnglishTextData = [[NSBundle mainBundle] pathForResource:@"Chinese_And_English_Text" ofType:@"dat"];
    
    err = [[BDSSpeechSynthesizer sharedInstance] loadOfflineEngine:offlineChineseAndEnglishTextData speechDataPath:offlineEngineSpeechData licenseFilePath:nil withAppCode:APP_ID];
    if(err){
         NSLog(@"开始Offline TTS init failed");
        return;
    }
   
}

+ (void)speak : (NSString*)content{
    // 获得合成器实例
    NSLog(@"开始合成%@", content);
    // 开始合成并播放
    NSError* speakError = nil;
   
    if([[BDSSpeechSynthesizer sharedInstance] speakSentence:content withError:&speakError] == -1){
        // 错误
        NSLog(@"错误: %ld, %@", (long)speakError.code, speakError.localizedDescription);
    }
}

+ (void) releaseVoice{
    [BDSSpeechSynthesizer releaseInstance] ;
}

+ (void) stop{
    [[BDSSpeechSynthesizer sharedInstance] cancel];
}

+ (void) pauseOrResume : (bool*) ispause{
    if(ispause){
        [[BDSSpeechSynthesizer sharedInstance] pause] ;
    }else{
        [[BDSSpeechSynthesizer sharedInstance] resume];
    }
}


- (void)synthesizerStartWorkingSentence:(NSInteger)SynthesizeSentence
{
    NSLog(@"Began synthesizing sentence %ld", (long)SynthesizeSentence);
}

- (void)synthesizerFinishWorkingSentence:(NSInteger)SynthesizeSentence
{
    NSLog(@"Finished synthesizing sentence %ld", (long)SynthesizeSentence);
}

- (void)synthesizerSpeechStartSentence:(NSInteger)SpeakSentence
{
    NSLog(@"Began playing sentence %ld", (long)SpeakSentence);
}

- (void)synthesizerSpeechEndSentence:(NSInteger)SpeakSentence
{
    NSLog(@"Finished playing sentence %ld", (long)SpeakSentence);
}

@end
