package com.xsznet.aliyun_voice;

import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;

/** AliyunVoicePlugin */
public class AliyunVoicePlugin implements MethodCallHandler {
  protected static Registrar registrar;
  /** Plugin registration. */
  public static void registerWith(Registrar reg) {
    registrar = reg;
    final MethodChannel channel = new MethodChannel(registrar.messenger(), "aliyun_voice");
    channel.setMethodCallHandler(new AliyunVoicePlugin());
    BaiduSDK.getBaiduSDKIntance().attchActivity(registrar.activity());
  }

  @Override
  public void onMethodCall(MethodCall call, Result result) {
    if (call.method.equals("getPlatformVersion")) {
      result.success("Android " + android.os.Build.VERSION.RELEASE);
    } else   if (call.method.equals("initTTS")) {
      BaiduSDK.getBaiduSDKIntance().initTTs(registrar.activity());
    }else   if (call.method.equals("attach")) {
      BaiduSDK.getBaiduSDKIntance().attchActivity(registrar.activity());
    }    else   if (call.method.equals("speak")) {
      BaiduSDK.getBaiduSDKIntance().speak(call.argument("content").toString(),true,false,false,false);
    }else if(call.method.equals("release")){
      BaiduSDK.getBaiduSDKIntance().release();
    }
    else if(call.method.equals("stop")){
      BaiduSDK.getBaiduSDKIntance().stop();
    }
    else if(call.method.equals("pauseOrResume")){
      BaiduSDK.getBaiduSDKIntance().pauseOrResume(call.argument("status").equals("pause")?true:false);
    }
    else if(call.method.equals("startASR")){
      BaiduSDK.getBaiduSDKIntance().startASR();
    }
    else if(call.method.equals("stopASR")){
      BaiduSDK.getBaiduSDKIntance().stopASR();
    }
    else {
      result.notImplemented();
    }
  }
}
