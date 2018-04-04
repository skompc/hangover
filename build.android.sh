#!/bin/bash
#
set -e
#
SRCDIR=`pwd`
DESTDIR=`pwd`
#
# environment needs to be setup before the script can run, e.g.:
#export PATH=/home/$USER/ndk/bin/:$PATH
#export ANDROID_HOME=/home/$USER/asdk
#export NDK_SYSROOT=/home/$USER/ndk/sysroot
#
mkdir -p $DESTDIR/build.android
mkdir -p $DESTDIR/build.android/wine-tools
mkdir -p $DESTDIR/build.android/wine-host
mkdir -p $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a
mkdir -p $DESTDIR/build.android/wine-guest
mkdir -p $DESTDIR/build.android/wine-guest32
mkdir -p $DESTDIR/build.android/qemu
mkdir -p $DESTDIR/build.android/glib
mkdir -p $DESTDIR/build.android/libs
#
# Build libs
cd $DESTDIR/build.android/
wget -c ftp://ftp-osl.osuosl.org/pub/libpng/src/libpng15/libpng-1.5.30.tar.gz
tar -xzf libpng-1.5.30.tar.gz
wget -c https://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz
tar -xzf freetype-2.8.tar.gz
cd $DESTDIR/build.android/libpng-1.5.30
./configure --host=arm-linux-androideabi --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a CXX=arm-linux-androideabi-clang++ CC=arm-linux-androideabi-clang
make -j4 ; make install
cd $DESTDIR/build.android/freetype-2.8
./configure --host=arm-linux-androideabi --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a LIBPNG_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/include/libpng15" LIBPNG_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib -lpng15" CXX=arm-linux-androideabi-clang++ CC=arm-linux-androideabi-clang
make -j4 ; make install
cd $DESTDIR/glib
./autogen.sh --help
cd $DESTDIR/build.android/glib
../../glib/configure --with-pcre=internal --host=arm-linux-androideabi CXX=arm-linux-androideabi-clang++ CC=arm-linux-androideabi-clang --disable-libmount --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a
make -j 4 ; make install
#
# Build the wine tools for crosscompilation
cd $DESTDIR/build.android/wine-tools
$SRCDIR/wine/configure --with-freetype --with-gettext --disable-tests --disable-win16 --without-alsa --without-capi --without-cms --without-coreaudio --without-cups --without-curses --without-dbus --without-fontconfig --without-gphoto --without-glu --without-gnutls --without-gsm --without-gstreamer --without-hal --without-jpeg --without-krb5 --without-ldap --without-mpg123 --without-netapi --without-openal --without-opencl --without-opengl --without-osmesa --without-oss --without-pcap --without-pulse --without-png --without-sane --without-tiff --without-v4l --without-x --without-xcomposite --without-xcursor --without-xinerama --without-xinput --without-xinput2 --without-xml --without-xrandr --without-xrender --without-xshape --without-xshm --without-xslt --without-xxf86vm --without-zlib
make -j 4 tools tools/sfnt2fon tools/widl tools/winebuild tools/winegcc tools/wmc tools/wrc
#
# Build the Host (e.g. arm) wine
cd $DESTDIR/build.android/wine-host
$SRCDIR/wine/configure --host=arm-linux-androideabi --with-wine-tools=../wine-tools --disable-tests --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/ --libdir=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib CXX=arm-linux-androideabi-clang++ CC=arm-linux-androideabi-clang LIBPNG_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/include/libpng15" LIBPNG_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib -lpng15" FREETYPE_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/include/freetype2" FREETYPE_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib -lm -lz -lpng15 -lfreetype"
make -j 4 ; make install
ln -sf ../wine-tools/tools tools
#
# Cross-Compile Wine for the guest platform to copy higher level DLLs from.
cd ../wine-guest32
$SRCDIR/wine/configure --host=i686-w64-mingw32 --with-wine-tools=../wine-host --without-freetype --disable-tests
make -j 4
#
# Build qemu
cd $DESTDIR/build.android/qemu
CC="$DESTDIR/build.android/wine-host/tools/winegcc/winegcc -D__ANDROID_API__=22 -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib --sysroot=$DESTDIR/build.android/wine-host -b arm-linux-androideabi -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include -DWINE_NOWINSOCK" CXX="$DESTDIR/build.android/wine-host/tools/winegcc/wineg++ -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib --sysroot=$DESTDIR/build.android/wine-host -b arm-linux-androideabi -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include  -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user --disable-fdt --disable-capstone
make -j 4
mkdir -p $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll32
mkdir -p $DESTDIR/build.android/qemu/i386-windows-user/qemu_host_dll32
#
# Build the wrapper DLLs.
# TODO: Figure out dependencies between them better.
declare -a dlls=("ntdll" "kernel32" "msvcrt" "advapi32" "comctl32" "comdlg32" "ddraw" "d3d9" "d3dx10_43"
        "d3dx9_43" "gdi32" "imm32" "msvcr100" "shell32" "shlwapi" "user32" "version" "xinput1_3" "winmm"
        "wsock32" "ws2_32" "iphlpapi" "secur32" "wininet" "advpack" "riched20" "riched32" "usp10" "dsound"
        "winspool.drv" "dinput")
