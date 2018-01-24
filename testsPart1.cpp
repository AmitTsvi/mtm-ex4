#include "testMacros.h"
#include "Group.h"
#include "exceptions.h"

using namespace mtm;

bool exampleGroup(){

    std::ostringstream os;
    //--------------------------------------------------------------------------
    /**
     * Group contructor tests
     */
    //--------------------------------------------------------------------------
    //Group constructor invalid arguments
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 0, 0, 10, 10 ,10),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 0, -1, 10, 10 ,10),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", -1, 0, 10, 10 ,10),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 1, 0, -1, 10 ,-1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 0, 0, 10, -1 ,0),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 0, 0, 10, 10 ,0),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", "Hogwarts", 0, 0, 10, 10 ,101),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", 0, 0), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", -1, 1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Gryffindor", 1, -1), GroupInvalidArgs);

    Group gryffindor("Gryffindor", 1, 2);
    ASSERT_TRUE(gryffindor.getName() == "Gryffindor");
    ASSERT_TRUE(gryffindor.getSize() == 3);
    ASSERT_TRUE(gryffindor.getClan() == "");

    os << gryffindor;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: \n"
            "Group's children: 1\n"
            "Group's adults: 2\n"
            "Group's tools: 8\n"
            "Group's food: 8\n"
            "Group's morale: 70\n"));

    //--------------------------------------------------------------------------
    /**
     * Change clan tests
     */
    //--------------------------------------------------------------------------
    //Change clan - to no empty clan - nothing should change
    gryffindor.changeClan("");
    os << gryffindor;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: \n"
            "Group's children: 1\n"
            "Group's adults: 2\n"
            "Group's tools: 8\n"
            "Group's food: 8\n"
            "Group's morale: 70\n"));

    //Change clan to existing clan - morale should increase by 10%
    gryffindor.changeClan("Hogwarts");
    os << gryffindor;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 1\n"
            "Group's adults: 2\n"
            "Group's tools: 8\n"
            "Group's food: 8\n"
            "Group's morale: 77\n"));

    //Change clan to the same clan - nothing should change
    gryffindor.changeClan("Hogwarts");
    os << gryffindor;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 1\n"
            "Group's adults: 2\n"
            "Group's tools: 8\n"
            "Group's food: 8\n"
            "Group's morale: 77\n"));

    //Change clan to different clan - morale should decrease by 10%
    gryffindor.changeClan("Koldovstoretz");
    os << gryffindor;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: Koldovstoretz\n"
            "Group's children: 1\n"
            "Group's adults: 2\n"
            "Group's tools: 8\n"
            "Group's food: 8\n"
            "Group's morale: 69\n"));

    Group slytherin("Slytherin", "", 10, 10 , 10, 10, 100);

    //Change clan to first clan - morale should stay 100 (can't be more then 100)
    slytherin.changeClan("Hogwarts");
    os << slytherin;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Slytherin\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 10\n"
            "Group's food: 10\n"
            "Group's morale: 100\n"));

    //--------------------------------------------------------------------------
    /**
     * Operator tests (==, !=, >, <, =>, <=)
     */
    //--------------------------------------------------------------------------
    Group alpha("Alpha", "Beta", 10, 10, 40, 50, 80);
    Group gamma("Gamma", "Lambda" ,5 , 5, 20, 10 , 90);

    ASSERT_FALSE(alpha < gamma);
    ASSERT_FALSE(alpha <= gamma);
    ASSERT_TRUE(alpha >= gamma);
    ASSERT_TRUE(alpha != gamma);
    ASSERT_TRUE(alpha > gamma);
    ASSERT_FALSE(alpha == gamma);

    Group alpha1("Alpha", "Beta", 10, 10, 40, 50, 80);

    //Same power and same name - should be equal
    ASSERT_TRUE(alpha1 == alpha);

    Group blpha("Blpha", "Beta", 10, 10, 40, 50, 80);

    //Same power different name
    ASSERT_TRUE(blpha > alpha);

    //--------------------------------------------------------------------------
    ASSERT_NO_EXCEPTION(alpha.changeClan("Lambda")); //alpha morale changed to 72
    //--------------------------------------------------------------------------
    /**
     * Trade tests
     */
    //--------------------------------------------------------------------------
    ASSERT_TRUE(alpha.trade(gamma));

    os << alpha << gamma;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 10\n"
        "Group's adults: 10\n"
        "Group's tools: 45\n"
        "Group's food: 45\n"
        "Group's morale: 72\n"
        "Group's name: Gamma\n"
        "Group's clan: Lambda\n"
        "Group's children: 5\n"
        "Group's adults: 5\n"
        "Group's tools: 15\n"
        "Group's food: 15\n"
        "Group's morale: 90\n"));

    //gryffindor has the same number of tools and food
    ASSERT_FALSE(gryffindor.trade(slytherin));
    ASSERT_FALSE(slytherin.trade(gryffindor));

    //cant trade with itself
    ASSERT_EXCEPTION(gryffindor.trade(gryffindor), GroupCantTradeWithItself);

    //--------------------------------------------------------------------------
    /**
     * Unite tests
     */
    //--------------------------------------------------------------------------
    Group hufflepuff("Hufflepuff", "", 10, 10, 2, 4, 70);
    Group ravenclaw("Ravenclaw", "", 10, 10, 2, 4, 90);

    //cant unite because both aren't a part of a clan
    ASSERT_FALSE(hufflepuff.unite(ravenclaw,100));

    //cant unite with itself
    ASSERT_FALSE(hufflepuff.unite(hufflepuff, 100));

    hufflepuff.changeClan("Hogwarts");
    ravenclaw.changeClan("Koldovstoretz");

    //cant unite because aren't in the same clan
    ASSERT_FALSE(hufflepuff.unite(ravenclaw, 100));

    ravenclaw.changeClan("Hogwarts");

    //cant unite because maximum people in too small
    ASSERT_FALSE(hufflepuff.unite(ravenclaw, 39));

    //can unite - the new name will be ravenclaw because ravenclaw > hufflepuff
    ASSERT_TRUE(hufflepuff.unite(ravenclaw,40));

    os << hufflepuff << ravenclaw;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Ravenclaw\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 20\n"
            "Group's adults: 20\n"
            "Group's tools: 4\n"
            "Group's food: 8\n"
            "Group's morale: 83\n" //weighted mean
            "Group's name: \n"
            "Group's clan: \n"
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"));

    ASSERT_TRUE(alpha.unite(gamma, 40));
    os << alpha << gamma;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 15\n"
        "Group's adults: 15\n"
        "Group's tools: 60\n"
        "Group's food: 60\n"
        "Group's morale: 78\n"
        "Group's name: \n"
        "Group's clan: \n"
        "Group's children: 0\n"
        "Group's adults: 0\n"
        "Group's tools: 0\n"
        "Group's food: 0\n"
        "Group's morale: 0\n"));

    //--------------------------------------------------------------------------
    /**
     * Divide tests
     */
    //--------------------------------------------------------------------------

    Group moggles = slytherin.divide("Moggles");

    os << moggles << slytherin;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Moggles\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 5\n"
            "Group's adults: 5\n"
            "Group's tools: 5\n"
            "Group's food: 5\n"
            "Group's morale: 100\n"
            "Group's name: Slytherin\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 5\n"
            "Group's adults: 5\n"
            "Group's tools: 5\n"
            "Group's food: 5\n"
            "Group's morale: 100\n"));
    //--------------------------------------------------------------------------
    Group alpha2 = alpha.divide("Alpha 2");
    //--------------------------------------------------------------------------
    /**
     * Fight tests
     */
    //--------------------------------------------------------------------------
    ASSERT_TRUE(alpha.fight(alpha2) == WON);
    
    os << alpha << alpha2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 8\n"
        "Group's adults: 6\n"
        "Group's tools: 23\n"
        "Group's food: 37\n"
        "Group's morale: 94\n"
        "Group's name: Alpha 2\n"
        "Group's clan: Lambda\n"
        "Group's children: 4\n"
        "Group's adults: 4\n"
        "Group's tools: 15\n"
        "Group's food: 15\n"
        "Group's morale: 62\n"));

    ASSERT_TRUE(gryffindor.fight(slytherin) == LOST);

    os << gryffindor << slytherin;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Gryffindor\n"
            "Group's clan: Koldovstoretz\n"
            "Group's children: 0\n"
            "Group's adults: 1\n"
            "Group's tools: 4\n"
            "Group's food: 4\n"
            "Group's morale: 55\n"
            "Group's name: Slytherin\n"
            "Group's clan: Hogwarts\n"
            "Group's children: 5\n"
            "Group's adults: 4\n"
            "Group's tools: 4\n"
            "Group's food: 7\n"
            "Group's morale: 100\n"));

    //Group cant fight itself
    ASSERT_EXCEPTION(gryffindor.fight(gryffindor), GroupCantFightWithItself);

    //Group cant fight with an empty group
    ASSERT_EXCEPTION(alpha.fight(gamma), GroupCantFightEmptyGroup);

    //--------------------------------------------------------------------------
    return true;
}

int main(){
    RUN_TEST(exampleGroup);
    return 0;
}
