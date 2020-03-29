cmake_minimum_required(VERSION 3.15)
project(rvm C)

set(CMAKE_C_STANDARD 99)

add_executable(rvm main.c rvm.c consts.h)
target_include_directories(rvm PUBLIC vendor/mruby/include/)
target_link_directories(rvm PUBLIC vendor/mruby/build/host/lib/)
target_link_libraries(rvm libmruby.a)
target_link_libraries(rvm m)