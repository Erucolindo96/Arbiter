
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/RealCoreCreators.hpp"

#include<vector>
#include"../Arbiter/Warrior.hpp"
#include"../Arbiter/Instruction.hpp"
#include"../Arbiter/Arbiter.hpp"

using namespace boost::unit_test;
//using namespace boost::unit_test_framework;
using namespace arbiter;

using namespace std;

//vector<Instruction::InsPtr> war_1_vect(), war_2_vect;

class MokeObserver: public Observer
{
public:
    virtual void update()
    {
        cout<<"Aktualizacja Obserwatora\n";
    }
};

Warrior war_1, war_2;

unique_ptr<Observer> observer_ptr;

unique_ptr<Observer> mok;

const unsigned int CORE_SIZE = 100;





void generateWarriors()//pierwszy wojownik - 2 instrukcje mov, drugi - mov, dat, mov
{
    const IntegerRegister oper(CORE_SIZE, 5);

    const Operand::OperandPtr oper_direct(new ImmidiateOperand(oper));
    const Instruction::InsPtr move_ins(new MOVInstruction(oper_direct->clone(), oper_direct->clone() ) );
    const Instruction::InsPtr dat_ins(new DATInstruction(oper_direct->clone(),  oper_direct->clone() ) );
    Instruction::InsPtr temp;

    war_1.addInstruction(move_ins );
    war_1.addInstruction(move_ins );
    war_1.setName("Wojownik 1");

    war_2.addInstruction(move_ins );
    war_2.addInstruction(dat_ins  );
    war_2.addInstruction(move_ins );
    war_2.setName("Wojownik 2");

    mok = unique_ptr<MokeObserver>(new MokeObserver());

}



BOOST_AUTO_TEST_SUITE(Core_Creators_Tests)



BOOST_AUTO_TEST_CASE(Constructor)
{
    generateWarriors();

    cout<<"Test Core Creatorow\n";
    Arbiter::CoreCreatorPtr core_creator_ptr = Arbiter::CoreCreatorPtr(new DATCreator(CORE_SIZE, war_1, war_2) );
    BOOST_CHECK(war_1.getName() == core_creator_ptr->getWarrior1Ref().getName());
    BOOST_CHECK(war_2.getName() == core_creator_ptr->getWarrior2Ref().getName());
    for(int i=0;i<war_1.instuctions_.size(); ++i)
    {
        BOOST_CHECK(war_1.instuctions_.at(i)->operandA()->getValue()  == core_creator_ptr->getWarrior1Ref().instuctions_.at(i)->operandA()->getValue()  );
        BOOST_CHECK(war_1.instuctions_.at(i)->operandB()->getValue() == core_creator_ptr->getWarrior1Ref().instuctions_.at(i)->operandB()->getValue() );
    }
    for(int i=0;i<war_2.instuctions_.size(); ++i)
    {
        BOOST_CHECK(war_2.instuctions_.at(i)->operandA()->getValue()  == core_creator_ptr->getWarrior2Ref().instuctions_.at(i)->operandA()->getValue()  );
        BOOST_CHECK(war_2.instuctions_.at(i)->operandB()->getValue() == core_creator_ptr->getWarrior2Ref().instuctions_.at(i)->operandB()->getValue() );
    }

        BOOST_CHECK(dynamic_cast<MOVInstruction*> (war_1.instuctions_.at(0).get())   );
        BOOST_CHECK(dynamic_cast<MOVInstruction*> (war_1.instuctions_.at(1).get())   );

        BOOST_CHECK(dynamic_cast<MOVInstruction*> (core_creator_ptr->getWarrior1Ref().instuctions_.at(0).get())   );
        BOOST_CHECK(dynamic_cast<MOVInstruction*> (core_creator_ptr->getWarrior1Ref().instuctions_.at(1).get())   );

        BOOST_CHECK(dynamic_cast<MOVInstruction*> (war_2.instuctions_.at(0).get())   );
        BOOST_CHECK(dynamic_cast<DATInstruction*> (war_2.instuctions_.at(1).get())   );
        BOOST_CHECK(dynamic_cast<MOVInstruction*> (war_2.instuctions_.at(2).get())   );

        BOOST_CHECK(dynamic_cast<MOVInstruction*> (core_creator_ptr->getWarrior2Ref().instuctions_.at(0).get())   );
        BOOST_CHECK(dynamic_cast<DATInstruction*> (core_creator_ptr->getWarrior2Ref().instuctions_.at(1).get())   );
        BOOST_CHECK(dynamic_cast<MOVInstruction*> (core_creator_ptr->getWarrior2Ref().instuctions_.at(2).get())   );

}

