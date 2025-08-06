cmake_minimum_required(VERSION 3.28.0)
set(PROJECT_NAME NDO)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} test/test.hpp main.cpp)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-local-typedefs -Wno-tautological-compare -Wno-unused-value)
endif()


target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)