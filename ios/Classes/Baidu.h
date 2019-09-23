//
// Created by jingtao gao on 2019/9/16.
//

#ifndef ALIYUN_VOICE_BAIDU_H
#define ALIYUN_VOICE_BAIDU_H

#endif //ALIYUN_VOICE_BAIDU_H
@interface Baidu : NSObject
+ (Baidu *)CDSingletonBaidu;
+ (void) initTTS;
+ (void) speak:(NSString*) content;
+ (void) stop;
+ (void) releaseVoice;
+ (void) pauseOrResume:(bool*) pause;
@end
