import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:aliyun_voice/aliyun_voice.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';

  @override
  void initState() {
    super.initState();
    initPlatformState();
   // AliyunVoice.attach();
     AliyunVoice.initTTS();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    String platformVersion;
    // Platform messages may fail, so we use a try/catch PlatformException.
    try {
      platformVersion = await AliyunVoice.platformVersion;
    } on PlatformException {
      platformVersion = 'Failed to get platform version.';
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _platformVersion = platformVersion;
    });
  }

  void _speak(){
    _platformVersion = _platformVersion+"11111";
    setState(() {
      _platformVersion = _platformVersion;
    });
     AliyunVoice.speak("春眠不觉晓 处处闻啼鸟 夜来风雨声 花落知多少");
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: GestureDetector(onTap:_speak ,child:Center(
          child: Text('设备Running on: $_platformVersion\n',style: TextStyle(fontSize: 30),),
        ),
      )),
    );
  }

  @override
  void dispose() {
    super.dispose();
    AliyunVoice.release();
  }
}
