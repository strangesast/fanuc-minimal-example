# start with multiplatform base image (x86/amd64/armv7/aarch64) with fwlib installed
from strangesast/fwlib as base

# add lots of stuff for compilation
from base as builder

# installs compiler, cmake, multilib for intel/arm
copy external/fwlib/build-deps.sh /tmp/
run /tmp/build-deps.sh

workdir /usr/src/app

copy . .

# cmake, make
run mkdir build && \
  cd build && \
  cmake .. && \
  make

# go back to lightish image. bring over compiled binary
from base
copy --from=builder /usr/src/app/build/bin/fanuc_example /usr/local/bin/
cmd ["fanuc_example", "localhost", "8193"]
