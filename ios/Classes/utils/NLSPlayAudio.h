//
//  NLSPlayAudio.h
//  AliyunNlsClientSample
//
//  Created by 刘方 on 2/25/16.
//  Copyright © 2016 阿里巴巴. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

#define EVERY_READ_LENGTH 200
#define NUM_BUFFERS 3
#define QUEUE_BUFFER_SIZE 640

@protocol NLSPlayAudioDelegate<NSObject>

-(void)playDone;

@end


@interface NLSPlayAudio : NSObject {
    //音频参数
    AudioStreamBasicDescription audioDescription;
    // 音频播放队列
    AudioQueueRef audioQueue;
    // 音频缓存
    AudioQueueBufferRef audioQueueBuffers[QUEUE_BUFFER_SIZE];
}
@property(nonatomic,weak) id<NLSPlayAudioDelegate> delegate;

-(void)process:(Byte *)audioByte length:(long)len; //填入播放数据
-(void)cleanup; //提前结束播放调用，清理当前未播放数据
-(void)finishFeed:(Boolean)enableFinishCallback; //如果需要回调播放结束信号，需要在OnSynthesizerCompleted调用本接口
@end


