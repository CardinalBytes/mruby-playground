cmake_minimum_required(VERSION 3.15)
project(mruby_sink C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build)

add_executable(mruby_sink src/main.c src/mruby_sink.c src/consts.h)
target_include_directories(mruby_sink PUBLIC vendor/mruby/include/)
target_link_directories(mruby_sink PUBLIC vendor/mruby/build/host/lib/)
target_link_libraries(mruby_sink libmruby.a)
target_link_libraries(mruby_sink m)
add_custom_command(TARGET mruby_sink POST_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/postbuild.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Compiling gems"
        )

