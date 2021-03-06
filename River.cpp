#include "Area.h"
#include "River.h"
#include <stdexcept>
#include <algorithm>

using std::vector;

mtm::River::River(const std::string& name):Area(name){}

mtm::River::~River() = default;

void mtm::River::groupArrive(const string& group_name, const string& clan,
                             map<string, Clan>& clan_map)
{
    try {
        mtm::Clan& arrived_clan = clan_map.at(clan);
        const mtm::GroupPointer& group = arrived_clan.getGroup(group_name);
        if (find(groups.begin(), groups.end(), group) != groups.end()){
            throw AreaGroupAlreadyIn();
        }
        this->sortStrongerToWeaker();
        bool trade_result = false;
        for (vector<GroupPointer>::size_type i = 0;
             i < groups.size() && !trade_result; i++){
            mtm::Clan& tmp_clan = clan_map.at(groups[i]->getClan());
            if(groups[i]->getClan() == clan || arrived_clan.isFriend(tmp_clan)){
                trade_result = group->trade(*groups[i]);
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