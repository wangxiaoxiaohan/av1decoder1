cmake_minimum_required(VERSION 3.16.3) 
project(av1decoder)

include_directories (./include)
set(SRC_LIST 
	./src/av1decoder.cpp
    ./src/obu.cpp
    ./src/frame.cpp
	)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(av1decoder ${SRC_LIST})
