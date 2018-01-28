cmake_minimum_required(VERSION 3.8)
project(ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")

set(SOURCE_FILES
        Area.h
        Clan.h
        testsPart1.cpp
        examplePart2.cpp
        examplePart2.cpp
        Group.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h)

add_executable(Group_tests Group.h Group.cpp exceptions.h testMacros.h Group_test.cpp)

set(SOURCE_FILES
        Group.h Group.cpp exceptions.h testMacros.h Group_test.cpp)

add_executable(Clan_tests Clan.h Clan.cpp MtmSet.h Group.h Group.cpp tmpClanTests.cpp)

set(SOURCE_FILES
        Clan.h Clan.cpp MtmSet.h Group.h Group.cpp tmpClanTests.cpp)

add_executable(examplePart3 Area.h
        Clan.h
        Group.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h
        World.cpp)

set(SOURCE_FILES Area.h
        Clan.h
        Group.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h
        World.cpp)

add_executable(World_tests Area.h
        Clan.h
        Clan.cpp
        Group.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h
        Area.cpp
        World.cpp Mountain.cpp Mountain.h Plain.cpp Plain.h River.cpp River.h tmpWorldTests.cpp)

set(SOURCE_FILES
        Area.h
        Clan.h
        Group.cpp
        exceptions.h
        Group.h
        MtmSet.h
        testMacros.h
        World.h
        Area.cpp
        World.cpp Clan.cpp Mountain.cpp Mountain.h Plain.cpp Plain.h River.cpp River.h tmpWorldTests.cpp)