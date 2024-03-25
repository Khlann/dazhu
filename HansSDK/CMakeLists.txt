cmake_minimum_required(VERSION 3.0.0)
project(HansSDK VERSION 0.1.0)

# set(rrr main.cpp)
set(CMAKE_BUILD_TYPE "Debug")
include_directories(/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/inc/home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/inc)
add_executable(HansSDK /home/xh/xh/HansSDK_demo/home/wayne/Desktop/HansSDK/src/Move.cpp)
# target_link_libraries(yyyyy /mnt/hgfs/HansRobotV5/HansSDK/bin/libtestSSo.so)
target_link_libraries(HansSDK /usr/local/lib/libHR_Pro.so)
find_package(Threads)

target_link_libraries(HansSDK ${CMAKE_THREAD_LIBS_INIT})


