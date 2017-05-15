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

    class CoreCreator
    {
        typedef std::shared_ptr<Instruction> InsSharedPtr;
        typedef std::unique_ptr<Instruction> InsPtr;
        typedef std::unique_ptr<Core> CorePtr;
        typedef std::unique_ptr<Observer> ObserverPtr;

    public:
        CoreCreator(const unsigned int CORE_TO_CREATE_SIZE, const std::vector<Warrior> &warriors_to_create);


         std::vector<Warrior> getWarriorsCopy()const;

        /**
         * @brief createCore() Tworzy rdzeń w postaci wektora Instrukcji
         * @return Wskazanie do utworzonego rdzenia
         */
        virtual CorePtr createCore(const ObserverPtr &obs_ptr) const = 0;
        /**
         * @brief modifyCore Modyfikuje już istniejący rdzeń w odpowiedni sposób
         * @param existed_core_ptr Wskazanie do istniejącego już rdzenia
         */
        virtual void modifyCore(CorePtr existed_core_ptr)const = 0;


    private:
        std::vector<Warrior> warriors_to_create_;
        const unsigned int CORE_TO_CREATE_SIZE_;

    };


}

#endif // CORECREATOR_HPP
