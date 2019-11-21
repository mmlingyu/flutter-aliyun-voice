package com.xsznet.aliyun_voice;

import android.app.Activity;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.util.Log;

import com.baidu.tts.auth.AuthInfo;
import com.baidu.tts.chainofresponsibility.logger.LoggerProxy;
import com.baidu.tts.client.SpeechSynthesizer;
import com.baidu.tts.client.SpeechSynthesizerListener;
import com.baidu.tts.client.TtsMode;

import java.io.File;
import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.Map;

import com.xsznet.aliyun_voice.core.mini.AutoCheck;
import com.xsznet.aliyun_voice.core.params.CommonRecogParams;
import com.xsznet.aliyun_voice.core.params.OnlineRecogParams;
import com.xsznet.aliyun_voice.core.recog.IStatus;
import com.xsznet.aliyun_voice.core.recog.MyRecognizer;
import com.xsznet.aliyun_voice.core.recog.listener.IRecogListener;
import com.xsznet.aliyun_voice.core.recog.listener.MessageStatusRecogListener;
import com.xsznet.aliyun_voice.core.util.MyLogger;

import org.greenrobot.eventbus.EventBus;

public class BaiduSDK implements IStatus {
    protected String appId = "16455084";
    protected String appKey = "7HGDv5wF0zVO2tUYmebPpa6f";

    protected String secretKey = "HaUXNaK3ESzuB5of10rXzgUNvluD9eYj";
    private TtsMode ttsMode = TtsMode.ONLINE;
    // ===============初始化参数设置完毕，更多合成参数请至getParams()方法中设置 =================
    protected SpeechSynthesizer mSpeechSynthesizer;
    protected Handler mainHandler,astHandler;
    SpeechSynthesizerListener listener;
    private static WeakReference<Activity> activityWeakReference;
    private final CommonRecogParams apiParams = new OnlineRecogParams();
    protected MyRecognizer myRecognizer;

    protected int asrstatus;

    static class BaiduSDKHolder{
        static final BaiduSDK baidu_sdk = new BaiduSDK();
    }
    public static BaiduSDK getBaiduSDKIntance(){
        return  BaiduSDKHolder.baidu_sdk;
    }

    public void attchActivity(Activity activity){
        activityWeakReference = new WeakReference<>(activity);
    }

