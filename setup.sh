if [ "$ARCH" = "x64" ]
then
  dpkg --add-architecture i386 && apt-get update && apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386
fi
if [ "$ARCH" = "arm" ]
then
  cp /tmp/libfwlib32-linux-armv7.so.1.0.5 /lib/
  ln -s /lib/libfwlib32-linux-armv7.so.1.0.5 /lib/libfwlib32.so
else
  cp /tmp/libfwlib32-linux-x86.so.1.0.5 /lib/
  ln -s /lib/libfwlib32-linux-x86.so.1.0.5 /lib/libfwlib32.so
fi
