#include "CoreCreator.hpp"

namespace arbiter
{

    CoreCreator::CoreCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2 ): warrior_1_(warrior_1), warrior_2_(warrior_2), CORE_TO_CREATE_SIZE_(CORE_TO_CREATE_SIZE)
    {}


    const Warrior& CoreCreator::getWarrior1Ref()const
    {
        return warrior_1_;
    }

    const Warrior& CoreCreator::getWarrior2Ref()const
    {
        return warrior_2_;
    }


    bool CoreCreator::isEnoughPlaceForWarriors()const
    {
        const unsigned int HALF_CORE = CORE_TO_CREATE_SIZE_/2;
        unsigned int first_size = warrior_1_.instuctions_.size();
        unsigned int second_size = warrior_2_.instuctions_.size();

        if( (first_size > HALF_CORE) || (second_size > HALF_CORE) )
            return false;

        return true;
    }

    IntegerRegister CoreCreator::countPositionWarrior1()const
    {
        const unsigned int FIRST_POS = 0; //pierwszego zawsze wklejamy na pozycji zerowej
        if(!isEnoughPlaceForWarriors())
            throw std::length_error("CoreCreator: Size of creating core is too less for warriors\n");

        return IntegerRegister(CORE_TO_CREATE_SIZE_, FIRST_POS);
    }

    IntegerRegister CoreCreator::countPositionWarrior2()const
    {
        const unsigned int HALF_CORE = CORE_TO_CREATE_SIZE_ / 2;
        //unsigned int second_pos = HALF_CORE + 1;

        if(!isEnoughPlaceForWarriors())
            throw std::length_error("CoreCreator: Size of creating core is too less for warriors\n");

        return IntegerRegister(CORE_TO_CREATE_SIZE_, HALF_CORE);
    }







}
