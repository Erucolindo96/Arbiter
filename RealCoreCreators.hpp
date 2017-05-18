#ifndef REALCORECREATORS_HPP
#define REALCORECREATORS_HPP

#include"CoreCreator.hpp"
#include"RealInstructions.hpp"

#include<memory>
namespace arbiter
{




    /**
    * @brief The DATCreator class Tworzy rdzeń zapełniony instrukcjami DAT
    *
    */
    class DATCreator : public CoreCreator
    {
    public:

        typedef std::unique_ptr<Core> CorePtr;

        DATCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2 );

         virtual CorePtr createCore(ObserverPtr &obs_ptr) const;
        virtual void modifyCore(CorePtr &existed_core_ptr)const;
    };


}
#endif // REALCORECREATORS_HPP
