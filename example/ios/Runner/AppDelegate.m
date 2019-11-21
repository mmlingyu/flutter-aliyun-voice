#include "AppDelegate.h"
#include "GeneratedPluginRegistrant.h"

@implementation AppDelegate
FlutterBasicMessageChannel *mMessageChannel;
NSString *STREAM  = @"com.xiaoshunzi.ainong/event";
- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  [GeneratedPluginRegistrant registerWithRegistry:self];
      [self BasicMessageChannelFunction];
  // Override point for customization after application launch.
      [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(notificationFuncion:) name:@"ios.to.flutter" object:nil];
  return [super application:application didFinishLaunchingWithOptions:launchOptions];
}
// flutter to native
- (void)notificationFuncion: (NSNotification *) notification {
    NSDictionary *userInfo = notification.userInfo;
    //通过这个方法 iOS可以主动多次 向 Flutter 发送消息
    [mMessageChannel sendMessage:userInfo];
}

//初始化channel
-(void) BasicMessageChannelFunction{
    //获取当前的 controller
    FlutterViewController* controller = (FlutterViewController*)self.window.rootViewController;
    // flutter_and_native_100 j
    mMessageChannel = [FlutterBasicMessageChannel messageChannelWithName:STREAM binaryMessenger:controller codec:FlutterJSONMessageCodec.new];
    // 接收消息监听
    [mMessageChannel setMessageHandler:^(id message, FlutterReply callback) {
        
    }];
}

- (void)dealloc {
    //单条移除观察者
    //[[NSNotificationCenter defaultCenter] removeObserver:self name:@"REFRESH_TABLEVIEW" object:nil];
    //移除所有观察者
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
