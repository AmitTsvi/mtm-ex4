#include "Area.h"
#include "exceptions.h"
#include <stdexcept>
#include <algorithm>

using std::vector;

mtm::Area::Area() = default;

mtm::Area::Area(const std::string& name)
{
    if (name.empty()){
        throw AreaInvalidArguments();
    }
    area_name = name;
}

mtm:: Area::~Area() = default;

void mtm::Area::addReachableArea(const std::string& area_name)
{
    other_areas.insert(area_name);
}

bool mtm::Area::isReachable(const std::string& area_name) const
{
    if (this->area_name == area_name) return true;
    return other_areas.contains(area_name);
}

void mtm::Area::groupArrive(const string& group_name,
                                    const string& clan,
                                    map<string, Clan>& clan_map)
{
    try {
        const mtm::Clan& arrived_clan = clan_map.at(clan);
        const mtm::GroupPointer& group = arrived_clan.getGroup(group_name);
        if (find(groups.begin(), groups.end(), group) != groups.end()){
            throw AreaGroupAlreadyIn();
        }
        groups.push_back(group);
    } catch (const std::out_of_range&){
        throw AreaClanNotFoundInMap();
    } catch (ClanGroupNotFound&){
        throw AreaGroupNotInClan();
    }
}

void mtm::Area::groupLeave(const std::string& group_name)
{
    auto it = groups.begin();
    for (; it != groups.end(); it++){
        if ((*it)->getName() == group_name) break;
    }
    if (it == groups.end()){
        throw AreaGroupNotFound();
    }
    groups.erase(it);
}

mtm::MtmSet<std::string> mtm::Area::getGroupsNames() const
{
    mtm::MtmSet<std::string> set;
    for (vector<GroupPointer>::size_type i=0; i < groups.size(); i++){
        set.insert((groups[i])->getName());
    }
    return set;
}