cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

project(ivr-task)

set(EXE_SOURCES
    main.cpp
    dataset.cpp
    csvreader.cpp
    
    dataset.hpp
    utils.hpp
    csvreader.hpp
)

include_directories(

)

add_executable(${PROJECT_NAME} ${EXE_SOURCES})

target_link_libraries (${PROJECT_NAME}
)
