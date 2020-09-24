# start with lightish image.  need glibc for fwlib, otherwise would use alpine
from debian:buster-slim as base
# these vars used by buildx (not set if not declared)
arg TARGETPLATFORM
arg BUILDPLATFORM

workdir /tmp
# bring all (x64,x86,arm) so
copy deps.sh env.sh setup.sh external/fwlib/*.so.1.0.5 ./
# get dependencies, move so based on architecture
run . ./env.sh && ./setup.sh && ldconfig /lib

# add lots of stuff for compilation
from base as builder

workdir /usr/src/app

# setup build dependencies
run . /tmp/env.sh && /tmp/deps.sh

copy . .

# cmake, make
run . /tmp/env.sh && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make
# && \ make install

# go back to lightish image. bring over compiled binary
from base
copy --from=builder /usr/src/app/build/fanuc_example /usr/local/bin/
cmd ["fanuc_example", "localhost", "8193"]
