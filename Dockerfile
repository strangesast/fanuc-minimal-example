from debian

run apt-get update && apt-get install -y \
  build-essential \
  cmake

workdir /usr/src/app

copy . .

run mkdir build && cd build && cmake .. && make

cmd ./build/bin/fanuc_example
