arch=$(arch)
tp=$TARGETPLATFORM
usearch="x86"
echo "$arch"
echo "$TARGETPLATFORM"
if [ -n "$tp" ]
then
  if [ "$tp" = "linux/amd64" ]; then
    usearch="x64"
  elif [ "$tp" = "linux/arm/v7" ]; then
    usearch="arm"
  fi
elif [ -n "$arch" ]; then
  if [ "$arch" = "x86_64" ]; then
    usearch="x64"
  elif [ "$arch" = "armv7l" ]; then
    usearch="arm"
  fi
fi
echo "using $usearch"
if [ "$usearch" = "x64" ]
then
  cp /tmp/libfwlib32-linux-x64.so.1.0.5 /lib/
  ln -s /lib/libfwlib32-linux-x64.so.1.0.5 /lib/libfwlib32.so
elif [ "$usearch" = "arm" ]
then
  cp /tmp/libfwlib32-linux-armv7.so.1.0.5 /lib/
  ln -s /lib/libfwlib32-linux-armv7.so.1.0.5 /lib/libfwlib32.so
else
  cp /tmp/libfwlib32-linux-x86.so.1.0.5 /lib/
  ln -s /lib/libfwlib32-linux-x86.so.1.0.5 /lib/libfwlib32.so
fi
