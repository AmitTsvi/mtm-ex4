#include "Group.h"
#include "exceptions.h"

namespace mtm {
    
    const int max_morale = 100;
    const int tools_factor = 4;
    const int adults_food_factor = 3;
    const int children_food_factor = 2;
    const int default_morale = 70;
    const double morale_inc = 1.1;
    const double morale_dec = 0.9;
    const int min_morale_to_unite = 70;
    const int trade_factor = 2;

    mtm::Group::Group(const std::string &name, const std::string &clan,
                      int children, int adults, int tools, int food,
                      int morale){
        if (children < empty || adults < empty || tools < empty ||
            food < empty) {
            throw GroupInvalidArgs();
        }
        if (children == empty && adults == empty) {
            throw GroupInvalidArgs();
        }
        if (morale < empty || morale > max_morale) {
            throw GroupInvalidArgs();
        }
        if (name.empty()) {
            throw GroupInvalidArgs();
        }
        this->name = name;
        this->clan = clan; //a clan can be empty - empty sting mean no clan
        this->children = children;
        this->adults = adults;
        this->tools = tools;
        this->food = food;
        this->morale = morale;
    }

    mtm::Group::Group(const std::string &name, int children, int adults){
        if (children < empty || adults < 0) {
            throw GroupInvalidArgs();
        }
        if (children == empty && adults == empty) {
            throw GroupInvalidArgs();
        }
        if (name.empty()) {
            throw GroupInvalidArgs();
        }
        this->name = name;
        this->clan = "";
        this->children = children;
        this->adults = adults;
        this->tools = tools_factor * adults;
        this->food =
                adults_food_factor * adults + children_food_factor * children;
        this->morale = default_morale;
    }

    const std::string &mtm::Group::getName() const{
        return this->name;
    }

    int mtm::Group::getSize() const {
        return (children + adults);
    }

    const std::string &mtm::Group::getClan() const {
        return this->clan;
    }

    void mtm::Group::changeClan(const std::string &clan){
        //If the new clan is the same as the old one (or empty as before)
        if (this->clan == clan) {
            return;
        }
        //If the the group wasn't part of a clan and the new clan is non empty
        if ((this->clan).empty()) {
            this->clan = clan;
            morale = (int) (((double) morale) * morale_inc);
            if (morale > max_morale) {
                morale = max_morale;
            }
            return;
        }
            //If the group was part of a clan and the new clan
            // is different or empty
        else {
            this->clan = clan;
            morale = (int) (((double) morale) * morale_dec);
            return;
        }
    }

    bool mtm::Group::operator<(const Group &rhs) const{
        return (compareGroups(rhs) > 0);
    }

    bool mtm::Group::operator>(const Group &rhs) const{
        return (compareGroups(rhs) < 0);
    }

    bool mtm::Group::operator<=(const Group& rhs) const{
        return !(*this > rhs);
    }

    bool mtm::Group::operator>=(const Group& rhs) const{
        return !(*this < rhs);
    }

    bool mtm::Group::operator==(const Group& rhs) const{
        return (!(*this < rhs) && !(*this > rhs));
    }

    bool mtm::Group::operator!=(const Group& rhs) const{
        return !(*this == rhs);
    }

    bool mtm::Group::unite(Group& other, int max_amount){
        if (this == &other) {
            //Same group
            return false;
        }
        //After we checked that the clans same, if one is empty so is the other
        if (clan != other.clan || clan.empty()){
            return false;
        }
        int total_size = getSize() + other.getSize();
        if (total_size > max_amount) {
            return false;
        }
        if (morale < min_morale_to_unite || other.morale < min_morale_to_unite) {
            return false;
        }
        //Union succeed:
        if (other.calcPower() > calcPower()) {
            name = other.name;
        }
        int morale_tmp = ((getSize() * morale + other.getSize() * other.morale)
                          / (total_size));
        children += other.children;
        adults += other.adults;
        tools += other.tools;
        food += other.food;
        morale = morale_tmp;
        //Empty the other group
        other.name = "";
        other.clan = "";
        other.children = empty;
        other.adults = empty;
        other.tools = empty;
        other.food = empty;
        other.morale = empty;
        return true;
    }

    Group mtm::Group::divide(const std::string& name){
        if(name.empty()) {
            throw GroupInvalidArgs();
        }
        if(children <= 1 && adults <= 1) {
            throw GroupCantDivide();
        }
        //Auto floor
        Group new_group
                (name, clan, children/2, adults/2, tools/2, food/2, morale);
        children -= new_group.children;
        adults -= new_group.adults;
        tools -= new_group.tools;
        food -= new_group.food;
        return new_group;
    }

