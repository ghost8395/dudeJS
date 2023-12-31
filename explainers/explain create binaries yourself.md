# for generaring v8 binary

sudo apt-get install -y ccache
sudo apt-get install -y cmake

ccache --version 
## ccache version 4.6.3

ccache g++ --version
## Apple clang version 13.1.6 (clang-1316.0.21.2.5)
## Target: arm64-apple-darwin21.6.0
## Thread model: posix
## InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

cmake --version
## cmake version 3.24.1

git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH=`pwd`/depot_tools:$PATH

echo "export PATH=`pwd`/depot_tools:\$PATH" >> ~/.zshrc

cd depot_tools && git checkout 787e71ac && cd ..

## add patch
mkdir -p lib/v8 && cd lib/v8
gclient
fetch v8

cd v8
git checkout 4ec5bb4f26

tools/dev/v8gen.py list

tools/dev/v8gen.py x64.release.sample

## echo 'v8_target_cpu = "arm64"' >> out.gn/x64.release.sample/args.gn 
echo 'cc_wrapper="ccache"' >> out.gn/x64.release.sample/args.gn 
sed -ie '/v8_enable_sandbox/d' out.gn/x64.release.sample/args.gn

export CCACHE_CPP2=yes
export CCACHE_SLOPPINESS=time_macros

## Optionally, add this to your ~/.zshrc if you are using zsh, or any
## other equivalents
echo "export CCACHE_CPP2=yes" >> ~/.zshrc
echo "export CCACHE_SLOPPINESS=time_macros" >> ~/.zshrc

time ninja -C out.gn/x64.release.sample v8_monolith

cp out.gn/x64.release.sample/obj/libv8_monolith.a ../../../v8/
cp out.gn/x64.release.sample/icudtl.dat ../../../v8/
cp -r include ../../../v8/

## clean up
cd ../../
rm -rf v8
rm -rf depot_tools

# for generaring libuv binary

#!/bin/bash

APP_DIR=../../app

git clone https://github.com/libuv/libuv
cd libuv && git checkout v1.x

sh autogen.sh
./configure
make
make check
make install

./build/uv_run_tests

cp -r include $APP_DIR/libuv/
cp -r .libs/libuv.a $APP_DIR/libuv/
