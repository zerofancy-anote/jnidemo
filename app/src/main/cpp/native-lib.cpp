#include <jni.h>
#include <string>
#include <android/log.h>

// https://juejin.cn/post/6983321432377786382
extern "C" JNIEXPORT jstring JNICALL
Java_top_ntutn_testjni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

jstring say_hello_2(JNIEnv *env, jobject thiz) {
    std::string hello2 = "我来自JNI动态注册";
    return env ->NewStringUTF(hello2.c_str());
}

static const JNINativeMethod gMethods[] = {
        "string2FromJNI",
        "()Ljava/lang/String;",
        (jstring *) say_hello_2
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_INFO, "native", "Jni_OnLoad");
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "native", "jni error");
        return -1;
    }
    jclass clazz = env ->FindClass("top/ntutn/testjni/MainActivity");
    if (!clazz) {
        __android_log_print(ANDROID_LOG_ERROR, "native", "cannot find class");
        return -1;
    }
    if (env ->RegisterNatives(clazz, gMethods, (sizeof gMethods) / (sizeof gMethods[0]))) {
        __android_log_print(ANDROID_LOG_ERROR, "native", "register method error");
        return -1;
    }
    return JNI_VERSION_1_6;
}