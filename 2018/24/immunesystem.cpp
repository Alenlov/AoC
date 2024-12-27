#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <regex>
#include <iterator>
#include <map>
#include <list>

struct unit
{
    long number;
    long number_init;
    long hp;
    long attack;
    long attack_init;
    long init;
    long effective_power;
    bool immune_system;

    int id;

    bool targeted{false};
    unit* target;

    std::string type;
    std::vector<std::string> weaknesses;
    std::vector<std::string> immunities;

    void update_effective_power()
    {
        effective_power = number*attack;
    }

    bool operator<(const unit& rhs) const
    {
        return rhs.effective_power < effective_power;
    }
    
    void reset()
    {
        number = number_init;
        update_effective_power();
    }

    long damage_to(unit *other)
    {
        update_effective_power();
        //std::cout << "My type is: " << type << std::endl;
        //std::cout << "My effective_power is " << effective_power << " test " << number*attack << std::endl;
        //std::cout << "Opponents weaknesses: ";
        for (auto w : other->weaknesses)
        {
            //std::cout << w << " ";
            if (w == type)
            {
                //std::cout << "found dubble" << std::endl;
                return 2 * effective_power;
            }
        }
        //std::cout << std::endl << "Opponents immunities ";
        for (auto i : other->immunities)
        {
            //std::cout << i << " ";
            if (i == type)
            {
                //std::cout << "found immunty" << std::endl;
                return 0;
            }
        }
        //std::cout << std::endl;
        return effective_power;
    }

    void take_damage(long dmg)
    {
        long lost_units = dmg/hp;
        number -= lost_units;
        if (number < 0)
        {
            number = 0;
        }
    }

    bool is_alive()
    {
        return number > 0;
    }
};

bool cmp_by_init(const unit* lhs, const unit* rhs)
{
    return rhs->init < lhs->init;
}

bool cmp_by_ep(const unit* lhs, const unit* rhs)
{
    if (rhs->effective_power != lhs->effective_power){
        return rhs->effective_power < lhs->effective_power;
    } else {
        return rhs->init < lhs->init;
    }
}

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos && (indx < line.length()))
    {
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0)
        {
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return vectorOfStrings;
}

bool fight_not_over(std::list<unit*> units)
{
    int num_immune{0}, num_infection{0};
    for (auto const& u : units)
    {
        if (u->is_alive())
        {
            if (u->immune_system)
            {
                num_immune += 1;
            }
            else
            {
                num_infection += 1;
            }
        }
    }
    bool fight = (num_immune > 0) && (num_infection > 0);
    //std::cout << num_immune << " vs " << num_infection << " fight is " << fight << std::endl;
    return fight;
}

bool immune_won(std::list<unit*> units)
{
    int num_immune{0}, num_infection{0};
    for (auto const& u : units)
    {
        if (u->is_alive())
        {
            if (u->immune_system)
            {
                num_immune += 1;
            }
            else
            {
                num_infection += 1;
            }
        }
    }
    bool fight = (num_immune > 0) && (num_infection == 0);
    return fight;
}

int uints_alive(std::list<unit*> units)
{
    int num_alive{0};
    for (auto const& u : units) {
        if (u->is_alive())
        {
            num_alive += u->number;
        }
    }
    return num_alive;
}



