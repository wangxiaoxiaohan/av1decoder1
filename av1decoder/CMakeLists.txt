cmake_minimum_required(VERSION 3.10.2) 
project(av1decoder)

include_directories (./include)
set(SRC_LIST 
	./src/av1decoder.cpp
    ./src/obu.cpp
    ./src/frame.cpp
    ./src/segmentation.cpp
    ./src/cdf.cpp
    ./src/decode.cpp
	)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(av1decoder ${SRC_LIST})
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall  -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -fsanitize=address -fno-omit-frame-pointer  -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
