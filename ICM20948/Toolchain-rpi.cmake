# Taken from tutorial at https://medium.com/@au42/the-useful-raspberrypi-cross-compile-guide-ea56054de187
# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Specify file system root for target libraries.  
SET(SYSROOT /home/mattmunee/raspi/sysroot)

# Specify the location of the cross-compiler tools
SET(TOOLSDIR /home/mattmunee/raspi/gcc-6-tools/gcc-6-arm-linux-gnueabihf-master/armv6-rpi-linux-gnueabihf/bin)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER   ${TOOLSDIR}/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLSDIR}/arm-linux-gnueabihf-g++)

# Define the sysroot path for the RaspberryPi distribution in our tools folder 
SET(CMAKE_FIND_ROOT_PATH ${SYSROOT})

# Use our definitions for compiler tools
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories only
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_definitions(-Wall)

