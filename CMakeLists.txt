cmake_minimum_required(VERSION 3.8)
project(ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")

set(SOURCE_FILES
        Area.h
        Clan.h
        examplePart1.cpp
        examplePart2.cpp
        examplePart3.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h)

add_executable(ex4 ${SOURCE_FILES})