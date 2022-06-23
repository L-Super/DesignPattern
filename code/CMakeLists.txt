cmake_minimum_required(VERSION 3.22)
project(DesignPattern)

set(CMAKE_CXX_STANDARD 14)

set(SRC
#        main.cpp
#        Flyweight.cpp
#        Factory.cpp
#        AbstractFactory.cpp
        Observer.cpp
        )

set(INCLUDEDIR ${CMAKE_SOURCE_DIR}/include)
if (NOT EXISTS ${INCLUDE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${INCLUDEDIR})
    message(STATUS "create dir ${INCLUDEDIR}")
endif ()

set(SPDLOGDIR ${CMAKE_SOURCE_DIR}/include/spdlog)

find_package(Git)
if (NOT GIT_FOUND)
    message(ERROR "Git required to build this tool")
endif ()

if (NOT EXISTS ${SPDLOGDIR})
    message("spdlog not exists")
#    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${SPDLOGDIR})
    execute_process(COMMAND git submodule add "https://github.com/gabime/spdlog.git"
            WORKING_DIRECTORY ${INCLUDEDIR}
            RESULT_VARIABLE GIT_RESULT
            OUTPUT_VARIABLE GIT_OUTPUT
            ERROR_VARIABLE  GIT_ERROR
            )
    if (NOT ${GIT_ERROR} EQUAL 0)
        message(SEND_ERROR "Command ${GIT_EXECUTABLE} clone failed with output:\n${GIT_ERROR}")
    endif ()
    message(STATUS "spdlog dir = ${SPDLOGDIR}")
#    message(STATUS "Git result = ${GIT_RESULT} Git output = ${GIT_OUTPUT} Git error = ${GIT_ERROR}")
endif ()

include_directories(${SPDLOGDIR}/include)

# fmt库通过FetchContent导入
include(FetchContent)
# FetchContent_Declare(<name> <contentOptions>...): 描述如何下载依赖库，name 声明下载库的名称，contentOptions 描述获取、更新外部库的方式
FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/archive/refs/tags/8.1.1.tar.gz)
FetchContent_MakeAvailable(fmt) #构建FetchContent_Declare所声明的name，即fmt。将库的声明与实际的下载分离，利于项目管理和维护。

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} fmt)
