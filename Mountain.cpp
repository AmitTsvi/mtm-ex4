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
            ruler = group;

        } else if (ruler->getClan() == clan){
            if (group > ruler){
                ruler = group;
            }
        } else {
            if (group->fight(*ruler) == WON){
                ruler = group;
            }
        }
        groups.push_back(group);
        return;
    } catch (const std::out_of_range&){
        throw AreaClanNotFoundInMap();
    } catch (ClanGroupNotFound&){
        throw AreaGroupNotInClan();
    }
}

virtual void mtm::Mountain::groupLeave(const std::string& group_name)
{
    std::vector::const_iterator it = find(groups.begin(), groups.end(),
                                          group_name);
    if (it == groups.end()){
        throw AreaGroupNotFound();
    }
    string group_clan = (*it)->getClan();
    std::sort(groups.begin(), groups.end());
    if (ruler->getName() == group_name){
        if (groups.size() == 1){
            ruler.reset();
        } else {
            for (int i = groups.size()-1; i >= 0; i++){
                if (groups[i]->getClan() == group_clan){
                    ruler = groups[i];
                    groups.erase(it);
                    return;
                }
            }
            ruler = groups[0];
        }
    }
    groups.erase(it);
}