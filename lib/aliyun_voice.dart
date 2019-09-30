import 'dart:async';

import 'package:flutter/services.dart';

class AliyunVoice {
  static const MethodChannel _channel =
      const MethodChannel('aliyun_voice');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
  static void initTTS() {
    _channel.invokeMethod('initTTS');
  }
  static void speak(String content) async {
    await  _channel.invokeMethod('speak',{'content':content});
  }
  static void stop() async {
     _channel.invokeMethod('stop');
  }
  static void release() async {
    _channel.invokeMethod('release');
  }

  static void pauseOrResume(bool isPause) async {
    print(isPause?"pause":"resume" +" ----> ");
    _channel.invokeMethod('pauseOrResume',{'status':isPause?"pause":"resume"});
  }
}
