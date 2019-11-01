cmake_minimum_required(VERSION 3.7)

project(icm20948)

#if(UNIX)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -std=c++11")
#endif(UNIX)

set(ICM20948_SRC "../Source")
set(ICM20948_INC "../Include")

file(GLOB_RECURSE ICM20948_SRC
	"../Source/*.cpp"
    "../Source/*.c"
)

file(GLOB_RECURSE ICM20948_INC
	"../Include/*.hpp"
	"../Include/*.h"
)

if(CMAKE_CROSSCOMPILING)
    set(CMAKE_SYSROOT_COMPILE ${SYSROOT})
    include_directories(${SYSROOT}/usr/include/arm-linux-gnueabihf)
endif()

include_directories("../Include")

add_executable(${PROJECT_NAME} ${ICM20948_SRC} ${ICM20948_INC})

