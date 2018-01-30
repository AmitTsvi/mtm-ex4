#include <vector>
#include <algorithm>
#include "MtmSet.h"
#include "Clan.h"

namespace mtm{

    const int empty = 0;

    Clan::Clan(const std::string& name){
        if (name.empty()) {
            throw ClanEmptyName();
        }
        clan_name = name;
        MtmSet<GroupPointer> clan_groups;
        MtmSet<std::string> clan_friends;
    }

    void Clan::addGroup(const Group& group){
        if (group.getSize() == empty) {
            throw ClanGroupIsEmpty();
        }
        if (doesContain(group.getName())) {
            throw ClanGroupNameAlreadyTaken();
        }
        //Change morale in group
        GroupPointer group_copy(new Group(group)); //to test
        (*group_copy).changeClan(clan_name);
        clan_groups.insert(group_copy);
    }

    const GroupPointer& Clan::getGroup(const std::string& group_name) const{
        for (MtmSet<GroupPointer>::const_iterator it = clan_groups.begin();
                it != clan_groups.end(); ++it) {
            if ((*it)->getName() == group_name) {
                return *it;
            }
        }
        throw ClanGroupNotFound();
    }

    bool Clan::doesContain(const std::string& group_name) const{
        for (MtmSet<GroupPointer>::const_iterator it = clan_groups.begin();
             it != clan_groups.end(); ++it) {
            if ((*it)->getName() == group_name) {
                return true;
            }
        }
        return false;
    }

    int Clan::getSize() const{
        int size = empty;
        for (MtmSet<GroupPointer>::const_iterator it = clan_groups.begin();
             it != clan_groups.end(); ++it) {
            size += (*it)->getSize();
        }
        return size;
    }

    Clan& Clan::unite(Clan& other, const std::string& new_name){
        if (new_name.empty()) {
            throw ClanEmptyName();
        }
        if (this == &other) {
            throw ClanCantUnite();
        }
        if (isSameGroupsInTwoClans(*this, other)) {
            throw ClanCantUnite();
        }
        //This clan name is same as the new clan name - change only others clan
        if (clan_name == new_name) {
            changeClanNameInGroups(other, new_name);
        }
        //other clan name is same as the new clan name - change only this clan
        if (other.clan_name == new_name) {
            changeClanNameInGroups(*this, new_name);
        } else {
            //both this and other clans has a different name from the new name
            changeClanNameInGroups(other, new_name);
            changeClanNameInGroups(*this, new_name);
        }
        clan_name = new_name;
        //Loop through the other clans groups and add each group
        //to the this clan groups
        for (MtmSet<GroupPointer>::const_iterator it =
                (other.clan_groups).begin();
             it != (other.clan_groups).end(); ++it) {
            clan_groups.insert(*it);
        }
        //remove from the groups of the other clan
        (other.clan_groups).clear();
        //Add friends of the other clan to this clan
        for (MtmSet<std::string>::const_iterator it =
                (other.clan_friends).begin();
             it != (other.clan_friends).end(); ++it) {
            clan_friends.insert(*it);
        }
        return *this;
    }

    void Clan::makeFriend(Clan& other){
        //Add the other clan to the this friends
        addFriend(*this, other.clan_name);

        //Add the this clan to the other friends
        addFriend(other, clan_name);
    }

    bool Clan::isFriend(const Clan& other) const{
        if (this == &other) {
            return true;
        }
      return (clan_friends.contains(other.clan_name));
    }

    bool compareToPrint(const GroupPointer& lgroup, const GroupPointer& rgroup){
        return ((*lgroup) > (*rgroup));
    }

    std::ostream& operator<<(std::ostream& os, const Clan& clan){
        using std::endl;
        using std::ostream;
        using std::vector;
        vector<GroupPointer> group_vector;
        for (MtmSet<GroupPointer>::const_iterator it =
                (clan.clan_groups).begin();
             it != (clan.clan_groups).end(); ++it) {
            group_vector.push_back(*it);
        }
        //sort from weakest to strongest
        std::sort(group_vector.begin(), group_vector.end(), compareToPrint);
        //Print details
        os << "Clan's name: " << clan.clan_name << endl;
        os << "Clan's groups:" << endl;
        for (vector<GroupPointer>::iterator it = group_vector.begin();
                it != group_vector.end(); ++it) {
            os << (*it)->getName() << endl;
        }
        return os;
    }
} //namespace mtm
