cmake_minimum_required(VERSION 3.15)
project(rvm C)

set(CMAKE_C_STANDARD 99)

set(CLANG_LINK_FLAGS "-lm")
add_executable(rvm main.c)
target_include_directories(rvm PUBLIC vendor/mruby/include/)
target_link_directories(rvm PUBLIC vendor/mruby/build/host/lib/)
target_link_libraries(rvm libmruby.a)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CLANG_LINK_FLAGS}")