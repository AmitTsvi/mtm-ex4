#include "Mountain.h"
#include <stdexcept>
#include <algorithm>

explicit mtm::Mountain::Mountain(const std::string& name):Area(name){};

mtm::Mountain::~Mountain() = default;

void mtm::Mountain::groupArrive(const string& group_name, const string& clan,
                             map<string, Clan>& clan_map)
{
    try {
        mtm::Clan& arrived_clan = clan_map.at(clan);
        const mtm::GroupPointer& group = arrived_clan.getGroup(group_name);
        if (find(groups.begin(), groups.end(), group) == groups.end()){
            throw AreaGroupAlreadyIn();
        }
        if (!ruler){
            groups.push_back(group);
            ruler = group;

        } else if (ruler->getClan() == clan){
            if ()
        } else {

        }
        groups.push_back(group);
        return;
    } catch (const std::out_of_range&){
        throw AreaClanNotFoundInMap();
    } catch (ClanGroupNotFound&){
        throw AreaGroupNotInClan();
    }
}

virtual void groupLeave(const std::string& group_name)