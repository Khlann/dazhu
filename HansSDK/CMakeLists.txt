cmake_minimum_required(VERSION 3.0.0)
project(HansSDK VERSION 0.1.0)

# set(rrr main.cpp)
set(CMAKE_BUILD_TYPE "Debug")
# 获取所有的.cpp和.h文件
file(GLOB SOURCES "/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/src/*.cpp")
file(GLOB HEADERS "/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/inc/*.h")

include_directories(/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/inc)
include_directories(/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/src)
add_executable(HansSDK /home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/src/main.cpp /home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/src/Dazhu.cpp)

# target_link_libraries(yyyyy /mnt/hgfs/HansRobotV5/HansSDK/bin/libtestSSo.so)
target_link_libraries(HansSDK /usr/local/lib/libHR_Pro.so)
find_package(Threads)

target_link_libraries(HansSDK ${CMAKE_THREAD_LIBS_INIT})


