#include "testMacros.h"
#include "Group.h"
#include "World.h"
#include "exceptions.h"

using namespace mtm;

std::ostringstream os;


bool testAddClan(){
    World world;
    ASSERT_EXCEPTION(world.addClan(""), WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_EXCEPTION(world.addClan("knights"), WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_EXCEPTION(world.addClan("maesters"), WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("knights"), WorldClanNameIsTaken);

    return true;
}

bool testAddArea(){
    World world;
    ASSERT_EXCEPTION(world.addArea("",PLAIN), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addArea("",MOUNTAIN), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addArea("",RIVER), WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_EXCEPTION
    (world.addArea("king's landing",PLAIN), WorldAreaNameIsTaken);
    ASSERT_EXCEPTION
    (world.addArea("king's landing",MOUNTAIN), WorldAreaNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addArea("the eyrie",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("riverrun",RIVER));
    ASSERT_EXCEPTION(world.addArea("the eyrie",PLAIN), WorldAreaNameIsTaken);
    ASSERT_EXCEPTION(world.addArea("riverrun",MOUNTAIN), WorldAreaNameIsTaken);

    return true;
}

bool testAddGroup(){
    World world;
    ASSERT_EXCEPTION(world.addGroup("", "maesters", 0, 1, "winterfell"), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("", "maesters", -1, 1, "winterfell"), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("", "maesters", 1, -1, "winterfell"), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("", "maesters", 0, 0, "winterfell"), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("stark", "maesters", 0, 10, "winterfell"), WorldClanNotFound);
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_EXCEPTION(world.addGroup("stark", "maesters", 0, 10, "winterfell"), WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("winterfell",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_EXCEPTION(world.addGroup("stark", "children of the forest", 0, 10, "winterfell"), WorldClanNotFound);
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "maesters", 0, 10, "winterfell"));
    ASSERT_EXCEPTION(world.addGroup("stark", "maesters", 0, 10, "winterfell"), WorldGroupNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addGroup("tully", "maesters", 0, 4, "winterfell"));
    ASSERT_EXCEPTION(world.addGroup("tully", "maesters", 0, 10, "winterfell"), WorldGroupNameIsTaken);

    return true;
}

bool testMakeReachable(){
    World world;
    ASSERT_EXCEPTION(world.makeReachable("winterfell", "volantis"), WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("winterfell",PLAIN));
    ASSERT_EXCEPTION(world.makeReachable("winterfell", "volantis"), WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("volantis",MOUNTAIN));
    ASSERT_EXCEPTION(world.makeReachable("free cities", "volantis"), WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("free cities",RIVER));
    ASSERT_NO_EXCEPTION(world.makeReachable("volantis","free cities"));
    ASSERT_NO_EXCEPTION(world.makeReachable("free cities","volantis"));

    return true;
}

bool testMoveGroup(){
    World world;
    ASSERT_EXCEPTION(world.moveGroup("stark","king's landing"), WorldGroupNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("winterfell",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "maesters", 0, 10, "winterfell"));
    ASSERT_EXCEPTION(world.moveGroup("stark","king's landing"), WorldAreaNotFound);
    ASSERT_EXCEPTION(world.moveGroup("stark","winterfell"), WorldGroupAlreadyInArea);
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_EXCEPTION(world.moveGroup("stark","king's landing"), WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(world.makeReachable("king's landing","winterfell"));
    ASSERT_EXCEPTION(world.moveGroup("stark","king's landing"), WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(world.makeReachable("winterfell","king's landing"));
    ASSERT_NO_EXCEPTION(world.moveGroup("stark","king's landing"));
    ASSERT_EXCEPTION(world.moveGroup("stark","king's landing"), WorldGroupAlreadyInArea);
    ASSERT_NO_EXCEPTION(world.moveGroup("stark","winterfell"));
    ASSERT_EXCEPTION(world.moveGroup("stark","winterfell"), WorldGroupAlreadyInArea);
    ASSERT_NO_EXCEPTION(world.moveGroup("stark","king's landing"));

    return true;
}

bool testMakeFriends(){
    World world;
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_NO_EXCEPTION(world.addClan("crows"));
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("lannisport",RIVER));
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "knights", 0, 10, "king's landing"));
    ASSERT_NO_EXCEPTION(world.addGroup("martell", "maesters", 0, 10, "king's landing"));
    ASSERT_NO_EXCEPTION(world.addGroup("lannister", "knights", 0, 10, "lannisport"));
    ASSERT_EXCEPTION(world.makeFriends("maesters", "children of the forest"), WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("children of the forest", "knights"), WorldClanNotFound);
    ASSERT_NO_EXCEPTION(world.makeFriends("maesters", "knights"));
    ASSERT_NO_EXCEPTION(world.makeFriends("maesters", "crows"));
    ASSERT_NO_EXCEPTION(world.makeFriends("maesters", "crows"));

    return true;
}

bool testUniteClans(){
    World world;
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_NO_EXCEPTION(world.addClan("crows"));
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("lannisport",RIVER));
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "knights", 0, 500, "king's landing"));
    ASSERT_NO_EXCEPTION(world.addGroup("lannister", "knights", 400, 1000, "lannisport"));
    ASSERT_NO_EXCEPTION(world.addGroup("martell", "maesters", 0, 400, "king's landing"));
    ASSERT_EXCEPTION(world.uniteClans("maesters", "knights", ""), WorldInvalidArgument);
    ASSERT_EXCEPTION(world.uniteClans("maesters", "knights", "crows"), WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.uniteClans("children of the forest", "knights", "army"), WorldClanNotFound);
    ASSERT_EXCEPTION(world.uniteClans("maesters", "children of the forest", "army"), WorldClanNotFound);
    ASSERT_NO_EXCEPTION(world.uniteClans("maesters", "knights", "army"));
    ASSERT_NO_EXCEPTION(world.addGroup("tyrell", "army", 0, 10, "king's landing"));
    ASSERT_EXCEPTION(world.addGroup("tully", "maesters", 0, 10, "king's landing"), WorldClanNotFound);
    ASSERT_EXCEPTION(world.addGroup("greyjoy", "knights", 0, 10, "king's landing"), WorldClanNotFound);
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addClan("knights"));

    return true;
}

