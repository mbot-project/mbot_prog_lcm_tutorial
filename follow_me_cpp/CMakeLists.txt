cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(follow_me)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(lcm REQUIRED)
include(${LCM_USE_FILE})
find_package(mbot_lcm_msgs)

# Follow me executable.
add_executable(follow_me
    src/follow_me.cpp
)
target_link_libraries(follow_me
  lcm
)
target_include_directories(follow_me PRIVATE
)