BOOST_AUTO_TEST_CASE(Core_creating)
{

    Arbiter::CoreCreatorPtr core_creator_ptr = Arbiter::CoreCreatorPtr(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr my_core = core_creator_ptr->createCore(observer_ptr);
    //cout<<my_core->getCoreSize()<<endl;
    BOOST_CHECK(my_core->getCoreSize() == CORE_SIZE);
    for(unsigned int i = 0; i < war_1.instuctions_.size();++i)
    {
        Core::InsPtr instruct =  my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, i) );
        BOOST_CHECK(dynamic_cast<MOVInstruction*>( instruct.get() ) );
        BOOST_CHECK(instruct->operandA()->getValue() == (war_1.instuctions_[i])->operandA()->getValue()  );
        BOOST_CHECK(instruct->operandB()->getValue() == (war_1.instuctions_[i])->operandB()->getValue()  );
    }
    for(unsigned int i = war_1.instuctions_.size(); i < CORE_SIZE/2; ++i)
    {
        Core::InsPtr instruct =  my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, i) );
        BOOST_CHECK(dynamic_cast<DATInstruction*>( instruct.get() ) );
        BOOST_CHECK(instruct->operandA()->getValue() == IntegerRegister(CORE_SIZE)  );
        BOOST_CHECK(instruct->operandB()->getValue() == IntegerRegister(CORE_SIZE)  );
    }
    Core::InsPtr instruct =  my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, CORE_SIZE/2) );
    BOOST_CHECK(dynamic_cast<MOVInstruction*>( instruct.get() ) );
    BOOST_CHECK(instruct->operandA()->getValue() == (war_2.instuctions_[0])->operandA()->getValue()  );
    BOOST_CHECK(instruct->operandB()->getValue() == (war_2.instuctions_[0])->operandB()->getValue()  );

    instruct = my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, CORE_SIZE/2 + 1) );
    BOOST_CHECK(dynamic_cast<DATInstruction*>( instruct.get() ) );
    BOOST_CHECK(instruct->operandA()->getValue() == (war_2.instuctions_[1])->operandA()->getValue()  );
    BOOST_CHECK(instruct->operandB()->getValue() == (war_2.instuctions_[1])->operandB()->getValue()  );

    instruct = my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, CORE_SIZE/2 + 2) );
    BOOST_CHECK(dynamic_cast<MOVInstruction*>( instruct.get() ) );
    BOOST_CHECK(instruct->operandA()->getValue() == (war_2.instuctions_[2])->operandA()->getValue()  );
    BOOST_CHECK(instruct->operandB()->getValue() == (war_2.instuctions_[2])->operandB()->getValue()  );

    for(unsigned int i = war_2.instuctions_.size() + CORE_SIZE/2; i < CORE_SIZE; ++i)
    {
        Core::InsPtr instruct =  my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, i) );
        BOOST_CHECK(dynamic_cast<DATInstruction*>( instruct.get() ) );
        BOOST_CHECK(instruct->operandA()->getValue() == IntegerRegister(CORE_SIZE)  );
        BOOST_CHECK(instruct->operandB()->getValue() == IntegerRegister(CORE_SIZE)  );
    }
}


BOOST_AUTO_TEST_CASE(Core_Method_Test)
{
    Arbiter::CoreCreatorPtr core_creator_ptr = Arbiter::CoreCreatorPtr(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr my_core = core_creator_ptr->createCore(mok);
/*
    //zwracanie

    Core::InsPtr instruct;
    BOOST_CHECK_NO_THROW( instruct = my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, -22)));

    instruct = my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, -5));
    BOOST_CHECK(dynamic_cast<MOVInstruction*> (instruct.get() ));

    //modyfikacja

    instruct = war_1.instuctions_.at(0)->clone();//przypisze MOVInstruction

    my_core->modifyInstruction(IntegerRegister(CORE_SIZE, 4), instruct->clone());

    Core::InsPtr modify_ins = my_core->getInstructionCopy(IntegerRegister(CORE_SIZE, 4));
    BOOST_CHECK(dynamic_cast<MOVInstruction*> (modify_ins.get()));
    BOOST_CHECK(instruct->operandA()->getValue() == modify_ins->operandA()->getValue());
    BOOST_CHECK(instruct->operandB()->getValue() == modify_ins->operandB()->getValue());

*/
}



BOOST_AUTO_TEST_SUITE_END()
