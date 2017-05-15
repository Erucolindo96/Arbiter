#include "Warrior.hpp"

namespace arbiter
{


    Warrior::Warrior():  instuctions_(),name_()
    {}

    Warrior::Warrior(const std::string &name,const  std::vector<InsPtr> &code_of_warrior):name_(name)
    {
        for(auto iter = code_of_warrior.begin(); iter != code_of_warrior.end(); ++iter)
        {
            instuctions_.push_back( (*iter)->clone() );//kopiujemy instrukcje
        }
    }

    Warrior::Warrior(const std::string &name, std::vector<InsPtr> &&code_of_warrior):instuctions_(std::move(code_of_warrior)), name_(name)
    {
/*        for(auto iter = code_of_warrior.begin(); iter != code_of_warrior.end();++iter)
        {
            instuctions_.push_back( std::move(*iter) );//cholera wie jak to sie zachowa
        }
*/
   }

    Warrior::Warrior(const Warrior &other):Warrior(other.name_, other.instuctions_)
    {}

    Warrior& Warrior::operator=(const Warrior &other)
    {
        if(this == &other)
            return *this;

        instuctions_.clear();
        for(auto iter = other.instuctions_.begin(); iter != other.instuctions_.end(); ++iter)
        {
            instuctions_.push_back( (*iter)->clone() );//kopiujemy instrukcje
        }

        name_ = other.name_;
        return *this;
    }
/*
    Warrior& Warrior::operator=(const Warrior &&other)
    {
        if(this == &other)
            return *this;

        instuctions_.clear();

        for(auto iter = other.instuctions_.begin(); iter != other.instuctions_.end(); ++iter)
        {
            instuctions_.push_back(std::move( *iter ) );//kopiujemy instrukcje
        }

        name_ =std::move( other.name_ );
        return *this;
    }

*/

/*
    Warrior Warrior::getCopy()const
    {
        return Warrior(name_, getInstructionsCopy());
    }
*/
    std::string Warrior::getName()const
    {
        return name_;
    }

/*    std::vector<Instruction::InsPtr> Warrior::getInstructionsCopy()const
    {
        std::vector<InsPtr> returned = copyInstructionVector(instuctions_);

        for(auto iter = instuctions_.begin(); iter!= instuctions_.end(); ++iter)
        {
            returned.push_back( (*iter)->clone() );//kopiujemy instrukcje
        }

        return returned;
    }
*/

    void Warrior::setName(const std::string &name)
    {
        name_ = name;
    }

    void Warrior::setInstructions(const std::vector<InsPtr> &instructions)
    {
        instuctions_.clear();

        //dokladna kopia kodu konstruktora
        for(auto iter = instructions.begin(); iter != instructions.end(); ++iter)
        {
            instuctions_.push_back( (*iter)->clone() );//kopiujemy instrukcje
        }
    }



}
