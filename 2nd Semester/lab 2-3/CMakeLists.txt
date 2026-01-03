cmake_minimum_required(VERSION 3.27)
project(A2_3 C)

set(CMAKE_C_STANDARD 11)


add_executable(A2_3 main.c
        controller.c
        domain.c
        domain.h
        repository.h
        repository.c
        controller.h
        ui.c
        ui.h
        tests.c
        tests.h
        FunctionPointers.c
        FunctionPointers.h)
