#include "../testMacros.h"
#include "../MtmSet.h"
#include "../exceptions.h"

using namespace mtm;

bool isEven(int n){
    return !(n%2);
}

bool iteratorCtorDtorTest(){
    MtmSet<int> set;
    set.insert(2);
    MtmSet<int>::iterator empty_it;
    MtmSet<int>::iterator it(set.begin());
    ASSERT_TRUE(*it == 2);

    const MtmSet<int> const_set = set;
    MtmSet<int>::const_iterator empty_cit;
    MtmSet<int>::const_iterator cit(set.begin());
    ASSERT_TRUE(*it == 2);
    MtmSet<int>::const_iterator cit2(it);
    ASSERT_TRUE(*cit == 2);
    return true;
}

bool iteratorAssignmentOperatorTest(){
    MtmSet<int> set;
    set.insert(2);
    MtmSet<int>::iterator it = set.begin();
    ASSERT_TRUE(*it == 2);

    const MtmSet<int> const_set = set;
    MtmSet<int>::const_iterator cit = set.begin();
    ASSERT_TRUE(*cit == 2);

    return true;
}

bool iteratorDereferenceTest(){
    MtmSet<int> set;
    set.insert(2);
    ASSERT_TRUE(*set.begin() == 2);

    const MtmSet<int> const_set = set;
    ASSERT_TRUE(*const_set.begin() == 2);

    class Dog{
    public:
        int id;
        int weight;

        Dog(int a, int b): id(a), weight(b){}

        bool operator==(const Dog& rhs) const{
            return (id == rhs.id && weight == rhs.weight);
        }

        Dog(const Dog& rhs) = default;

    };

    MtmSet<Dog> dset;
    Dog aaa(2,7);
    dset.insert(aaa);
    ASSERT_TRUE(dset.begin()->id == 2);

    const MtmSet<Dog> const_dset = dset;
    ASSERT_TRUE(const_dset.begin()->weight == 7);

    return true;
}

bool iteratorOperatorPlusTest(){
    MtmSet<int> set;
    set.insert(2);
    set.insert(0);
    set.insert(4);
    set.insert(8);

    MtmSet<int>::iterator it(set.begin());
    ASSERT_TRUE(*it == 2);
    ASSERT_TRUE(*(it++) == 2);
    ASSERT_TRUE(*it == 0);
    ASSERT_TRUE(*(++it) == 4);

    const MtmSet<int> const_set = set;
    MtmSet<int>::const_iterator cit(const_set.begin());
    ASSERT_TRUE(*cit == 2);
    ASSERT_TRUE(*(cit++) == 2);
    ASSERT_TRUE(*cit == 0);
    ASSERT_TRUE(*(++cit) == 4);

    return true;
}

bool iteratorCompareTest(){
    MtmSet<int> set;
    set.insert(2);
    set.insert(0);
    set.insert(4);
    set.insert(8);

    MtmSet<int> set2;
    set2.insert(2);
    set2.insert(0);
    set2.insert(4);
    set2.insert(8);

    MtmSet<int>::iterator set1_it(set.begin());
    MtmSet<int>::iterator set1_it2(set.begin());
    MtmSet<int>::iterator set2_it(set2.begin());

    set1_it++;
    set1_it2++;
    ASSERT_TRUE(set1_it == set1_it2);
    ASSERT_FALSE(set1_it != set1_it2);
    set2_it++;
    ASSERT_FALSE(set1_it == set2_it);
    ASSERT_TRUE(set1_it != set2_it);

    const MtmSet<int> cset = set;
    const MtmSet<int> cset2 = set2;

    MtmSet<int>::iterator cset1_it(set.begin());
    MtmSet<int>::iterator cset1_it2(set.begin());
    MtmSet<int>::iterator cset2_it(set2.begin());

    cset1_it++;
    cset1_it2++;
    ASSERT_TRUE(cset1_it == cset1_it2);
    ASSERT_FALSE(cset1_it != cset1_it2);
    cset2_it++;
    ASSERT_FALSE(cset1_it == cset2_it);
    ASSERT_TRUE(cset1_it != cset2_it);

    return true;
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
    MtmSet<int> set;
    ASSERT_NO_EXCEPTION(set.insert(5));
    ASSERT_NO_EXCEPTION(set.erase(5));
    ASSERT_TRUE(set.begin() == set.end());
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_NO_EXCEPTION(set.insert(7));
    ASSERT_NO_EXCEPTION(set.insert(3));
    ASSERT_TRUE(set.contains(2));
    ASSERT_NO_EXCEPTION(set.erase(2));
    ASSERT_FALSE(set.contains(2));
    ASSERT_TRUE(set.size() == 2);
    ASSERT_TRUE(*(set.begin()) == 7);
    ASSERT_NO_EXCEPTION(set.insert(6));
    ASSERT_NO_EXCEPTION(set.erase(3));
    ASSERT_TRUE(set.size() == 2);
    MtmSet<int>::iterator it = set.find(6);
    ASSERT_NO_EXCEPTION(set.erase(22));
    ASSERT_TRUE(*it == 6);
    return true;
}

