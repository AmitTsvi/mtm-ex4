#ifndef EX4_RIVER_H
#define EX4_RIVER_H

#include "Area.h"

namespace mtm{
    class River : public Area{

    public:
        /**
         * Constructor
         * @param name The name of the river
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit River(const std::string& name);

        /**
         * Disable copy constructor
         */
        River(const Area&) = delete;

        /**
         * Disable assignment operator
         */
        River &operator=(const River &) = delete;

        /**
         * Destructor
         */
        ~River() override;

        /**
        * Get a group into the river:
         * before entering the river the group trades with the strongest group
         * which is from it's clan or a friend clan of it.
        * @param group_name The name of the group that get into the river.
        * @param clan The name of the clan that the group belongs to.
        * @param clan_map The map of clans that contains the clan of the group
        * @throws AreaClanNotFoundInMap If there is no clan with the given
        * name in the map.
        * @throws AreaGroupNotInClan If there is no group with the given name
        * in the clan with the given name in the map.
        * @throws AreaGroupAlreadyIn If group with same name already in the
        *  river.
        *
        * Assert that the map does contain the clan that the group belongs to.
        */
        void groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) override;

    };


} //namespace mtm


#endif //EX4_RIVER_H
