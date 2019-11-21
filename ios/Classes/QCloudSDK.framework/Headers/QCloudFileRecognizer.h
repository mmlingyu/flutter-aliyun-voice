//
//  QCloudBaseRecognizer.h
//  QCloudSDK
//
//  Created by Sword on 2019/8/8.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "QCloudBaseRecognizer.h"

@protocol QCloudFileRecognizerDelegate;

@class QCloudFileRecognizeParams;

@interface QCloudFileRecognizer : QCloudBaseRecognizer

@property (nonatomic, weak) id<QCloudFileRecognizerDelegate> _Nullable delegate;

/**
 文件识别接口

 @param params 识别参数
 @return 返回请求唯一标识requestId，回调中用到
 */
- (NSInteger)recognize:(QCloudFileRecognizeParams *_Nonnull)params;

- (void)clear;

@end


@protocol QCloudFileRecognizerDelegate <NSObject>
@optional

/**
 录音文件识别成功回调

 @param recognizer 录音文件识别器
 @param requestId 请求唯一标识requestId,recognize:接口返回
 @param text 识别文本
 @param resultData 原始数据
 */
- (void)fileRecognizer:(QCloudFileRecognizer *_Nullable)recognizer requestId:(NSInteger)requestId text:(nullable NSString *)text resultData:(nullable NSDictionary *)resultData;
/**
 录音文件识别失败回调
 
 @param recognizer 录音文件识别器
 @param requestId 请求唯一标识requestId,recognize:接口返回
 @param error 识别错误，出现错误此字段有
 @param resultData 原始数据
 */
- (void)fileRecognizer:(QCloudFileRecognizer *_Nullable)recognizer requestId:(NSInteger)requestId error:(nullable NSError *)error resultData:(nullable NSDictionary *)resultData;
@end
