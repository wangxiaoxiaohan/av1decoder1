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
       ./asm/itx.S
    )

enable_language(ASM ) #编译汇编 需要加上这个
# 如果你的汇编代码需要特定的编译选项，可以通过set_source_files_properties设置
#set_source_files_properties(src/vector_add.S PROPERTIES COMPILE_FLAGS "-march=armv8-a -mfpu=vfpv3-d16")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(av1decoder   ${SRC_LIST} ${ASM_LIST})

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall  -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -fsanitize=address -fno-omit-frame-pointer  -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64) 

#gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-none-linux-gnu-
#set(CMAKE_C_COMPILER /home/wanghan/Downloads/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc)
#set(CMAKE_CXX_COMPILER /home/wanghan/Downloads/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++)
#set(CMAKE_ASM_COMPILER /home/wanghan/Downloads/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-as) #汇编器
#set(CMAKE_LINKER /home/wanghan/Downloads/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-ld)

set(CMAKE_C_COMPILER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)
set(CMAKE_ASM_COMPILER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc) #汇编器 ，使用-as 会出现识别到__MACH__的情况
set(CMAKE_LINKER /home/wanghan/Downloads/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-ld)
#target_compile_options(av1decoder PRIVATE -march=armv8-a)

#enable_language(CXX C ASM ASM-ATT)