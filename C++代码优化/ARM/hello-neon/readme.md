#说明
```
对NDK samples程序hello-neon进行改造，BUILD_EXECUTABLE
生成的可执行程序拷贝到手机的/data/local/tmp目录下面执行，结果如下

dipper:/data/local/tmp # ./helloneonElf
main exit.
buffer: FIR Filter benchmark:
C version          : 89.3337 ms
Neon version   : 20.4885 ms (x4.36018 faster)

ARM官方的文档 DEN0018A_neon_programmers_guide_en.pdf，第8章有三个NEON Code Examples with Optimization
Converting color depth
Median filter
FIR filter（和NDK的例子比较像）
```

```
使用neon的方式：
1、使用neno intrinsics函数（C函数）		NDK给出的例子是用的neno intrinsics函数
2、使用neon汇编指令
3、使用第三方的库，OpenMAx
```

```
官方文档
2.5 NEON libraries
There is free open source software which makes use of NEON, for example:
? Ne10 library functions, the C interfaces to the functions provide assembler and NEON
implementations. See http://projectne10.github.com/Ne10/.
? OpenMAX, a set of APIs for processing audio, video, and still images. It is part of a
standard created by the Khronos group. There is a free ARM implementation of the
OpenMAX DL layer for NEON. See http://www.khronos.org/openmax/.
? ffmpeg, a collection of codecs for many different audio and video standards under LGPL
license at http://ffmpeg.org/.
? Eigen3, a linear algebra, matrix math C++ template library at eigen.tuxfamily.org/.
? Pixman, a 2D graphics library (part of Cairo graphics) at http://pixman.org/.
? x264, a rights-free GPL H.264 video encoder at
http://www.videolan.org/developers/x264.html.
? Math-neon at http://code.google.com/p/math-neon/.
```