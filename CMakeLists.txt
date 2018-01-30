cmake_minimum_required(VERSION 3.8)
project(ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")

set(SOURCE_FILES
        Group.h
        Group.cpp
        exceptions.h
        testMacros.h
        ./test/GroupTests.cpp
        )

add_executable(Group_tests ${SOURCE_FILES})


set(SOURCE_FILES
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        exceptions.h
        testMacros.h
        ./test/ClanTests.cpp
        )

add_executable(Clan_tests ${SOURCE_FILES})

set(SOURCE_FILES
        MtmSet.h
        exceptions.h
        testMacros.h
        ./test/MtmSetTests.cpp
        )

add_executable(MtmSet_tests ${SOURCE_FILES})

set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Plain.h
        Plain.cpp
        Mountain.h
        Mountain.cpp
        River.h
        River.cpp
        World.h
        World.cpp
        exceptions.h
        testMacros.h
        ./test/WorldTests.cpp
        )

add_executable(World_tests ${SOURCE_FILES})

set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Plain.h
        Plain.cpp
        Mountain.h
        Mountain.cpp
        River.h
        River.cpp
        exceptions.h
        testMacros.h
        ./test/AreaTests.cpp
        )

add_executable(Area_tests ${SOURCE_FILES})


set(SOURCE_FILES
        Group.h
        Group.cpp
        exceptions.h
        testMacros.h
        examplePart1.cpp
        )

add_executable(example1 ${SOURCE_FILES})

set(SOURCE_FILES
        MtmSet.h
        exceptions.h
        testMacros.h
        examplePart2.cpp
        )

add_executable(example2 ${SOURCE_FILES})

set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Plain.h
        Plain.cpp
        Mountain.h
        Mountain.cpp
        River.h
        River.cpp
        World.h
        World.cpp
        exceptions.h
        testMacros.h
        examplePart3.cpp
        )

add_executable(example3 ${SOURCE_FILES})