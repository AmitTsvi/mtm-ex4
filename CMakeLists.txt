cmake_minimum_required(VERSION 3.8)
project(ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")

set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Area.h
        Area.cpp
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
        ./test/GroupTests.cpp
        )

add_executable(Group_tests ${SOURCE_FILES})


set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Area.h
        Area.cpp
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
        ./test/ClanTests.cpp
        )

add_executable(Clan_tests ${SOURCE_FILES})

set(SOURCE_FILES
        Area.h
        Area.cpp
        Clan.h
        Clan.cpp
        Group.h
        Group.cpp
        MtmSet.h
        Area.h
        Area.cpp
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
        Area.h
        Area.cpp
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
        Area.h
        Area.cpp
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
        ./test/AreaTests.cpp
        )

add_executable(Area_tests ${SOURCE_FILES})