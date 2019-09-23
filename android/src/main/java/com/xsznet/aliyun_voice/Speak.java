package com.xsznet.aliyun_voice;

public class Speak {
    private String string;
    private boolean loop;
    private boolean isexit;
    private boolean ispause;

    public boolean isIsresume() {
        return isresume;
    }

    public void setIsresume(boolean isresume) {
        this.isresume = isresume;
    }

    private boolean isresume
            ;
    public boolean isIsexit() {
        return isexit;
    }

    public boolean isIspause() {
        return ispause;
    }

    public void setIspause(boolean ispause) {
        this.ispause = ispause;
    }

    public void setIsexit(boolean isexit) {
        this.isexit = isexit;
    }

    public String getString() {
        return string;
    }

    public void setString(String string) {
        this.string = string;
    }

    public boolean isLoop() {
        return loop;
    }

    public void setLoop(boolean loop) {
        this.loop = loop;
    }
}