bool testPrintGroup(){
    World world;
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_NO_EXCEPTION(world.addClan("crows"));
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("lannisport",RIVER));
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "knights", 0, 10, "king's landing"));
    ASSERT_NO_EXCEPTION(world.addGroup("martell", "maesters", 0, 10, "king's landing"));
    world.printGroup(os, "stark");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: stark\n"
            "Group's clan: knights\n"
            "Group's children: 0\n"
            "Group's adults: 5\n"
            "Group's tools: 20\n"
            "Group's food: 15\n"
            "Group's morale: 77\n"
            "Group's current area: king's landing\n"));
    world.printGroup(os, "martell");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: martell\n"
            "Group's clan: maesters\n"
            "Group's children: 0\n"
            "Group's adults: 5\n"
            "Group's tools: 20\n"
            "Group's food: 15\n"
            "Group's morale: 77\n"
            "Group's current area: king's landing\n"));
    return true;
}

bool testPrintClan(){
    World world;
    ASSERT_NO_EXCEPTION(world.addClan("knights"));
    ASSERT_NO_EXCEPTION(world.addClan("crows"));
    ASSERT_NO_EXCEPTION(world.addClan("maesters"));
    ASSERT_NO_EXCEPTION(world.addArea("king's landing",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("lannisport",RIVER));
    ASSERT_NO_EXCEPTION(world.addGroup("stark", "knights", 0, 10, "king's landing"));
    ASSERT_NO_EXCEPTION(world.addGroup("martell", "maesters", 0, 8, "king's landing"));
    world.printClan(os, "knights");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: knights\n"
            "Clan's groups: \n"
            "stark_2\n"
            "stark\n"));
    world.printClan(os, "maesters");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: maesters\n"
            "Clan's groups: \n"
            "martell\n"));
    return true;
}

int main(){
    RUN_TEST(testAddClan);
    RUN_TEST(testAddArea);
    RUN_TEST(testAddGroup);
    RUN_TEST(testAddGroup);
    RUN_TEST(testMakeReachable);
    RUN_TEST(testMoveGroup);
    RUN_TEST(testMakeFriends);
    RUN_TEST(testUniteClans);
    RUN_TEST(testPrintGroup);
    RUN_TEST(testPrintClan);


    return 0;
}
