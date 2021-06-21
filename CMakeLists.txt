cmake_minimum_required(VERSION 3.19)
project(TEC_FILE_SYSTEM)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(CMAKE_PREFIX_PATH ${CONAN_LIBS})

## In most cases better set in the CMake cache
set(SFML_DIR "/usr/include/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_library(Sockets
        src/Socket/Server.cpp
        src/Socket/Server.h
        "src/Socket/TEST Sockets.cpp"
        src/Socket/Huffman.cpp
        src/Socket/Huffman.h
        src/Socket/Client.cpp
        src/Socket/Client.h)
target_link_libraries(Sockets
        ${CONAN_LIBS})

add_executable(CE_Programs
        "src/CE programs/main.cpp"
        "src/CE programs/Interface.cpp"
        "src/CE programs/Interface.h"
        "src/CE programs/InputBox.h"
        "src/CE programs/InputBox.cpp"
  )

target_link_libraries(CE_Programs
        ${CONAN_LIBS}
        Sockets
        sfml-graphics
        sfml-audio
        )

add_executable(Node_Controller
        "src/Node Controller/NodeController.cpp"
        "src/Node Controller/NodeController.h")

target_link_libraries(Node_Controller
        ${CONAN_LIBS}
        Sockets
        )

add_executable(Disk_Nodes
        "src/Disk Nodes/DiskNodes.cpp"
        "src/Disk Nodes/DiskNodes.h")

target_link_libraries(Disk_Nodes
        ${CONAN_LIBS}
        Sockets
        )

add_executable(test
        "src/Socket/TEST Sockets.cpp")

target_link_libraries(test
        ${CONAN_LIBS}
        Sockets
        )