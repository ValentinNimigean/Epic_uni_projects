cmake_minimum_required(VERSION 3.22)
project(oop_a4_5_915_Nimigean_Valentin)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(oop_a4_5_915_Nimigean_Valentin
        Repository.cpp
        Repository.h
        Domain.h
        Domain.cpp
        Dynamic_Vector.h
        Dynamic_Vector.cpp
        Controller.h
        Controller.cpp
        Tests.h
        Main.cpp
        Tests.cpp
        User_interface.cpp
        User_interface.h
)
