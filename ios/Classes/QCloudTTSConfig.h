#import <Foundation/Foundation.h>

/**
 * TTS音色类型
 */
typedef NS_ENUM(NSUInteger, VoiceType) {
    VoiceTypeAffinityFemale   = 0,   // 0：亲和女声（默认）
    VoiceTypeAffinityMale     = 1,   // 1：亲和男声
    VoiceTypeMatureMale       = 2,   // 2：成熟男声
    VoiceTypeVibrantMale      = 3,   // 3：活力男声
    VoiceTypeWarmFemale       = 4,   // 4：温暖女声
    VoiceTypeEmotionalFemale  = 5,   // 5：情感女声
    VoiceTypeEmotionalMale    = 6,   // 6：情感男声
};

/**
 * TTS语速，
 */
typedef NS_ENUM(NSInteger, SpeedType) {
    SpeedTypeVerySlow     = -2,   // 0.6 倍
    SpeedTypeSlowDown     = -1,   // 0.8 倍
    SpeedTypeNormal       = 0,    // 1.0 倍(默认)
    SpeedTypeAccelerate   = 1,    // 1.2 倍
    SpeedTypeVeryFast     = 2,    // 1.5 倍
};

/**
 * TTS音量，
 */
typedef NS_ENUM(NSUInteger, VolumeLevel) {
    VolumeLevelZero    = 0,   // 默认为0，逐级递增
    VolumeLevelOne     = 1,
    VolumeLevelTwo     = 2,
    VolumeLevelThree   = 3,
    VolumeLevelFour    = 4,
    VolumeLevelFive    = 5,
    VolumeLevelSix     = 6,
    VolumeLevelSeven   = 7,
    VolumeLevelEight   = 8,
    VolumeLevelNine    = 9,
    VolumeLevelTen     = 10,
};

/**
 * TTS主语言类型
 */
typedef NS_ENUM(NSUInteger, PrimaryLanguage) {
    PrimaryChinese    = 1,   // 1：中文，最大支持 500 字符(默认)
    PrimaryEnglish    = 2,   // 2：英文
};

@interface QCloudTTSConfig : NSObject

@property (nonatomic, assign) NSInteger appId;
@property (nonatomic, strong) NSString *secretId;
@property (nonatomic, strong) NSString *secretKey;

//以下参数非必填
@property (nonatomic, assign) NSInteger projectId;  //项目 ID，用户自定义，默认为 0。
@property (nonatomic, assign) VoiceType voiceType;  //tts音色，默认女声，亲和风格
@property (nonatomic, assign) SpeedType speed;      //语速，范围：[-2，2]，分别对应不同语速：0.6 倍、0.8 倍、1.0 倍、1.2 倍、1.5 倍，默认为 0。
@property (nonatomic, assign) VolumeLevel volume;   //默认为0，逐级递增
@property (nonatomic, assign) PrimaryLanguage language;   //主语言类型，默认中文

+ (QCloudTTSConfig *)getInstance;

@end
