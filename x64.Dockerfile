from debian:buster-slim as base

copy external/fwlib/libfwlib32-linux-x64.so.1.0.5 /usr/local/lib/
run ln -s /usr/local/lib/libfwlib32-linux-x64.so.1.0.5 /usr/local/lib/libfwlib32.so && ldconfig

from base as builder
run apt-get update && apt-get install -y build-essential cmake

workdir /usr/src/app

copy . .

run mkdir build && cd build && cmake .. && make

from base

copy --from=builder /usr/src/app/build/fanuc_example /usr/local/bin/

cmd fanuc_example
