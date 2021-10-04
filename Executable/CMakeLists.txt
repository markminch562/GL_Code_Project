cmake_minimum_required(VERSION 3.19)
PROJECT(EXECUTABLE1)

add_executable(${PROJECT_NAME} main.cpp InputSystem/include/View.h)

target_link_libraries(${PROJECT_NAME} glad glfw LoadSystem)