bool setEraseByItTest(){
    MtmSet<int> set;
    MtmSet<int>::iterator it1 = set.insert(5);
    ASSERT_NO_EXCEPTION(set.erase(it1));
    ASSERT_TRUE(set.begin() == set.end());
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_NO_EXCEPTION(set.insert(7));
    ASSERT_NO_EXCEPTION(set.insert(3));
    it1 = set.find(2);
    ASSERT_NO_EXCEPTION(set.erase(it1));
    ASSERT_FALSE(set.contains(2));
    ASSERT_TRUE(set.size() == 2);
    ASSERT_TRUE(*(set.begin()) == 7);
    ASSERT_NO_EXCEPTION(set.insert(6));
    ASSERT_NO_EXCEPTION(set.erase(3));
    ASSERT_TRUE(set.size() == 2);
    return true;
}

bool setSizeTest(){
    MtmSet<int> set;
    set.insert(7);
    set.insert(8);
    set.insert(123);
    ASSERT_TRUE(set.size() == 3);
    set.erase(7);
    ASSERT_TRUE(set.size() == 2);
    set.insert(123);
    ASSERT_TRUE(set.size() == 2);
    return true;
}

bool setEmptyTest(){
    MtmSet<int> set;
    ASSERT_TRUE(set.empty());
    set.insert(3);
    ASSERT_FALSE(set.empty());
    return true;
}

bool setClearTest(){
    MtmSet<int> set;
    set.insert(7);
    ASSERT_NO_EXCEPTION(set.clear());
    ASSERT_TRUE(set.begin() == set.end());
    set.insert(9);
    set.insert(2);
    set.insert(4);
    ASSERT_NO_EXCEPTION(set.clear());
    ASSERT_TRUE(set.begin() == set.end());
    return true;
}

bool setBeginTest(){
    MtmSet<int> set;
    const MtmSet<int>& cset = set;
    ASSERT_TRUE(set.begin() == set.end());
    ASSERT_TRUE(cset.begin() == cset.end());
    set.insert(3);
    ASSERT_TRUE(*set.begin() == 3);
    ASSERT_TRUE(*cset.begin() == 3);
    set.insert(7);
    ASSERT_TRUE(*set.begin() == 3);
    ASSERT_TRUE(*cset.begin() == 3);
    return true;
}

bool setFindTest(){
    MtmSet<int> set;
    const MtmSet<int>& cset = set;
    set.insert(3);
    MtmSet<int>::iterator it = set.find(3);
    MtmSet<int>::const_iterator cit = cset.find(3);
    ASSERT_TRUE(*it == 3);
    ASSERT_TRUE(*cit == 3);
    ASSERT_TRUE(++it == set.end());
    ASSERT_TRUE(++cit == set.end());
    set.insert(1);
    set.insert(5);
    set.insert(7);
    it = set.find(5);
    cit = set.find(5);
    ASSERT_TRUE(*it == 5);
    ASSERT_TRUE(*cit == 5);
    ASSERT_TRUE(*(++it) == 7);
    ASSERT_TRUE(*(++cit) == 7);
    return true;
}

bool setContainsTest(){
    MtmSet<int> set;
    set.insert(3);
    set.insert(4);
    set.insert(7);
    ASSERT_TRUE(set.contains(3));
    ASSERT_TRUE(set.contains(4));
    ASSERT_TRUE(set.contains(7));
    ASSERT_FALSE(set.contains(2));
    return true;
}

bool setIsSuperSetOfTest(){
    MtmSet<int> setA;
    MtmSet<int> setB;
    ASSERT_TRUE(setA.isSuperSetOf(setB));
    setA.insert(1);
    setB.insert(1);
    ASSERT_TRUE(setA.isSuperSetOf(setB));
    setA.insert(2);
    ASSERT_TRUE(setA.isSuperSetOf(setB));
    setB.insert(3);
    ASSERT_FALSE(setA.isSuperSetOf(setB));
    return true;
}

bool setEqualOperatorTest(){
    MtmSet<int> setA;
    MtmSet<int> setB;
    ASSERT_TRUE(setA == setB);
    setA.insert(1);
    setB.insert(1);
    ASSERT_TRUE(setA == setB);
    setA.insert(2);
    ASSERT_FALSE(setA == setB);
    setB.insert(3);
    ASSERT_FALSE(setA == setB);
    setA.insert(3);
    setB.insert(2);
    ASSERT_TRUE(setA == setB)
    return true;
}

