# Fanuc Minimal Communication Example  
This is a c/CMake project with minimal configuration required 
to test cnc functions provided by the Fanuc FOCAS library.

Supported architectures: x86, armv7/hf, aarch64, x64

# Build & Run Instructions  

## Docker
- `docker-compose build && docker-compose up` (requires docker-compose)  
OR  
- `docker run --rm -it $(docker build -q .)` (builds and runs image)  

## Manual
- `git submodule update --init --recursive`  
- Copy libfwlib32\*.so to `/usr/local/lib` or rename / link libfwlib32-\* according to your architecture in `external/fwlib` i.e. (`ln -s libfwlib32-linux-x86.so.1.0.5 libfwlib32.so)`
- `mkdir build && cd build`  
- `cmake ..`  
- `make`  
- `./fanuc_example`  

# Development
Docker images for multiple platforms can be built with `buildx`:  
```
docker buildx build --platform=linux/386,linux/arm/v7 .
```

# Resources  
[fwlib](https://github.com/strangesast/fwlib) header & lib files w/ another example  
[fwlib library documentation](https://www.inventcom.net/fanuc-focas-library/general/fwlib32 "fwlib")  

