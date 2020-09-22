arg image=debian
from $image as builder
arg TARGETPLATFORM
arg BUILDPLATFORM

run apt-get update && apt-get install -y \
  cmake \
  gcc \
  g++ \
  make \
  unzip \
  wget

copy setup.sh external/fwlib/*.so.1.0.5 /tmp/
run /tmp/setup.sh && ldconfig /lib

workdir /usr/src/app

copy . .

run mkdir build && \
  cd build && \
  cmake .. && \
  make && \
  make install

cmd fanuc_example