#
for dll in "${dlls[@]}"
do
    mkdir -p $DESTDIR/build.android/dlls32/$dll
    cd $DESTDIR/build.android/dlls32/$dll
    echo "GUEST_CC=i686-w64-mingw32" > Makefile
    echo "SRCDIR=../../../dlls/$dll" >> Makefile
    echo "DESTDIR?=../../.." >> Makefile
    echo "GUEST_BIT=32" >> Makefile
    echo "HOST_BIT=32" >> Makefile
    echo "WINE_DIR=wine-guest32" >> Makefile
    echo >> Makefile
    echo "include $SRCDIR/dlls/$dll/Makefile" >> Makefile
#
    make -j4 WINEGCC="$DESTDIR/build.android/wine-host/tools/winegcc/winegcc -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib --sysroot=$DESTDIR/build.android/wine-host -b arm-linux-androideabi -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include"
    ln -sf $PWD/$dll.dll $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll32
    ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build.android/qemu/i386-windows-user/qemu_host_dll32
done
#
# Link Wine libraries.
declare -a wine_dlls=("dbghelp" "ole32" "oleaut32" "propsys" "rpcrt4" "urlmon" "windowscodecs" "netapi32" "dnsapi" "msimg32"
        "crypt32" "dwmapi" "uxtheme" "setupapi" "wintrust" "wtsapi32" "pdh" "avrt" "cryptnet" "imagehlp" "cryptui" "sensapi"
        "msvcp80" "msvcp100" "lz32" "cabinet" "msi" "dplay" "dplayx" "dpwsockx" "dpnet" "dpnaddr" "dpnhpast" "dpnlobby"
        "dpvoice" "mpr" "oledlg")
ln -sf $DESTDIR/build.android/wine-guest32/libs/wine/libwine.dll $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll32
#
for dll in "${wine_dlls[@]}"
do
    ln -sf $DESTDIR/build.android/wine-guest/dlls/$dll/$dll.dll $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll32
done
ln -sf $DESTDIR/build.android/wine-guest32/dlls/winspool.drv/winspool.drv $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll32
#
set +e
#
# Resetup the apk with qemu
cp -lf $DESTDIR/build.android/qemu/i386-windows-user/qemu-i386.exe.so $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/bin/
cp -rf $DESTDIR/build.android/qemu/i386-windows-user/qemu_host_dll $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/bin/
cp -rf $DESTDIR/build.android/qemu/i386-windows-user/qemu_guest_dll $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/bin/
mkdir -p $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/lib/armeabi-v7a
cp -f  $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/lib/* $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/lib/armeabi-v7a/
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/armeabi-v7a/include
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/include
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/wine-debug.apk
make -C $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/
#
