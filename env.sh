arch=$(arch)
ARCH="x86"
if [ -n "$TARGETPLATFORM" ]
then
  if [ "$TARGETPLATFORM" = "linux/amd64" ]; then
    ARCH="x64"
  elif [ "$TARGETPLATFORM" = "linux/arm/v7" ]; then
    ARCH="arm"
  fi
elif [ -n "$arch" ]; then
  if [ "$arch" = "x86_64" ]; then
    ARCH="x64"
  elif [ "$arch" = "armv7l" ]; then
    ARCH="arm"
  fi
fi
export ARCH
