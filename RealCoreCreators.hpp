#ifndef REALCORECREATORS_HPP
#define REALCORECREATORS_HPP

#include"CoreCreator.hpp"
#include<memory>
namespace arbiter
{




    /**
    * @brief The DATCreator class Tworzy rdzeń zapełniony instrukcjami DAT
    * Wywołanie metody modifyCore() spowoduje zainicjowanie rdzenia
    */
    class DATCreator : public CoreCreator
    {
    public:

        typedef std::shared_ptr<Core> CorePtr;
        DATCreator(const unsigned int CORE_TO_CREATE_SIZE, std::vector<Warrior> &warriors_to_create);

        virtual CorePtr createCore() const ;
        virtual void modifyCore(CorePtr existed_core)const;
    };


}
#endif // REALCORECREATORS_HPP
