#ifndef CORECREATOR_HPP
#define CORECREATOR_HPP


#include"Core.hpp"
#include<vector>
#include"Instruction.hpp"
#include<memory>
#include"Warrior.hpp"
#include"Observer.hpp"

namespace arbiter
{
    class Instruction;
    class Core;
    class Warrior;

    /**
     * Założenia: wojownicy mogą być co najwyżej wielkości połowy rdzenia. Jeśli którys z nich nie jest - rzucany jest wyjątek.
     *
     * @brief The CoreCreator class
     *
     *
     */
    class CoreCreator
    {
    protected:
        typedef std::shared_ptr<Instruction> InsSharedPtr;
        typedef std::unique_ptr<Instruction> InsPtr;
        typedef std::unique_ptr<Core> CorePtr;
        typedef std::unique_ptr<Observer> ObserverPtr;

    public:
        CoreCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2 );

        unsigned int getCoreSize()const;

        // std::vector<Warrior> getWarriorsCopy()const;
        const Warrior& getWarrior1Ref()const;
        const Warrior& getWarrior2Ref()const;

        /**
         * @brief getPositionWarriorFirst Zwraca adres pierszej instrukcji wojownika 1
         * @return Adres pierwszej instrukcji wojownika 1
         */
        IntegerRegister getPositionWarriorFirst()const;
        /**
         * @brief getPositionWarriorSecond Zwraca adres pierszej instrukcji wojownika 2
         * @return Adres pierwszej instrukcji wojownika 2
         */
        IntegerRegister getPositionWarriorSecond()const;

        /**
         * @brief createCore() Tworzy rdzeń w postaci wektora Instrukcji
         * @return Wskazanie do utworzonego rdzenia
         */
        virtual CorePtr createCore( ObserverPtr &obs_ptr) const = 0;
        /**
         * @brief modifyCore Modyfikuje już istniejący rdzeń w odpowiedni sposób
         * @param existed_core_ptr Wskazanie do istniejącego już rdzenia
         */
        virtual void modifyCore(CorePtr &existed_core_ptr)const = 0;


    protected:
        Warrior warrior_1_;
        Warrior warrior_2_;
        const unsigned int CORE_TO_CREATE_SIZE_;

        virtual IntegerRegister countPositionWarrior1()const;
        virtual IntegerRegister countPositionWarrior2()const;

        virtual bool isEnoughPlaceForWarriors()const;

    };


}

#endif // CORECREATOR_HPP
