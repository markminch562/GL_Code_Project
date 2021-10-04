cmake_minimum_required(VERSION 3.19)
project(GLAD)

add_library(glad src/glad.c)
add_library(sub::glad ALIAS glad)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/include)