#include "testMacros.h"
#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include "exceptions.h"
#include "World.h"

using namespace mtm;
std::ostringstream os;
//------------------------------------------------------------------------------
/**
 * Clan tests
 */
//------------------------------------------------------------------------------

bool testCtors(){
    //Invalid clan name
    ASSERT_EXCEPTION(Clan(""), ClanEmptyName);
    ASSERT_NO_EXCEPTION(Clan("Knesset"));
    Clan knesset("Knesset");

    //Copy constructor
    Clan knesset_copy(knesset);

    return true;
}

bool testAddGroup(){
    Group likud("Likud", "Knesset",1,1, 1, 1, 90);
    Group shas("Shas", "Knesset", 2, 2, 2, 2, 70);
    Group habayit_hayehudi("Shas", 4, 4);

    Clan knesset("Knesset");

    ASSERT_NO_EXCEPTION(knesset.addGroup(shas));
    //knesset has already one clan with the name Shas
    ASSERT_EXCEPTION
    (knesset.addGroup(habayit_hayehudi), ClanGroupNameAlreadyTaken);

    shas.unite(likud, 10);

    //Trying to add an emtpy group - after the union likud is empty
    ASSERT_EXCEPTION(knesset.addGroup(likud), ClanGroupIsEmpty);

    return true;
}

bool testGetGroup(){
    Group yesh_atid("Yesh Atid", "Knesset",1,1, 1, 1, 60);
    Group joint_list("Joint List", "Knesset",1,1, 1, 1, 60);
    Group ale_yarok("Ale Yarok", "",1,1, 1, 1, 60);


    Clan knesset("Knesset");

    ASSERT_NO_EXCEPTION(knesset.addGroup(yesh_atid));
    ASSERT_NO_EXCEPTION(knesset.addGroup(joint_list));

    //No matching group in clan
    ASSERT_EXCEPTION(knesset.getGroup("Ale Yarok"), ClanGroupNotFound);
    //There is matching group in clan
    ASSERT_NO_EXCEPTION(knesset.getGroup("Yesh Atid"));
    ASSERT_NO_EXCEPTION(knesset.getGroup("Joint List"));

    GroupPointer yesh_atid_ptr = knesset.getGroup("Yesh Atid");
    GroupPointer joint_list_ptr = knesset.getGroup("Joint List");

    ASSERT_TRUE((*yesh_atid_ptr).getName() == yesh_atid.getName());
    ASSERT_TRUE((*joint_list_ptr).getName() == joint_list.getName());

    return true;
}

bool testDoesContain(){
    Group yesh_atid("Yesh Atid", "Knesset",1,1, 1, 1, 60);
    Group joint_list("Joint List", "Knesset",1,1, 1, 1, 60);
    Group ale_yarok("Ale Yarok", "",1,1, 1, 1, 60);


    Clan knesset("Knesset");

    ASSERT_NO_EXCEPTION(knesset.addGroup(yesh_atid));
    ASSERT_NO_EXCEPTION(knesset.addGroup(joint_list));

    ASSERT_TRUE(knesset.doesContain("Yesh Atid"));
    ASSERT_TRUE(knesset.doesContain("Joint List"));
    ASSERT_FALSE(knesset.doesContain("Ale_Yarok"));
    return true;
}

bool testGetSize(){
    Group likud("Likud",29,1);
    Group ale_yarok("Ale Yarok", "Knesset",10,10, 100, 200, 100);

    Clan knesset("knesset");

    ASSERT_NO_EXCEPTION(knesset.addGroup(likud));
    ASSERT_TRUE(knesset.getSize() == 30);
    ASSERT_NO_EXCEPTION(knesset.addGroup(ale_yarok));
    ASSERT_TRUE(knesset.getSize() == 50);

    return true;
}

bool testUnite(){
    Group likud("Likud",1,29);
    Group habayit_hayehudi("Habayit Hayehudi", 0, 8);
    Group joint_list("Joint List",0, 13);
    Group meretz("Meretz", 0, 5);

    Clan opposition("Opposition");
    Clan coalition("Coalition");

    ASSERT_NO_EXCEPTION(opposition.addGroup(joint_list));
    ASSERT_NO_EXCEPTION(opposition.addGroup(meretz));
    ASSERT_NO_EXCEPTION(coalition.addGroup(likud));
    ASSERT_NO_EXCEPTION(coalition.addGroup(habayit_hayehudi));

    ASSERT_NO_EXCEPTION(coalition.unite(opposition, "Knesset"));
    ASSERT_TRUE(coalition.getSize() == 56);
    ASSERT_TRUE(opposition.getSize() == 0);

    ASSERT_EXCEPTION(coalition.unite(opposition, ""), ClanEmptyName);

    ASSERT_NO_EXCEPTION(opposition.addGroup(joint_list));
    //Has the same (named) group in both of clans
    ASSERT_EXCEPTION(coalition.unite(opposition, "Knesset"), ClanCantUnite);

    //This clan == other clan
    ASSERT_EXCEPTION(coalition.unite(coalition, "Knesset"), ClanCantUnite);
    return true;
}

