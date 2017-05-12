#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include<vector>
#include"Instruction.hpp"

namespace arbiter
{

class Instruction;

    struct Warrior
    {
    public:
        typedef std::unique_ptr<Instruction> InsPtr;

        Warrior() = delete;
        Warrior(std::vector<InsPtr> &code_of_warrior);
        Warrior(std::vector<InsPtr> &&code_of_warrior);

        Warrior& operator=(const Warrior &other);


        std::vector<InsPtr> instuctions_;

    };

}

#endif // WARRIOR_HPP
