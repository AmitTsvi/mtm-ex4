#include "World.h"
#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "MtmSet.h"
#include "stdexcept"
#include <iostream>
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include "cassert"

namespace mtm{

    const int empty = 0;
    typedef map<string, string>::iterator GroupAreaMapIterator; //to change!!!!!!
    typedef map<string, AreaPointer>::iterator AreaMapIterator;
    typedef map<string, Clan>::iterator ClanMapIterator;



    void World::addClan(const string& new_clan){
        if (new_clan.empty()) {
            throw WorldInvalidArgument();
        }
       if(clan_map.find(new_clan) != clan_map.end()) {
           throw WorldClanNameIsTaken();
       }
        clan_map.insert(std::pair<string, Clan>(new_clan, Clan(new_clan)));
    }

    void World::addArea(const string& area_name, AreaType type){
        if (area_name.empty()) {
            throw WorldInvalidArgument();
        }
        AreaMapIterator area_it = area_map.find(area_name);
        if (area_it != area_map.end()) {
            throw WorldAreaNameIsTaken();
        }
        if (type == PLAIN) {
            AreaPointer plain_ptr(new Plain(area_name));
            area_map.insert
                    (std::pair<string, AreaPointer>(area_name, plain_ptr));
        }
        else if (type == MOUNTAIN) {
            AreaPointer mountain_ptr(new Mountain(area_name));
            area_map.insert(
                    std::pair<string, AreaPointer>(area_name, mountain_ptr));
        }
        else if (type == RIVER) {
            AreaPointer river_ptr(new River(area_name));
            area_map.insert(
                    std::pair<string, AreaPointer>(area_name, river_ptr));
        }
    }

    void World::addGroup(const string& group_name, const string& clan_name, int
    num_children, int num_adults, const string& area_name){
        //Checking possible errors in order
        if (group_name.empty()) {
            throw WorldInvalidArgument();
        }
        if (num_children < empty || num_adults < empty) {
            throw WorldInvalidArgument();
        }
        if (num_children == empty && num_adults == empty) {
            throw WorldInvalidArgument();
        }
        GroupAreaMapIterator group_it = group_area_map.find(group_name);
        if (group_it != group_area_map.end()) {
            throw WorldGroupNameIsTaken();
        }
        try {
            clan_map.at(clan_name);
        } catch (std::out_of_range& e) {
            throw WorldClanNotFound();
        }
        try {
            area_map.at(area_name);
        } catch (std::out_of_range& e) {
            throw WorldAreaNotFound();
        }
        Group group_to_add(group_name, num_children, num_adults);
        (clan_map.at(clan_name)).addGroup(group_to_add);
        (area_map.at(area_name))->groupArrive(group_name, clan_name, clan_map);
        group_area_map.insert(
                std::pair<string, string>(group_name, area_name));
    }

    void World::makeReachable(const string& from, const string& to){
        try {
            area_map.at(to);
            (area_map.at(from))->addReachableArea(to);
        } catch (std::out_of_range& e) {
            throw WorldAreaNotFound();
        }
    }

    void World::moveGroup(const string& group_name, const string& destination){
        try {
            group_area_map.at(group_name);
        } catch (std::out_of_range& e) {
            throw WorldGroupNotFound();
        }
        try {
            area_map.at(destination);
        } catch (std::out_of_range& e) {
            throw WorldAreaNotFound();
        }
        string origin = (group_area_map.find(group_name))->second;
        if (origin == destination) {
            throw WorldGroupAlreadyInArea();
        }
         if (!(area_map.find(origin)->second)->isReachable(destination)) {
            throw WorldAreaNotReachable();
        }
        //Find group's clan
        string clan = "";
        for (ClanMapIterator it = clan_map.begin(); it != clan_map.end(); ++it) {
            if((it->second).doesContain(group_name)) {
                clan = it->first;
                break;
            }
        }
        assert(!(clan.empty()));
        //Group arrive to destination
        (area_map.find(destination)->second)->groupArrive(group_name, clan, clan_map);
        //Group leave original location
        (area_map.find(origin)->second)->groupLeave(group_name);
        //Change group placement in group area map
        group_area_map.at(group_name) = destination;
    }

    void World::makeFriends(const string& clan1, const string& clan2){
        try {
            clan_map.at(clan1);
            (clan_map.at(clan2)).makeFriend(clan_map.find(clan1)->second);
        } catch (std::out_of_range& e) {
            throw WorldClanNotFound();
        }
    }

    void World::uniteClans(const string& clan1, const string& clan2, const
    string& new_name){
        if (new_name.empty()) {
            throw WorldInvalidArgument();
        }
        if (clan_map.find(new_name) != clan_map.end()) {
            throw WorldClanNameIsTaken();
        }
        try {
            Clan clan1_to_unite = clan_map.at(clan1);
            Clan clan2_to_unite = clan_map.at(clan2);


            Clan united_clan = clan1_to_unite.unite(clan2_to_unite, new_name);
            clan_map.insert(std::pair<string, Clan>(new_name, Clan(united_clan)));
            clan_map.erase(clan1);
            clan_map.erase(clan2);
        } catch (std::out_of_range& e) {
            throw WorldClanNotFound();
        }
    }

    void World::printGroup(std::ostream& os, const string& group_name) const {
        bool flag = false;
        for (auto it = clan_map.begin(); it != clan_map.end(); ++it) {
            if ((it->second).doesContain(group_name)) {
                GroupPointer group_ptr = (it->second).getGroup(group_name);
                os << (*group_ptr);
                os << "Group's current area: "
                   << (group_area_map.find(group_name))->second
                   << std::endl;
                flag = true;
                break;
            }
        }
        if (!flag){
            throw WorldGroupNotFound();
        }
    }

    void World::printClan(std::ostream& os, const string& clan_name) const {
        try {
            os << clan_map.at(clan_name);
        } catch (std::out_of_range& e) {
            throw WorldClanNotFound();
        }
    }

} //namespace mtm