bool setUniteTest(){
    MtmSet<int> set1;
    MtmSet<int> set2;
    set2.insert(2);
    set1.unite(set2);
    ASSERT_TRUE(*(set1.begin()) == 2);
    set1.insert(3);
    set2.insert(4);
    set1.unite(set2);
    ASSERT_TRUE(set1.contains(3));
    ASSERT_TRUE(set2.contains(4));
    ASSERT_TRUE(set1.size() == 3);
    MtmSet<int> set3;
    set1.unite(set3);
    ASSERT_TRUE(set1.size() == 3);
    return true;
}

bool setUniteTestConst(){
    const MtmSet<int> eset1;
    const MtmSet<int> eset2;
    MtmSet<int> set3 = eset1.unite(eset2);
    ASSERT_TRUE(set3.empty());
    MtmSet<int> set1;
    MtmSet<int> set2;
    set1.insert(1);
    set1.insert(3);
    set2.insert(2);
    set2.insert(4);
    set2.insert(3);
    const MtmSet<int> cset1 = set1;
    const MtmSet<int> cset2 = set2;
    MtmSet<int> set6 = cset1.unite(cset2);
    ASSERT_TRUE(set6.size() == 4);

    const MtmSet<int> cset4;
    MtmSet<int> set5 = cset4.unite(cset1);
    ASSERT_TRUE(set5 == set1);
    return true;
}

bool setIntersectTest(){
    MtmSet<int> set1;
    MtmSet<int> set2;
    set1.intersect(set2);
    ASSERT_TRUE(set1.empty());
    set1.insert(1);
    set1.intersect(set2);
    ASSERT_TRUE(set1.empty());
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(3);
    set2.insert(7);
    set2.insert(1);
    set1.intersect(set2);
    ASSERT_TRUE(set1.size() == 2);
    ASSERT_TRUE(set1.contains(1));
    ASSERT_TRUE(set1.contains(3));
    return true;
}

bool setIntersectTestConst(){
    const MtmSet<int> eset1;
    const MtmSet<int> eset2;
    MtmSet<int> set3 = eset1.intersect(eset2);
    ASSERT_TRUE(set3.empty());
    MtmSet<int> set1;
    MtmSet<int> set2;
    set1.insert(1);
    set1.insert(3);
    set2.insert(2);
    set2.insert(4);
    set2.insert(3);
    const MtmSet<int> cset1 = set1;
    const MtmSet<int> cset2 = set2;
    MtmSet<int> set6 = cset1.intersect(cset2);
    ASSERT_TRUE(set6.size() == 1);
    ASSERT_TRUE(set6.contains(3));

    const MtmSet<int> cset4;
    MtmSet<int> set5 = cset4.intersect(cset1);
    ASSERT_TRUE(set5.empty());
    return true;
}

bool setGetSubSetTest(){
    MtmSet<int> set;
    set.getSubSet(isEven);
    ASSERT_TRUE(set.empty());
    set.insert(1);
    set.insert(3);
    set.getSubSet(isEven);
    ASSERT_TRUE(set.empty());
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.getSubSet(isEven);
    ASSERT_TRUE(set.size() == 2);
    ASSERT_TRUE(set.contains(2));
    ASSERT_TRUE(set.contains(4));
    return true;
}

bool setGetSubSetTestConst(){
    const MtmSet<int> eset1;
    MtmSet<int> eset2 = eset1.getSubSet(isEven);
    ASSERT_TRUE(eset2.empty());

    MtmSet<int> set1;
    set1.insert(1);
    set1.insert(3);
    set1.insert(2);
    set1.insert(4);
    const MtmSet<int> cset1 = set1;
    MtmSet<int> set6 = cset1.getSubSet(isEven);
    ASSERT_TRUE(set6.size() == 2);
    ASSERT_TRUE(set6.contains(2));
    ASSERT_TRUE(set6.contains(4));
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
    RUN_TEST(setEraseByItTest);
    RUN_TEST(setSizeTest);
    RUN_TEST(setEmptyTest);
    RUN_TEST(setClearTest);
    RUN_TEST(setBeginTest);
    RUN_TEST(setFindTest);
    RUN_TEST(setContainsTest);
    RUN_TEST(setIsSuperSetOfTest);
    RUN_TEST(setEqualOperatorTest);
    RUN_TEST(setUniteTest);
    RUN_TEST(setUniteTestConst);
    RUN_TEST(setIntersectTest);
    RUN_TEST(setIntersectTestConst)
    RUN_TEST(setGetSubSetTest);
    RUN_TEST(iteratorCtorDtorTest);
    RUN_TEST(iteratorAssignmentOperatorTest);
    RUN_TEST(iteratorDereferenceTest);
    RUN_TEST(iteratorOperatorPlusTest);
    RUN_TEST(iteratorCompareTest);
    return 0;
}
