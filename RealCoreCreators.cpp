#include "RealCoreCreators.hpp"


namespace arbiter
{

    DATCreator::DATCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2):
        CoreCreator(CORE_TO_CREATE_SIZE, warrior_1, warrior_2)
    {}

    DATCreator::CorePtr DATCreator::createCore(ObserverPtr &obs_ptr)const
    {
        IntegerRegister FIRST_POS = countPositionWarrior1();//jesli rdzeń jest za mały dla wojowników - to te fcje rzucają wyjątek
        IntegerRegister SECOND_POD = countPositionWarrior2();

        const IntegerRegister ZERO(CORE_TO_CREATE_SIZE_, 0);
        const Operand::OperandPtr IMMID_OP(new ImmidiateOperand(ZERO));
        const InsPtr DAT_TO_COPY(new DATInstruction(IMMID_OP->clone(), IMMID_OP->clone() ) );

        CorePtr created_core = CorePtr(new Core(obs_ptr) );
        //wstawiamy to co pomiedzy zerowym adresem pamieci rdzenia a warriorem_1
        for(unsigned int i = 0 ;i != FIRST_POS.getValue(); ++i)
        {
            created_core->core_memory_.push_back(DAT_TO_COPY->clone() );
        }

        InsPtr temp;
        //wstawiamy kod wojownika 1
        for(unsigned int j = 0; j < warrior_1_.instuctions_.size() ; ++j )
        {
            temp = ( warrior_1_.instuctions_.at(j) )->clone();
            created_core->core_memory_.push_back( std::move(temp) );
        }
        //teraz wstawiamy pomiedzy wojowników instrukcje DAT
        for(unsigned int i = warrior_1_.instuctions_.size() + FIRST_POS.getValue(); i<SECOND_POD.getValue();++i)
        {
            created_core->core_memory_.push_back(DAT_TO_COPY->clone());
        }
        //wstawiamy kod wojownika 2
        for(unsigned int j = 0; j < warrior_2_.instuctions_.size(); ++j)
        {
            temp = ( warrior_2_.instuctions_.at(j) )->clone();
            created_core->core_memory_.push_back( std::move(temp) );
        }
        //teraz az do konca rdzenia wstawiamy instrukcje DAT
        for(unsigned int i = warrior_2_.instuctions_.size() + SECOND_POD.getValue(); i< CORE_TO_CREATE_SIZE_; ++i)
        {
            created_core->core_memory_.push_back(DAT_TO_COPY->clone() );
        }

        return std::move(created_core);
    }

    void DATCreator::modifyCore(CorePtr &existed_core) const
    {
        throw std::runtime_error("TODO");
    }
}
