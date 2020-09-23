from debian:buster-slim as base
arg TARGETPLATFORM
arg BUILDPLATFORM

workdir /tmp
copy deps.sh env.sh setup.sh external/fwlib/*.so.1.0.5 ./
run . ./env.sh && ./setup.sh && ldconfig /lib

from base as builder

workdir /usr/src/app

copy . .

run . ./env.sh && \
  /tmp/deps.sh && \
  echo ARCH $ARCH && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make
#  make install

from base
copy --from=builder /usr/src/app/build/fanuc_example /usr/local/bin/
cmd ["fanuc_example", "localhost", "8193"]
