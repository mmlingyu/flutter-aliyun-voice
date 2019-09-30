//
//  QCloudTTS.h

#import <Foundation/Foundation.h>


//! Project version string for QCloudTTSSDK.

FOUNDATION_EXPORT NSString * _Nullable const libQCloudTTSSDKVersionString;

#include "QCloudTTSConfig.h"

@protocol QCloudTTSDelegate <NSObject>

@optional
//开始播放
- (void) onTTSPlayStart;

//缓冲中
- (void) onTTSPlayWait;

//缓冲完成
- (void) onTTSPlayContinue;

//播放中止
- (void) onTTSPlayStop;

//播放结束
- (void) onTTSPlayEnd;
@end


typedef void(^TTSExceptionHandler)(NSString * _Nullable errCode, NSString * _Nullable errMsg);

@interface QCloudTTS : NSObject

@property(assign, nullable) id<QCloudTTSDelegate> ttsDelegate;

//初始化
- (id _Nonnull )initWithAppId:(NSInteger)appId secretId:(NSString *_Nonnull)secretId secretKey:(NSString *_Nonnull)secretKey;

//开始播放，支持任意长度文本
- (BOOL)startTTS:(NSString *_Nonnull)text fail:(TTSExceptionHandler _Nullable )fail;

//暂停播放
- (BOOL)pauseTTS;

//恢复播放(如果可以)
- (BOOL)resumeTTS;

//停止播放
- (BOOL)stopTTS;

@end