    FIGHT_RESULT mtm::Group::fight(Group& opponent){
        if (this == &opponent) {
            throw GroupCantFightWithItself();
        }
        if (getSize() == empty || opponent.getSize() == empty) {
            throw GroupCantFightEmptyGroup();
        }
        if (*this == opponent) {
            return DRAW;
        }
        else if (*this < opponent) {
            opponent.handleFightEffects(*this);
            return LOST;
        }
        else {
            handleFightEffects(opponent);
            return  WON;
        }
    }
    bool mtm::Group::trade(Group& other){
        if (this == &other) {
            throw GroupCantTradeWithItself();
        }
        if (food == tools || other.food == other.tools) {
            return false;
        }
        if (food > tools && other.food > other.tools) {
            return false;
        }
        if (food < tools && other.food < other.tools) {
            return false;
        }
        //trade success
        int this_diff = food - tools;
        int other_diff = other.food - other.tools;
        //Ceiling
        int delta_this = (abs(this_diff) + trade_factor - 1) / trade_factor;
        int delta_other = (abs(other_diff) + trade_factor -1) / trade_factor;
        int trade_val = ((delta_this + delta_other) + trade_factor -1)
                        / trade_factor;
        if (this_diff > same) {
            //The this group has more food then tools,
            //which means the other group has more tools then food.
            trade(other, trade_val);
        }
        else {
            //The other group has more food then tools,
            //which means the this group has more tools then food.
            other.trade(*this, trade_val);
        }
        return true;
    }

    std::ostream& operator<<(std::ostream& os, const Group& group){
        using namespace std;
        os << "Group's name: " << group.name << endl;
        os << "Group's clan: " << group.clan << endl;
        os << "Group's children: " << group.children << endl;
        os << "Group's adults: " << group.adults << endl;
        os << "Group's tools: " << group.tools << endl;
        os << "Group's food: " << group.food << endl;
        os << "Group's morale: " << group.morale << endl;
        return os;
    }

    //----------------------------------------------------------------------
    /**
     * Private functions implementation
     * @return
     */
    //----------------------------------------------------------------------
    double Group::calcPower() const{
        int people_factor = adult_power_factor * adults
                            + children_power_factor * children;
        int other_factor = tools_power_factor * tools
                           + food_power_factor * food;
        double power = ((double)(people_factor * other_factor * morale))
                       / power_divide;
        return power;
        }

        double Group::compareGroups(const Group &rhs) const{
            double powerDiff = rhs.calcPower() - calcPower();
            if(powerDiff != same) {
                return powerDiff;
            }
            else {
                //rhs.power == this->power
                return ((double)(rhs.name.compare(name)));
            }
        }

        void Group::handleFightEffects(Group& loser){
            //Ceiling
            if (loser.children != empty) {
                loser.children -= ((lost_children_mul_factor * loser.children
                                    + lost_children_div_factor - 1) /
                                   lost_children_div_factor);
            }
            //Ceiling
            if (loser.adults != empty) {
                loser.adults -= ((lost_adults_mul_factor * loser.adults
                                  + lost_adults_div_factor - 1) /
                                 lost_adults_div_factor);
            }
            //Ceiling
            if (loser.tools != empty) {
                loser.tools -= ((lost_tools_mul_factor * loser.tools
                                 + lost_tools_div_factor - 1) /
                                lost_tools_div_factor);
            }
            //Ceiling
            int food_lost = empty;
            if (loser.food != empty) {
                food_lost = ((lost_food_mul_factor * loser.food
                              + lost_food_div_factor - 1) /
                             lost_food_div_factor);
                loser.food -= food_lost;
            }
            //Ceiling
            loser.morale -= ((lost_morale * loser.morale + 100 -1) / 100);
            if (loser.morale < empty) {
                loser.morale = empty;
            }
            //Floor
            children += ((won_children_mul_factor * children) /
                         won_children_div_factor);
            //Floor
            if (adults != empty) {
                adults -= ((won_adults_mul_factor * adults)
                           / won_adults_div_factor);
            }
            //Floor
            if (tools != empty) {
                tools -= ((won_tools_mul_factor * tools)
                          / won_tools_div_factor);
            }
            //Floor
            food += (won_food_mul_factor * food_lost) / won_food_div_factor;
            //Ceiling
            morale += ((won_morale * morale + 100 -1) / 100);
            if (morale > full) {
                morale = full;
            }
        }

        void Group::trade(Group& other, int trade) {
            if (food < trade) {
                trade = food;
            }
            if (other.tools < trade) {
                trade = other.tools;
            }
            food -= trade;
            tools += trade;
            other.food += trade;
            other.tools -= trade;
        }


} //namespace mtm

