# Fanuc Minimal Communication Example  
This is a c/CMake project with minimal configuration required 
to test cnc functions provided by the Fanuc FOCAS library.

Supported architectures: x86, armv7/8/hf, x64 (unresolved problems with long, ulong)  

# Build & Run Instructions  

## Docker
- `docker-compose build && docker-compose up` (requires docker-compose)  
OR  
- `docker run --rm -it $(docker build -q .)` (builds and runs image)  

## Manual
- `mkdir build && cd build` (Create a build folder)  
- `cmake ..` (Run cmake)  
- `make` (Run make, build the executable)  
- `./fanuc_example` (Run the executable)  

# Resources  
[fwlib library documentation](https://www.inventcom.net/fanuc-focas-library/general/fwlib32 "fwlib")  
