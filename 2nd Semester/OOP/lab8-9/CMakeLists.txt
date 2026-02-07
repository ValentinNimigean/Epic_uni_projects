cmake_minimum_required(VERSION 3.22)
project(oop_a8_9_915_Nimigean_Valentin)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.1\\mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

include_directories(.)
#include_directories(. GUI)

qt_add_executable(

        oop_a8_9_915_Nimigean_Valentin
        Controller.cpp
        Controller.h
        Domain.cpp
        Domain.h
        File_writer.cpp
        File_writer.h
        Main.cpp
        Repository.cpp
        Repository.h
        Tests.cpp
        Tests.h
        TrenchCoat_exceptions.cpp
        TrenchCoat_exceptions.h
        User_interface.cpp
        User_interface.h
        Principal_window.cpp
        Principal_window.h
        Principal_window.h
        Admin_window.cpp
        Admin_window.h
        User_WIndow.cpp
        User_WIndow.h
        User_WIndow.h
        SQL_repo.cpp
        SQL_repo.h
        Graph_window.cpp
        Graph_window.h
        UndoRedo.h
        Basket.h
        Basket.cpp
        BasketWindow.h
        BasketWindow.cpp)
target_link_libraries(oop_a8_9_915_Nimigean_Valentin PRIVATE Qt6::Widgets)

set_target_properties(oop_a8_9_915_Nimigean_Valentin PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDE ON
)