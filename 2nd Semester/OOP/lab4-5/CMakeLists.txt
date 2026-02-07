cmake_minimum_required(VERSION 3.27)
project(oop_a4_5_915_Nimigean_Valentin)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(oop_a4_5_915_Nimigean_Valentin
        Domain.cpp
        Domain.h
        Main.cpp
        Dynamic_Vector.h
        Dynamic_Vector.cpp
        Repository.h
        Repository.cpp
        Controller.h
        Controller.cpp
        User_interface.h
        User_interface.cpp
        Tests.h
        Tests.cpp)
