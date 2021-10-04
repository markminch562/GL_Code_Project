cmake_minimum_required(VERSION 3.19)
project(LoadSystem)

add_library(LoadSystem ShaderSystems.cpp ShaderSystem.h Shader.cpp Shader.h)
target_include_directories(LoadSystem PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(LoadSystem sub::glad glm::glm)