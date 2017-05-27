
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/Arbiter.hpp"
#include"RealInstructions.hpp"
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
