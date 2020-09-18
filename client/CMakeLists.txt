cmake_minimum_required(VERSION 3.10)

project(raspip VERSION 0.0.1)
option(BUPT_LOGIN "Login to BUPT wifi" OFF)
configure_file(RaspipConfig.hpp.in RaspipConfig.hpp)
add_executable(raspip raspip.cc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS raspip DESTINATION bin)