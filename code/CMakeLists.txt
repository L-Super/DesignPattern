cmake_minimum_required(VERSION 3.22)
project(DesignPattern)

set(CMAKE_CXX_STANDARD 14)

set(SRC
#        main.cpp
#        Flyweight.cpp
#        Factory.cpp
        AbstractFactory.cpp
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
    execute_process(COMMAND git clone "https://github.com/gabime/spdlog.git"
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

add_executable(${PROJECT_NAME} ${SRC})