int main(int argc, char const *argv[])
{
    const std::regex reg_unit("(\\d+) units each with (\\d+) hit points \\(?([\\w, ;]+)?\\)? ?with an attack that does (\\d+) (\\w+) damage at initiative (\\d+)");
    const std::regex reg_weak("(weak|immune) to( ?\\w+,?)+");
    std::smatch m;
    std::smatch m_weak;
    std::ifstream myfile;
    std::string line;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    std::list<unit*> units;
    bool immune_system{true};
    if (myfile.is_open())
    {
        int id{0};
        while (getline(myfile, line))
        {
            if (std::regex_match(line, m, reg_unit))
            {
                unit *u = new unit;
                u->number = std::stol(m[1]);
                u->number_init = std::stol(m[1]);
                u->hp = std::stol(m[2]);
                u->attack = std::stol(m[4]);
                u->attack_init = std::stol(m[4]);
                u->init = std::stol(m[6]);
                u->type = m[5];
                std::string middle = m[3];
                if (middle.length() > 1)
                {
                    std::vector<std::string> weak_immune_vec = splitLine(middle, "; ");
                    for (auto s : weak_immune_vec)
                    {
                        std::vector<std::string> types = splitLine(s, " to ");
                        if (types[0] == "weak")
                        {
                            u->weaknesses = splitLine(types[1], ", ");
                        } else if (types[0] == "immune")
                        {
                            u->immunities = splitLine(types[1], ", ");
                        }
                    }
                }
                u->immune_system = immune_system;
                u->id = id;
                u->update_effective_power();
                u->target = NULL;
                units.push_back(u);
                ++id;
            } 
            else if (line == "Infection:")
            {
                immune_system = false;
            }
            
        }
        
    }
    myfile.close();


    int round{0};

    while(fight_not_over(units)){
        ++round;
        //std::cout << "\n\nRound: " << round << std::endl;
        units.sort(cmp_by_ep);

        for (auto const& u : units) {
            int u_id = u->id;
            if (!u->is_alive()) continue;
            // std::cout << u_id << " contains " << u->number << " units! " << u->effective_power << " " << u->init << std::endl;
            long most_damage{0};
            for (auto &o : units) {
                int o_id = o->id;
                if (!o->is_alive()) continue;
                if (u->immune_system != o->immune_system) {
                    long dmg = u->damage_to(o);
                    if ((dmg > most_damage) && !o->targeted) {
                        most_damage = dmg;
                        u->target = o;
                        //std::cout << "Choose id " << o->id << std::endl;
                    }
                }
            }
            if (u->target == NULL) {continue;}
            u->target->targeted = true;
            //std::cout << "ID: " << u_id << " targets " << units_map[u_id]->target << std::endl;
        }

        units.sort(cmp_by_init);

        for (auto &u : units) 
        {
            int id = u->id;
            if (!u->is_alive()) continue;
            if (u->target == NULL ) continue;
            //std::cout << u->id << " attacks " << u->target->id << " using " << u->number << " units with init " << u->init << std::endl;
            long dmg = u->damage_to(u->target);
            //std::cout << "Does " << dmg << " damage to " << u->target->number << " units" << std::endl;
            u->target->take_damage(dmg);
            //std::cout << u->target->number << " left" << std::endl;
            //std::cout << std::endl;
        }

        for (auto &u : units) 
        {
            u->update_effective_power();
            u->target = NULL;
            u->targeted = false;
        }
    }

    int ansA = uints_alive(units);
    std::cout << "Answer part A: " << ansA << std::endl;
    int boost{0};
    bool partB{false};
    
    while (!partB) 
    {
        boost += 1;
        for (auto &u : units)
        {
            u->reset();
            if (u->immune_system)
            {
                u->attack = u->attack_init+boost;
                std::cout << "Boost " << boost << " gives attack " << u->attack << " with " << u->attack_init << std::endl;
            }
        }

        while(fight_not_over(units))
        {
            units.sort(cmp_by_ep);

            for (auto const& u : units) {
                int u_id = u->id;
                if (!u->is_alive()) continue;
                long most_damage{0};
                for (auto &o : units) {
                    int o_id = o->id;
                    if (!o->is_alive()) continue;
                    if (u->immune_system != o->immune_system) {
                        long dmg = u->damage_to(o);
                        if ((dmg > most_damage) && !o->targeted) {
                            most_damage = dmg;
                            u->target = o;
                        }
                    }
                }
                if (u->target == NULL) {continue;}
                u->target->targeted = true;
            }

            units.sort(cmp_by_init);
            int num_attacks{0};
            for (auto &u : units) 
            {
                int id = u->id;
                if (!u->is_alive()) continue;
                if (u->target == NULL ) 
                {
                    continue;
                }
                long num_before = u->target->number;
                long dmg = u->damage_to(u->target);
                u->target->take_damage(dmg);
                if (num_before > u->target->number)
                {
                    num_attacks++;
                }
            }
            int num_immune{0}, num_infection{0};
            for (auto const& u : units)
            {
                if (u->is_alive())
                {
                    if (u->immune_system)
                    {
                        num_immune += 1;
                    }
                    else
                    {
                        num_infection += 1;
                    }
                }
            }
            if (num_attacks == 0)
            {
                
                break;
            }

            for (auto &u : units) 
            {
                u->update_effective_power();
                u->target = NULL;
                u->targeted = false;
            }
        }
        partB = immune_won(units);
        
    }
    
    int ansB = uints_alive(units);
    std::cout << "Answer part B: " << ansB << " boost " << boost << " " << partB << std::endl;
}