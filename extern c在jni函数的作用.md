# extern "C"

```
extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。
加上extern "C"后，会指示编译器这部分代码按C语言（而不是C++）的方式进行编译。
由于C++支持函数重载，因此编译器编译函数的过程中会将函数的参数类型也加到编译后的代码中，而不仅仅是函数名；而C语言并不支持函数重载，因此编译C语言代码的函数时不会带上函数的参数类型，一般只包括函数名。

hello-gl2	编译出的so 在IDA中看到的jni导出函数名称是
jni函数：								JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
导出的函数名称：						Java_com_android_gl2jni_GL2JNILib_init	
(gl_code.cpp是用c++的方式编译，加了extern "C"的函数 会指示编译器这个函数按C语言（而不是C++）的方式进行编译)
如果不加extern "C"导出的函数名称是		_Z38Java_com_android_gl2jni_GL2JNILib_initP7_JNIEnvP8_jobjectii

hello-jni列子编译出的so 在IDA中看到的jni导出函数名称是
jni函数：						jstring Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env, jobject thiz )
导出的函数名称：				Java_com_example_hellojni_HelloJni_stringFromJNI
```

```
ndk samples: hello-gl2
gl_code.cpp

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

（1）JNIEXPORT ：在Jni编程中所有本地语言实现Jni接口的方法前面都有一个"JNIEXPORT",这个可以看做是Jni的一个标志，至今为止没发现它有什么特殊的用处。
（3）JNICALL ：这个可以理解为Jni 和Call两个部分，和起来的意思就是 Jni调用XXX（后面的XXX就是JAVA的方法名）。


ndk samples: native-codec
native-codec-jni.cpp

extern "C" {

jboolean Java_com_example_nativecodec_NativeCodec_createStreamingMediaPlayer(JNIEnv* env,
        jclass clazz, jstring filename)
{
    LOGV("@@@ create");

    return JNI_TRUE;
}

// set the playing state for the streaming media player
void Java_com_example_nativecodec_NativeCodec_setPlayingStreamingMediaPlayer(JNIEnv* env,
        jclass clazz, jboolean isPlaying)
{
    LOGV("@@@ playpause: %d", isPlaying);

}

}
这个例子用的是将jni函数直接包在 extern "C" 中
没有写JNIEXPORT和JNICALL
```

```
ndk samples: hello-jni
hello-jni.c

jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
	#define ABI "armeabi-v7a"
    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
}
```


