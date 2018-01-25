#ifndef EX4_PLAIN_H
#define EX4_PLAIN_H

#include "Area.h"

namespace mtm{
    class Plain : public Area{

        string getFirstValidName(const string& base_name, map<string,
                Clan>& clan_map) const;

    public:
        /**
         * Constructor
         * @param name The name of the plain
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Plain(const std::string& name);

        /**
         * Disable copy constructor
         */
        Plain(const Area&) = delete;

        /**
         * Disable assignment operator
         */
        Plain &operator=(const Plain &) = delete;

        /**
         * Destructor
         */
        ~Plain() override;

        /**
        * Get a group into the plain:
         * if the group have less people than third of the clan's people it is
         * united with the strongest group which is in the same clan, together
         * they have less than third of the clan's people.
         * if the group have more than third of the clan's people it is divided
         * into and the new group created have the same name with an extension
         * _i when i>=2 and is the lowest, no group in the map have the same.
         * the default action is simply to add the group as it is to the plain.
        *
        * @param group_name The name of the group that get into the plain.
        * @param clan The name of the clan that the group belongs to.
        * @param clan_map The map of clans that contains the clan of the group
        * @throws AreaClanNotFoundInMap If there is no clan with the given
        * name in the map.
        * @throws AreaGroupNotInClan If there is no group with the given name
        * in the clan with the given name in the map.
        * @throws AreaGroupAlreadyIn If group with same name already in the
        *  plain.
        *
        * Assert that the map does contain the clan that the group belongs to.
        */
        void groupArrive(const string& group_name, const string& clan,
                                 map<string, Clan>& clan_map) override;

    };


} //namespace mtm


#endif //EX4_PLAIN_H
