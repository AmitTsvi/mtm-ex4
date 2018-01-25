#include "Plain.h"
#include <stdexcept>
#include <algorithm>

string mtm::Plain::getFirstValidName(const string& base_name, map<string,
        Clan>& clan_map) const
{
    int i=2;
    while (true){
        string new_name(base_name + "_" + std::to_string(i));
        bool legal = true;
        for (std::map<string, Clan>::const_iterator it = clan_map.begin();
             it != clan_map.end(); it++){
            if ((it->second).doesContain(new_name)){
                legal = false;
            }
        }
        if (legal){
            return new_name;
        }
        i++;
    }
}

mtm::Plain::Plain(const std::string& name):Area(name){}

mtm::Plain::~Plain() = default;

void mtm::Plain::groupArrive(const string& group_name, const string& clan,
                 map<string, Clan>& clan_map)
{
    try {
        mtm::Clan& arrived_clan = clan_map.at(clan);
        const mtm::GroupPointer& group = arrived_clan.getGroup(group_name);
        if (find(groups.begin(), groups.end(), group) != groups.end()){
            throw AreaGroupAlreadyIn();
        }
        if (3*group->getSize() <= arrived_clan.getSize()){
            std::sort(groups.begin(), groups.end());
            for (int i = groups.size()-1; i >= 0; i--){
                if (groups[i]->unite(*group, arrived_clan.getSize()/3)) return;
            }
        } else if (group->getSize() >= 10){
            string new_name = getFirstValidName(group_name, clan_map);
            Group new_group = group->divide(new_name);
            GroupPointer new_group_ptr(&new_group);
            arrived_clan.addGroup(new_group);
            groups.push_back(group);
            groups.push_back(new_group_ptr);
            return;
        }
        groups.push_back(group);
        return;
    } catch (const std::out_of_range&){
        throw AreaClanNotFoundInMap();
    } catch (ClanGroupNotFound&){
        throw AreaGroupNotInClan();
    }
}