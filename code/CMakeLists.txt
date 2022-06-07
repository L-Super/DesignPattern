cmake_minimum_required(VERSION 3.22)
project(DesignPattern)

set(CMAKE_CXX_STANDARD 14)

set(SRC
#        main.cpp
#        Flyweight.cpp
        Factory.cpp
        )

add_executable(${PROJECT_NAME} ${SRC})
