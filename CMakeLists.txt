# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

project(libospath_project)

add_library(ospath STATIC src/os_path.cpp)

install(TARGETS ospath DESTINATION lib)
install(FILES src/os_path.hpp DESTINATION include)