bool testFriends(){
    Group likud("Likud",1,29);
    Group habayit_hayehudi("Habayit Hayehudi", 0, 8);
    Group joint_list("Joint List",0, 13);
    Group meretz("Meretz", 0, 5);

    Clan opposition("Opposition");
    Clan coalition("Coalition");
    Clan knesset("Knesset");

    ASSERT_NO_EXCEPTION(opposition.addGroup(joint_list));
    ASSERT_NO_EXCEPTION(opposition.addGroup(meretz));
    ASSERT_NO_EXCEPTION(coalition.addGroup(likud));
    ASSERT_NO_EXCEPTION(coalition.addGroup(habayit_hayehudi));

    ASSERT_FALSE(opposition.isFriend(coalition));
    ASSERT_FALSE(coalition.isFriend(opposition));

    ASSERT_NO_EXCEPTION(opposition.makeFriend(coalition));
    ASSERT_NO_EXCEPTION(knesset.makeFriend(coalition));
    ASSERT_TRUE(opposition.isFriend(coalition));
    ASSERT_TRUE(coalition.isFriend(opposition));
    ASSERT_TRUE(knesset.isFriend(coalition));
    ASSERT_TRUE(coalition.isFriend(knesset));
    ASSERT_FALSE(knesset.isFriend(opposition));
    ASSERT_FALSE(opposition.isFriend(knesset));

    return true;
}

bool testPrint(){
    Group likud("Likud",1,29);
    Group habayit_hayehudi("Habayit Hayehudi", 0, 8);
    Group joint_list("Joint List",0, 13);
    Group meretz("Meretz", 0, 5);

    Clan opposition("Opposition");
    Clan coalition("Coalition");
    Clan knesset("Knesset");

    os << knesset;
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Knesset\n"
            "Clan's groups:\n"));

    ASSERT_NO_EXCEPTION(opposition.addGroup(joint_list));
    ASSERT_NO_EXCEPTION(opposition.addGroup(meretz));
    ASSERT_NO_EXCEPTION(coalition.addGroup(likud));
    ASSERT_NO_EXCEPTION(coalition.addGroup(habayit_hayehudi));

    os << opposition << coalition;
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Opposition\n"
            "Clan's groups:\n"
            "Joint List\n"
            "Meretz\n"
            "Clan's name: Coalition\n"
            "Clan's groups:\n"
            "Likud\n"
            "Habayit Hayehudi\n"));

    return true;
}
//------------------------------------------------------------------------------
/**
 * Area tests
 */
//------------------------------------------------------------------------------

typedef std::shared_ptr<Area> AreaPtr;
bool exampleClan(){
    Clan beta("Beta");
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha1", 10, 10)));
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha2", 5, 5)));
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha3", 15, 15)));
    ASSERT_NO_EXCEPTION(beta.getGroup("Alpha1")->getClan() == "Beta");
    ASSERT_TRUE(beta.doesContain("Alpha2"));
    ASSERT_TRUE(beta.getSize() == 60);
    Clan beta2("Beta2");
    ASSERT_NO_EXCEPTION(beta2.addGroup(Group("Alpha4", 20, 20)));
    ASSERT_NO_EXCEPTION(beta.unite(beta2, "Beta3"));
    ostringstream os;
    ASSERT_TRUE(beta2.getSize() == 0);
    ASSERT_NO_EXCEPTION(os << beta);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Beta3\n"
        "Clan's groups:\n"
        "Alpha4\n"
        "Alpha3\n"
        "Alpha1\n"
        "Alpha2\n"));
    Clan gamma1("Gamma 1");
    Clan gamma2("Gamma 2");
    ASSERT_NO_EXCEPTION(gamma1.makeFriend(gamma2));
    ASSERT_TRUE(gamma1.isFriend(gamma2));
    return true;
}

std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("Beta", Clan("Beta")));
    clan_map.insert(std::pair<std::string, Clan>("Gamma", Clan("Gamma")));
    clan_map.at("Beta").addGroup(Group("Alpha1", 10, 10));
    clan_map.at("Beta").addGroup(Group("Alpha2","", 10, 10, 40, 0, 70));
    clan_map.at("Gamma").addGroup(Group("Lambda1", 10, 10));
    clan_map.at("Gamma").addGroup(Group("Lambda2", 5, 5));
    clan_map.at("Gamma").addGroup(Group("Lambda3", 100, 100));
    return clan_map;
}

bool examplePlain(){
    AreaPtr tel_aviv(new Plain("Tel-Aviv"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Alpha1", "Beta", clan_map));
    // divide
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Alpha1_2"));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Lambda1", "Gamma", clan_map));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Lambda2", "Gamma", clan_map));
    //unite with lambda1
    
    ASSERT_FALSE(tel_aviv->getGroupsNames().contains("Lambda2"));
    
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
//------------------------------------------------------------------------------
/**
 * World tests
 */
//------------------------------------------------------------------------------
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

bool testWorldAddGroup(){
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
            "Clan's groups:\n"
            "stark_2\n"
            "stark\n"));
    world.printClan(os, "maesters");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: maesters\n"
            "Clan's groups:\n"
            "martell\n"));
    return true;
}

int main(){
    //Clan tests
    RUN_TEST(testCtors);
    RUN_TEST(testAddGroup);
    RUN_TEST(testGetGroup);
    RUN_TEST(testDoesContain);
    RUN_TEST(testGetSize);
    RUN_TEST(testUnite);
    RUN_TEST(testFriends);
    RUN_TEST(testPrint);
    //Area tests
    RUN_TEST(exampleClan);
    RUN_TEST(examplePlain);
    RUN_TEST(exampleMountain);
    RUN_TEST(exampleRiver);
    //World tests
    RUN_TEST(testAddClan);
    RUN_TEST(testAddArea);
    RUN_TEST(testWorldAddGroup);
    RUN_TEST(testAddGroup);
    RUN_TEST(testMakeReachable);
    RUN_TEST(testMoveGroup);
    RUN_TEST(testMakeFriends);
    RUN_TEST(testUniteClans);
    RUN_TEST(testPrintGroup);
    RUN_TEST(testPrintClan);
    return 0;
}
