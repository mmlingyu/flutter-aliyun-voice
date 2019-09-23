//
//  NlsDelegateEvent.h
//  NlsSdk
//
//  Created by Songsong Shao on 2018/6/26.
//  Copyright © 2018年 Songsong Shao. All rights reserved.
//

typedef enum{
    VoiceData,
    VoiceVolume,
    
    TaskFailed,
    TaskStarted,
    TaskStopped,
    RecognitionStarted,
    RecognitionCompleted ,
    RecognitionResultChanged,
    
    SynthesizerStarted,
    SynthesizerCompleted,
    Binary,
    
    TranscriberStarted,
    TranscriberCompleted,
    TranscriberSentenceBegin,
    TranscriberSentenceEnd,
    TranscriberResultChanged,
    
    DialogResultGenerated,
    
    Close
}NlsDelegateEvent;

typedef enum{
    LOGERROR = 1,
    LOGWARNNING =2,
    LOGINFO = 3,
    LOGDEBUG = 4

}NlsLogLevel;

//状态 init -> start ->connected ->stop ->closed
typedef enum {
    w_init = 0,
    w_start,
    w_connected,
    w_stop,
    w_closed,
    w_failed
}w_status;