    private void initASR(Activity activity){
        apiParams.initSamplePath(activity);
        asrstatus = STATUS_NONE;
        astHandler = new Handler() {

            /*
             * @param msg
             */
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                handleMsg(msg);
            }

        };
        MyLogger.setHandler(astHandler);
        IRecogListener listener = new MessageStatusRecogListener(astHandler);
        // DEMO集成步骤 1.1 1.3 初始化：new一个IRecogListener示例 & new 一个 MyRecognizer 示例,并注册输出事件
        myRecognizer = new MyRecognizer(activity, listener);
    }

    protected void handleMsg(Message msg) {

        switch (msg.what) { // 处理MessageStatusRecogListener中的状态回调
            case STATUS_FINISHED:
                if (msg.arg2 == 1) {
                    //txtResult.setText(msg.obj.toString());
                    EventBus.getDefault().post(msg.obj.toString());
                }
                asrstatus = msg.what;
                //updateBtnTextByStatus();
                break;
            case STATUS_NONE:
            case STATUS_READY:
            case STATUS_SPEAKING:
            case STATUS_RECOGNITION:
                asrstatus = msg.what;
               //updateBtnTextByStatus();
                break;
            default:
                break;

        }
    }

    public void startASR() {
        switch (asrstatus) {
            case STATUS_NONE: // 初始状态
                startBaisuASR();
                asrstatus = STATUS_WAITING_READY;

                break;
            case STATUS_WAITING_READY: // 调用本类的start方法后，即输入START事件后，等待引擎准备完毕。
            case STATUS_READY: // 引擎准备完毕。
            case STATUS_SPEAKING: // 用户开始讲话
            case STATUS_FINISHED: // 一句话识别语音结束
            case STATUS_RECOGNITION: // 识别中
                stopASR();
                asrstatus = STATUS_STOPPED; // 引擎识别中
                break;
            case STATUS_LONG_SPEECH_FINISHED: // 长语音识别结束
            case STATUS_STOPPED: // 引擎识别中
                cancelASR();
                asrstatus = STATUS_NONE; // 识别结束，回到初始状态
                break;
            default:
                break;
        }
    }

    protected Map<String, Object> fetchParams() {
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(activityWeakReference.get());
        //  上面的获取是为了生成下面的Map， 自己集成时可以忽略
        Map<String, Object> params = apiParams.fetch(sp);
        //  集成时不需要上面的代码，只需要params参数。
        return params;
    }

        /**
         * 开始录音，点击“开始”按钮后调用。
         * 基于DEMO集成2.1, 2.2 设置识别参数并发送开始事件
         */
        protected void startBaisuASR() {
            // DEMO集成步骤2.1 拼接识别参数： 此处params可以打印出来，直接写到你的代码里去，最终的json一致即可。
            final Map<String, Object> params = fetchParams();
            // params 也可以根据文档此处手动修改，参数会以json的格式在界面和logcat日志中打印
            Log.i("ASR", "设置的start输入参数：" + params);
            // 复制此段可以自动检测常规错误
            (new AutoCheck(activityWeakReference.get(), new Handler() {
                public void handleMessage(Message msg) {
                    if (msg.what == 100) {
                        AutoCheck autoCheck = (AutoCheck) msg.obj;
                        synchronized (autoCheck) {
                            String message = autoCheck.obtainErrorMessage(); // autoCheck.obtainAllMessage();
                            //txtLog.append(message + "\n");
                            ; // 可以用下面一行替代，在logcat中查看代码
                             Log.w("AutoCheckMessage", message);
                        }
                    }
                }
            }, false)).checkAsr(params);

            // 这里打印出params， 填写至您自己的app中，直接调用下面这行代码即可。
            // DEMO集成步骤2.2 开始识别
            myRecognizer.start(params);
        }

        /**
         * 开始录音后，手动点击“停止”按钮。
         * SDK会识别不会再识别停止后的录音。
         * 基于DEMO集成4.1 发送停止事件 停止录音
         */
        protected void stopASR() {

            myRecognizer.stop();
        }

        /**
         * 开始录音后，手动点击“取消”按钮。
         * SDK会取消本次识别，回到原始状态。
         * 基于DEMO集成4.2 发送取消事件 取消本次识别
         */
        protected void cancelASR(){

            myRecognizer.cancel();
        }

        /**
         * 销毁时需要释放识别资源。
         */
        protected void releaseASR() {

            // 如果之前调用过myRecognizer.loadOfflineEngine()， release()里会自动调用释放离线资源
            // 基于DEMO5.1 卸载离线资源(离线时使用) release()方法中封装了卸载离线资源的过程
            // 基于DEMO的5.2 退出事件管理器
            myRecognizer.release();

        }

    /**
     * 注意此处为了说明流程，故意在UI线程中调用。
     * 实际集成中，该方法一定在新线程中调用，并且该线程不能结束。具体可以参考NonBlockSyntherizer的写法
     */
    public void initTTs(Activity activity) {
        initView();
        activityWeakReference = new WeakReference<>(activity);
        LoggerProxy.printable(true); // 日志打印在logcat中
        boolean isMix = ttsMode.equals(TtsMode.MIX);
        initASR(activity);
        boolean isSuccess;
        if (isMix) {
            // 检查2个离线资源是否可读
            isSuccess = checkOfflineResources();
            if (!isSuccess) {
                return;
            } else {

            }
        }
        // 日志更新在UI中，可以换成MessageListener，在logcat中查看日志
        listener = new UiMessageListener(mainHandler);

        // 1. 获取实例
        mSpeechSynthesizer = SpeechSynthesizer.getInstance();
        mSpeechSynthesizer.setContext(activityWeakReference.get());

        // 2. 设置listener
        mSpeechSynthesizer.setSpeechSynthesizerListener(listener);

        // 3. 设置appId，appKey.secretKey
        int result = mSpeechSynthesizer.setAppId(appId);
        checkResult(result, "setAppId");
        result = mSpeechSynthesizer.setApiKey(appKey, secretKey);
        checkResult(result, "setApiKey");

        // 4. 支持离线的话，需要设置离线模型
        if (isMix) {
            // 检查离线授权文件是否下载成功，离线授权文件联网时SDK自动下载管理，有效期3年，3年后的最后一个月自动更新。
            isSuccess = checkAuth();
            if (!isSuccess) {
                return;
            }
            // 文本模型文件路径 (离线引擎使用)， 注意TEXT_FILENAME必须存在并且可读
            mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_TTS_TEXT_MODEL_FILE, TEXT_FILENAME);
            // 声学模型文件路径 (离线引擎使用)， 注意TEXT_FILENAME必须存在并且可读
            mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_TTS_SPEECH_MODEL_FILE, MODEL_FILENAME);
        }

        // 5. 以下setParam 参数选填。不填写则默认值生效
        // 设置在线发声音人： 0 普通女声（默认） 1 普通男声 2 特别男声 3 情感男声<度逍遥> 4 情感儿童声<度丫丫>
        mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_SPEAKER, "0");
        // 设置合成的音量，0-9 ，默认 5
        mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_VOLUME, "9");
        // 设置合成的语速，0-9 ，默认 5
        mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_SPEED, "4");
        // 设置合成的语调，0-9 ，默认 5
        mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_PITCH, "5");

        mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_MIX_MODE, SpeechSynthesizer.MIX_MODE_DEFAULT);
        // 该参数设置为TtsMode.MIX生效。即纯在线模式不生效。
        // MIX_MODE_DEFAULT 默认 ，wifi状态下使用在线，非wifi离线。在线状态下，请求超时6s自动转离线
        // MIX_MODE_HIGH_SPEED_SYNTHESIZE_WIFI wifi状态下使用在线，非wifi离线。在线状态下， 请求超时1.2s自动转离线
        // MIX_MODE_HIGH_SPEED_NETWORK ， 3G 4G wifi状态下使用在线，其它状态离线。在线状态下，请求超时1.2s自动转离线
        // MIX_MODE_HIGH_SPEED_SYNTHESIZE, 2G 3G 4G wifi状态下使用在线，其它状态离线。在线状态下，请求超时1.2s自动转离线

        mSpeechSynthesizer.setAudioStreamType(AudioManager.MODE_IN_CALL);

        // x. 额外 ： 自动so文件是否复制正确及上面设置的参数
        HashMap<String, String> params = new HashMap<>();
        // 复制下上面的 mSpeechSynthesizer.setParam参数
        // 上线时请删除AutoCheck的调用
        if (isMix) {
            params.put(SpeechSynthesizer.PARAM_TTS_TEXT_MODEL_FILE, TEXT_FILENAME);
            params.put(SpeechSynthesizer.PARAM_TTS_SPEECH_MODEL_FILE, MODEL_FILENAME);
        }
        InitConfig initConfig =  new InitConfig(appId, appKey, secretKey, ttsMode, params, listener);

        // 6. 初始化
        result = mSpeechSynthesizer.initTts(ttsMode);
        checkResult(result, "initTts");

    }


    /**
     * 检查appId ak sk 是否填写正确，另外检查官网应用内设置的包名是否与运行时的包名一致。本demo的包名定义在build.gradle文件中
     *
     * @return
     */
    private boolean checkAuth() {
        AuthInfo authInfo = mSpeechSynthesizer.auth(ttsMode);
        if (!authInfo.isSuccess()) {
            // 离线授权需要网站上的应用填写包名。本demo的包名是com.baidu.tts.sample，定义在build.gradle中
            String errorMsg = authInfo.getTtsError().getDetailMessage();
            return false;
        } else {

            return true;
        }
    }

    /**
     * 检查 TEXT_FILENAME, MODEL_FILENAME 这2个文件是否存在，不存在请自行从assets目录里手动复制
     *
     * @return
     */
    private boolean checkOfflineResources() {
        String[] filenames = {TEXT_FILENAME, MODEL_FILENAME};
        for (String path : filenames) {
            File f = new File(path);
            if (!f.canRead()) {

                return false;
            }
        }
        return true;
    }

    public void speak(String current,boolean isLoop,boolean isPause,boolean isExit,boolean isResume) {
        /* 以下参数每次合成时都可以修改
         *  mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_SPEAKER, "0");
         *  设置在线发声音人： 0 普通女声（默认） 1 普通男声 2 特别男声 3 情感男声<度逍遥> 4 情感儿童声<度丫丫>
         *  mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_VOLUME, "5"); 设置合成的音量，0-9 ，默认 5
         *  mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_SPEED, "5"); 设置合成的语速，0-9 ，默认 5
         *  mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_PITCH, "5"); 设置合成的语调，0-9 ，默认 5
         *
         *  mSpeechSynthesizer.setParam(SpeechSynthesizer.PARAM_MIX_MODE, SpeechSynthesizer.MIX_MODE_DEFAULT);
         *  MIX_MODE_DEFAULT 默认 ，wifi状态下使用在线，非wifi离线。在线状态下，请求超时6s自动转离线
         *  MIX_MODE_HIGH_SPEED_SYNTHESIZE_WIFI wifi状态下使用在线，非wifi离线。在线状态下， 请求超时1.2s自动转离线
         *  MIX_MODE_HIGH_SPEED_NETWORK ， 3G 4G wifi状态下使用在线，其它状态离线。在线状态下，请求超时1.2s自动转离线
         *  MIX_MODE_HIGH_SPEED_SYNTHESIZE, 2G 3G 4G wifi状态下使用在线，其它状态离线。在线状态下，请求超时1.2s自动转离线
         */

        if (mSpeechSynthesizer == null) {
            return;
        }
        this.current = current;
        loop = isLoop;

        if(isExit){
            mSpeechSynthesizer.stop();
            return;
        }
        if(isPause){
            mSpeechSynthesizer.pause();
            return;
        }
        if(isResume){
            mSpeechSynthesizer.resume();
            return;
        }

        int result = mSpeechSynthesizer.speak(current);
        Log.i("mainHandler", "mSpeechSynthesizer.speak-->"+result);
        checkResult(result, "speak");
    }

    public void stop() {
        int result = mSpeechSynthesizer.stop();
        checkResult(result, "stop");
    }
    public void pauseOrResume(boolean isPause) {
        if(isPause){
            mSpeechSynthesizer.pause();
            return;
        }else{
            mSpeechSynthesizer.resume();
            return;
        }
    }

    public void release(){
        if (mSpeechSynthesizer != null) {
            mSpeechSynthesizer.stop();
            mSpeechSynthesizer.release();
            mSpeechSynthesizer = null;
        }
    }

    private static String current="";
    private static boolean loop=false;

    //  下面是UI部分

    private void initView() {
        mainHandler = new Handler() {
            /*
             * @param msg
             */
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                if (msg.obj != null) {
                    Log.i("mainHandler", msg.what+"-->");
                }
                if(msg.what==UiMessageListener.AGAIN&&loop){
                    mSpeechSynthesizer.speak(current);
                }
            }

        };
    }

    private void checkResult(int result, String method) {
        if (result != 0) {
        }
    }


    // ================选择TtsMode.ONLINE  不需要设置以下参数; 选择TtsMode.MIX 需要设置下面2个离线资源文件的路径
    private static final String TEMP_DIR = "/sdcard/baiduTTS"; // 重要！请手动将assets目录下的3个dat 文件复制到该目录

    // 请确保该PATH下有这个文件
    private static final String TEXT_FILENAME = TEMP_DIR + "/" + "bd_etts_text.dat";

    // 请确保该PATH下有这个文件 ，m15是离线男声
    private static final String MODEL_FILENAME =
            TEMP_DIR + "/" + "bd_etts_common_speech_m15_mand_eng_high_am-mix_v3.0.0_20170505.dat";
}
