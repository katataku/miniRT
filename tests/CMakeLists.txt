cmake_minimum_required(VERSION 3.0)
project(minirt C CXX)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS "../srcs/**/*.c")
file(GLOB LIBFT "../libft/**/*.c")
file(GLOB XSYSCALL "../srcs/xsyscall/*.c")

include_directories("../libft/includes")
include_directories("../includes")
include_directories("../mlx")
include_directories("/usr/X11R6/include")

add_library(minirt
        STATIC
        ${SRCS}
        ${LIBFT}
        ${XSYSCALL}
#        ../main.c
)

add_executable(main
        main.cpp
        vector.cpp
        io.cpp
        utils.cpp
        )

target_link_libraries(main
    PRIVATE
    GTest::GTest
    GTest::Main
    minirt
)
