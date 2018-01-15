#include "testMacros.h"
#include "MtmSet.h"
#include "exceptions.h"

using namespace mtm;

bool isEven(int n){
    return !(n%2);
}

bool setEmptyCtorTest(){
    MtmSet<int> set;
    ASSERT_TRUE(set.begin() == set.end());
    return true;
}

bool setCopyCtorTest(){
    MtmSet<int> set;
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_NO_EXCEPTION(set.insert(0));
    ASSERT_NO_EXCEPTION(set.insert(4));
    ASSERT_NO_EXCEPTION(set.insert(8));
    MtmSet<int> set1(set);
    MtmSet<int>::const_iterator org_it = set.begin();
    MtmSet<int>::const_iterator new_it = set1.begin();
    ASSERT_TRUE(*(new_it++) == *(org_it++));
    ASSERT_TRUE(*(new_it++) == *(org_it++));
    ASSERT_TRUE(*(new_it++) == *(org_it++));
    ASSERT_TRUE(*(new_it++) == *(org_it++));
    ASSERT_TRUE(new_it == set1.end());
    ASSERT_TRUE(org_it == set.end());

    MtmSet<int> set2;
    MtmSet<int> set3(set2);
    ASSERT_TRUE(set3.begin() == set3.end());

    return true;
}

bool setInsertTest(){
    MtmSet<int> set;
    MtmSet<int>::iterator inset1_it = set.insert(3);
    ASSERT_TRUE(inset1_it == set.begin());
    ASSERT_TRUE(*set.begin() == 3);

    MtmSet<int>::iterator insert2_it = set.insert(3);
    ASSERT_TRUE(insert2_it == inset1_it);
    MtmSet<int>::const_iterator it = set.begin();
    ASSERT_TRUE(++it == set.end());

    MtmSet<int>::iterator second_element = set.insert(2);
    ASSERT_TRUE(set.size() == 2);
    ASSERT_TRUE(*second_element == 2);
    ASSERT_TRUE(set.contains(2));

    return true;
}

bool setEraseByElementTest(){
        return true;
}

bool exampleSet(){
    MtmSet<int> set;
    ASSERT_NO_EXCEPTION(set.insert(1));
    ASSERT_NO_EXCEPTION(set.insert(2));
    MtmSet<int> set2(set);
    ASSERT_TRUE(set.contains(1));
    ASSERT_NO_EXCEPTION(set.erase(1));
    ASSERT_FALSE(set.contains(1));
    ASSERT_TRUE(set.size() == 1);
    ASSERT_FALSE(set.empty());
    MtmSet<int>::iterator it = set.begin();
    ASSERT_TRUE(*(it++) == 2);
    ASSERT_TRUE(it == set.end());
    ASSERT_TRUE(set.begin() == set.find(2));
    ASSERT_TRUE(set2.isSuperSetOf(set));
    ASSERT_TRUE(set2 != set);
    ASSERT_NO_EXCEPTION(set.unite(set2));
    ASSERT_TRUE(set == set2);
    MtmSet<int> set3;
    ASSERT_NO_EXCEPTION(set.intersect(set3));
    ASSERT_TRUE(set.empty());
    ASSERT_NO_EXCEPTION(set2.clear());
    ASSERT_TRUE(set2.empty());
    ASSERT_NO_EXCEPTION(set.insert(1));
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_NO_EXCEPTION(set.insert(3));
    ASSERT_TRUE(set.getSubSet(isEven).size() == 1);
    return true;
}

int main(){
    RUN_TEST(exampleSet);
    RUN_TEST(setEmptyCtorTest);
    RUN_TEST(setCopyCtorTest);
    RUN_TEST(setInsertTest);
    RUN_TEST(setEraseByElementTest);
    return 0;
}
