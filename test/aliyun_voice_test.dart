import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:aliyun_voice/aliyun_voice.dart';

void main() {
  const MethodChannel channel = MethodChannel('aliyun_voice');

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await AliyunVoice.platformVersion, '42');
  });
}
