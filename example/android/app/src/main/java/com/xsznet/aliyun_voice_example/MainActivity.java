package com.xsznet.aliyun_voice_example;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;

import java.util.ArrayList;
import java.util.Map;

import io.flutter.app.FlutterActivity;
import io.flutter.plugin.common.BasicMessageChannel;
import io.flutter.plugin.common.EventChannel;
import io.flutter.plugin.common.JSONMessageCodec;
import io.flutter.plugins.GeneratedPluginRegistrant;
import com.alibaba.fastjson.JSON;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class MainActivity extends FlutterActivity {
  public static final String STREAM = "com.xiaoshunzi.ainong/event";
  private BasicMessageChannel<Object> mMessageChannel;
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    GeneratedPluginRegistrant.registerWith(this);
    initPermission();


    mMessageChannel = new BasicMessageChannel<Object>(getFlutterView(), STREAM,JSONMessageCodec.INSTANCE);
    mMessageChannel.setMessageHandler(new MainStreamHandler());


    EventBus.getDefault().register(this);
  }

  /**
   * android 6.0 以上需要动态申请权限
   */
  private void initPermission() {
    String[] permissions = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.ACCESS_NETWORK_STATE,
            Manifest.permission.INTERNET,
            Manifest.permission.READ_PHONE_STATE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    ArrayList<String> toApplyList = new ArrayList<String>();

    for (String perm : permissions) {
      if (PackageManager.PERMISSION_GRANTED != ContextCompat.checkSelfPermission(this, perm)) {
        toApplyList.add(perm);
        // 进入到这里代表没有权限.

      }
    }
    String[] tmpList = new String[toApplyList.size()];
    if (!toApplyList.isEmpty()) {
      ActivityCompat.requestPermissions(this, toApplyList.toArray(tmpList), 123);
    }

  }

  @Override
  public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
    // 此处为android 6.0以上动态授权的回调，用户自行实现。
  }

  @Subscribe(threadMode = ThreadMode.MAIN)
  public void onGetMessage(String message) {
    MessageData messageData = new MessageData();
    messageData.setCode("0");
    messageData.setObj(message);
    messageData.setType("0");
    mMessageChannel.send(JSON.toJSON(messageData));
  }

  class MessageData{
    String obj;
    String type;
    String code;

    public String getObj() {
      return obj;
    }

    public void setObj(String obj) {
      this.obj = obj;
    }

    public String getType() {
      return type;
    }

    public void setType(String type) {
      this.type = type;
    }

    public String getCode() {
      return code;
    }

    public void setCode(String code) {
      this.code = code;
    }
  }


  private static Handler handler = new Handler() {
    @Override
    public void handleMessage(Message msg) {
      super.handleMessage(msg);
      ((EventChannel.EventSink)msg.obj).success("data from native~");
      //eventSink.success((count++) + "主动发送消息给flutter");
//              handler.sendEmptyMessageDelayed(1,1000);
    }
  };


  static class MainStreamHandler implements BasicMessageChannel.MessageHandler {

    @Override
    public void onMessage(Object o, BasicMessageChannel.Reply reply) {
      Log.w("MainActivity", "adding listener");
      Map<Object, Object> arguments = (Map<Object, Object>) o;
      Message message = new Message();
      message.obj = o;
      handler.sendMessage(message);
    }
  }
}
