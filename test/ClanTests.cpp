#include "../testMacros.h"
#include "../Group.h"
#include "../Clan.h"
#include "../exceptions.h"

using namespace mtm;
std::ostringstream os;

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

bool testPrint() {
    Group likud("Likud", 1, 29);
    Group habayit_hayehudi("Habayit Hayehudi", 0, 8);
    Group joint_list("Joint List", 0, 13);
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

int main(){
    RUN_TEST(testCtors);
    RUN_TEST(testAddGroup);
    RUN_TEST(testGetGroup);
    RUN_TEST(testDoesContain);
    RUN_TEST(testGetSize);
    RUN_TEST(testUnite);
    RUN_TEST(testFriends);
    RUN_TEST(testPrint);
    return 0;
}
