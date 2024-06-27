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
set(ASM_LIST 
       ./asm/itx4x4.S 
    
    )

enable_language(ASM) #编译arm汇编 需要加上这个
#set_source_files_properties(${ASM_LIST}  PROPERTIES LANGUAGE ASM)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(av1decoder  ${ASM_LIST} ${SRC_LIST})

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall  -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -fsanitize=address -fno-omit-frame-pointer  -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_C_COMPILER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)


#enable_language(CXX C ASM ASM-ATT)