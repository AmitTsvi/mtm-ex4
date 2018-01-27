#include "testMacros.h"
#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include "exceptions.h"

using namespace mtm;

typedef std::shared_ptr<Area> AreaPtr;

std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("1", Clan("1")));
    clan_map.insert(std::pair<std::string, Clan>("2", Clan("2")));
    clan_map.at("1").addGroup(Group("1.1", "1", 0, 24, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.1_2", "1", 0, 1, 1, 1, 80));
    clan_map.at("1").addGroup(Group("1.2", "1", 0, 16, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.3", "1", 0, 19, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.4", "1", 0, 4, 1, 1, 80));
    clan_map.at("2").addGroup(Group("2.1", "2", 0, 20, 2, 2, 80));
    clan_map.at("2").addGroup(Group("2.2", "2", 0, 10, 1, 1, 80));
    clan_map.at("2").addGroup(Group("2.3", "2", 0, 200, 2, 2, 80));
    return clan_map;
}

//PLAIN TESTS
bool plainCtorDtorTest(){
    ASSERT_NO_EXCEPTION(Plain plain1("One"));
    ASSERT_EXCEPTION(Plain error_plain(""), AreaInvalidArguments);
    return true;
}

bool plainReachableTest(){
    Plain plain1("One");
    ASSERT_TRUE(plain1.isReachable("One"));
    ASSERT_NO_EXCEPTION(plain1.addReachableArea("Two"));
    ASSERT_TRUE(plain1.isReachable("Two"));
    ASSERT_FALSE(plain1.isReachable("Three"));
    return true;
}

bool plainGroupArriveLeaveTest(){
    Plain plain1("1");
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(plain1.groupArrive("1.1", "TT", clan_map), AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(plain1.groupArrive("2.1", "1", clan_map), AreaGroupNotInClan);
    //1.1(24) added and divided to 1.1(12) and 1.1_3(12)
    ASSERT_NO_EXCEPTION(plain1.groupArrive("1.1", "1", clan_map));
    ASSERT_TRUE(plain1.getGroupsNames().size() == 2);
    ASSERT_EXCEPTION(plain1.groupArrive("1.1", "1", clan_map) ,AreaGroupAlreadyIn);
    //1.2(16) added and no group to unite with
    ASSERT_NO_EXCEPTION(plain1.groupArrive("1.2", "1", clan_map));
    //1.4(4) added and united with 1.2(20)
    ASSERT_NO_EXCEPTION(plain1.groupArrive("1.4", "1", clan_map));
    ASSERT_TRUE(plain1.getGroupsNames().size() == 3);
    ASSERT_TRUE(plain1.getGroupsNames().contains("1.1"));
    ASSERT_TRUE(plain1.getGroupsNames().contains("1.1_3"));
    ASSERT_TRUE(plain1.getGroupsNames().contains("1.2"));

    ASSERT_EXCEPTION(plain1.groupLeave("1.1.4"),AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(plain1.groupLeave("1.2"));
    ASSERT_FALSE(plain1.getGroupsNames().contains("1.2"));
    return true;
}

//Mountain TESTS
bool mountainCtorDtorTest(){
    ASSERT_NO_EXCEPTION(Mountain mount1("One"));
    ASSERT_EXCEPTION(Mountain error_mount(""), AreaInvalidArguments);
    return true;
}

bool mountainReachableTest(){
    Mountain mount1("One");
    ASSERT_TRUE(mount1.isReachable("One"));
    ASSERT_NO_EXCEPTION(mount1.addReachableArea("Two"));
    ASSERT_TRUE(mount1.isReachable("Two"));
    ASSERT_FALSE(mount1.isReachable("Three"));
    return true;
}

bool mountainGroupArriveLeaveTest(){
    Mountain mount1("1");
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(mount1.groupArrive("1.1", "TT", clan_map), AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(mount1.groupArrive("2.1", "1", clan_map), AreaGroupNotInClan);
    //1.4 is added and is now the ruler
    ASSERT_NO_EXCEPTION(mount1.groupArrive("1.4", "1", clan_map));
    ASSERT_EXCEPTION(mount1.groupArrive("1.4", "1", clan_map) ,AreaGroupAlreadyIn);
    //1.1 is added and is now the new ruler
    ASSERT_NO_EXCEPTION(mount1.groupArrive("1.2", "1", clan_map));
    //2.1 fights 1.1 and is now the new ruler
    ASSERT_NO_EXCEPTION(mount1.groupArrive("2.1", "2", clan_map));
    ASSERT_TRUE((clan_map.at("1").getGroup("1.2"))->getSize() == 10);
    ASSERT_TRUE((clan_map.at("2").getGroup("2.1"))->getSize() == 15);
    ASSERT_TRUE(mount1.getGroupsNames().size() == 3);
    ASSERT_TRUE(mount1.getGroupsNames().contains("1.2"));
    ASSERT_TRUE(mount1.getGroupsNames().contains("2.1"));
    ASSERT_TRUE(mount1.getGroupsNames().contains("1.4"));


    ASSERT_EXCEPTION(mount1.groupLeave("1.1.4"),AreaGroupNotFound);
    //2.1 leaves and 1.2 becomes the ruler
    ASSERT_NO_EXCEPTION(mount1.groupLeave("2.1"));
    //2.3 arrives and fights 1.2 and wins
    ASSERT_NO_EXCEPTION(mount1.groupArrive("2.3", "2", clan_map));
    ASSERT_TRUE(clan_map.at("1").getGroup("1.2")->getSize() == 6);
    //2.2 arrives, 2.3 is still the ruler
    ASSERT_NO_EXCEPTION(mount1.groupArrive("2.2", "2", clan_map));
    //2.1 arrives, 2.3 is still the ruler
    ASSERT_NO_EXCEPTION(mount1.groupArrive("2.1", "2", clan_map));
    //2.3 leaves and now 2.1 is the new ruler
    ASSERT_NO_EXCEPTION(mount1.groupLeave("2.3"));
    //1.1_2 arrives and fights 2.1 and loses
    ASSERT_NO_EXCEPTION(mount1.groupArrive("1.1_2", "1", clan_map));
    ASSERT_TRUE(clan_map.at("2").getGroup("2.1")->getSize() == 12);

    return true;
}


bool exampleRiver(){
    AreaPtr jordan(new River("Jordan"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Alpha1", "Beta", clan_map));
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Alpha2", "Beta", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Beta").getGroup("Alpha1"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha1\n"
            "Group's clan: Beta\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 53\n"
            "Group's food: 37\n"
            "Group's morale: 77\n"));
    return true;
}

int main(){
    RUN_TEST(plainCtorDtorTest);
    RUN_TEST(plainReachableTest);
    RUN_TEST(plainGroupArriveLeaveTest);
    RUN_TEST(mountainCtorDtorTest);
    RUN_TEST(mountainReachableTest);
    RUN_TEST(mountainGroupArriveLeaveTest);
    return 0;
}
