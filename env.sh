#!/bin/sh

# 编译目录
SRC=/usr/src
CEF_SRC=/usr/src/mdc-ubuntu-for-cef
CEF_SDK=/usr/src/mdc-ubuntu-for-cef/cef_binary_97.1.5+g2b00258+chromium-97.0.4692.71_linux64_minimal

# 安装目录
PREFIX=/usr/local/mdc
mkdir -p $PREFIX/include
mkdir -p $PREFIX/lib

# 下载CEF SDK
cd $SRC && git clone https://git.mudu.tv/mdc-stream/mdc-compile/mdc-ubuntu-for-cef.git
cd $CEF_SRC && tar -xjf cef_binary_97.1.5+g2b00258+chromium-97.0.4692.71_linux64_minimal.tar.bz2

# cef编译
apt-get install build-essential libgtk-3-dev libx11-dev -y
mkdir -p $CEF_SDK/build
cd $CEF_SDK/build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j4

# 拷贝cef头文件、库及其它资源
cp -r $CEF_SDK/include/*    $PREFIX/include
cp -r $CEF_SDK/Release/*    $PREFIX/lib
cp -r $CEF_SDK/Resources/*  $PREFIX/lib
cp -r $CEF_SDK/build/libcef_dll_wrapper/libcef_dll_wrapper.a $PREFIX/lib


