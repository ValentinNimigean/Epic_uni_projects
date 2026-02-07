cmake_minimum_required(VERSION 3.27)
project(t1_915_Nimigean_Valentin_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(t1_915_Nimigean_Valentin_1
        Repository.cpp
        Repository.h
        Domain.h
        Domain.cpp
        User_interface.h
        User_interface.cpp
        MAin.cpp
        Controller.cpp
        Tests.h
        Tests.cpp
)
