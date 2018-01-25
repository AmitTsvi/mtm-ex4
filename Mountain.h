#ifndef EX4_MOUNTAIN_H
#define EX4_MOUNTAIN_H

#include "Area.h"

namespace mtm{
    class Mountain : public Area{

        GroupPointer ruler;

    public:
        /**
         * Constructor
         * @param name The name of the Mountain
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Mountain(const std::string& name);

        /**
         * Disable copy constructor
         */
        Mountain(const Area&) = delete;

        /**
         * Disable assignment operator
         */
        Mountain &operator=(const Mountain &) = delete;

        /**
         * Destructor
         */
        ~Mountain() override;

        /**
        * Get a group into the Mountain:
         * if there is no group on the mountain then it is the new ruler.
         * if the current ruler is from the same clan then if the new group
         * is stronger it becomes the new ruler.
         * if the current ruler is from another clan then the two groups fight
         * and the winner is the new ruler
        *
        * @param group_name The name of the group that get into the Mountain.
        * @param clan The name of the clan that the group belongs to.
        * @param clan_map The map of clans that contains the clan of the group
        * @throws AreaClanNotFoundInMap If there is no clan with the given
        * name in the map.
        * @throws AreaGroupNotInClan If there is no group with the given name
        * in the clan with the given name in the map.
        * @throws AreaGroupAlreadyIn If group with same name already in the
        *  Mountain.
        *
        * Assert that the map does contain the clan that the group belongs to.
        */
        void groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) override;

        /**
        * Get a group out of the area:
         * if the group is the ruler then the strongest group from it's clan
         * becomes the new ruler.
         * if there is no other group from the same clan then the strongest
         * group on the mountain becomes the new ruler.
        * @param group_name The name of the leaving group.
        * @throws AreaGroupNotFound If there is no group in the area with the
        *  same name;
        */
        void groupLeave(const std::string& group_name) override;

    };


} //namespace mtm


#endif //EX4_MOUNTAIN_H
