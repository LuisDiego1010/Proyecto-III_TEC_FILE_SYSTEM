cmake_minimum_required(VERSION 3.19)
project(TEC_FILE_SYSTEM)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_PREFIX_PATH ${CONAN_LIBS})
add_executable(TEC_FILE_SYSTEM
        src/Socket/Server.cpp
        src/Socket/Server.h
        "src/Socket/TEST Sockets.cpp"
        src/Socket/Huffman.cpp
        src/Socket/Huffman.h)
target_link_libraries(TEC_FILE_SYSTEM
        ${CONAN_LIBS})