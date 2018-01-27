#include "Area.h"
#include "exceptions.h"
#include <stdexcept>
#include <algorithm>

using namespace mtm;
using std::vector;

bool compByPower(const GroupPointer& first, const GroupPointer& second)
{
    return ((*first) > (*second));
}

void Area::sortStrongerToWeaker()
{
    std::sort(groups.begin(), groups.end(), compByPower);
}

Area::Area(const std::string& name)
{
    if (name.empty()){
        throw AreaInvalidArguments();
    }
    area_name = name;
}

Area::~Area() = default;

void Area::addReachableArea(const std::string& area_name)
{
    other_areas.insert(area_name);
}

bool Area::isReachable(const std::string& area_name) const
{
    if (this->area_name == area_name) return true;
    return other_areas.contains(area_name);
}

void Area::groupArrive(const string& group_name,
                                    const string& clan,
                                    map<string, Clan>& clan_map)
{
    try {
        const Clan& arrived_clan = clan_map.at(clan);
        const GroupPointer& group = arrived_clan.getGroup(group_name);
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

void Area::groupLeave(const std::string& group_name)
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

MtmSet<std::string> Area::getGroupsNames() const
{
    MtmSet<std::string> set;
    for (vector<GroupPointer>::size_type i=0; i < groups.size(); i++){
        set.insert((groups[i])->getName());
    }
    return set;
}