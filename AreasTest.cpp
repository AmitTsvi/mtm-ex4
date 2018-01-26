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
    clan_map.at("1").addGroup(Group("1.1", "1", 24, 0, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.1_2", "1", 1, 0, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.2", "1", 16, 0, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.3", "1", 19, 0, 2, 2, 80));
    clan_map.at("1").addGroup(Group("1.4", "1", 4, 0, 2, 2, 80));
    clan_map.at("2").addGroup(Group("2.1", "2", 20, 0, 2, 2, 80));
    clan_map.at("2").addGroup(Group("2.2", "2", 10, 0, 2, 2, 80));
    clan_map.at("2").addGroup(Group("2.3", "2", 200, 0, 2, 2, 80));
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

bool plainGroupAriveTest(){
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
    return true;
}

bool exampleMountain(){
    AreaPtr carmel(new Mountain("Carmel"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Alpha1", "Beta", clan_map));
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Lambda2", "Gamma", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Gamma").getGroup("Lambda2"));
    ASSERT_TRUE(VerifyOutput(os ,"Group's name: Lambda2\n"
            "Group's clan: Gamma\n"
            "Group's children: 3\n"
            "Group's adults: 3\n"
            "Group's tools: 10\n"
            "Group's food: 12\n"
            "Group's morale: 61\n"));
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
    RUN_TEST(plainGroupAriveTest);
    RUN_TEST(exampleMountain);
    RUN_TEST(exampleRiver);
    return 0;
}
