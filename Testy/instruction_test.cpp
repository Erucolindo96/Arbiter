
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/RealInstructions.hpp"

using namespace boost::unit_test;
//using namespace boost::unit_test_framework;
using namespace arbiter;
using namespace std;


const unsigned int CORE_SIZE = 10;
IntegerRegister register_1(CORE_SIZE), register_2(CORE_SIZE);
Operand::OperandPtr op_ptr_1 = Operand::OperandPtr(new DirectOperand(register_1));
Operand::OperandPtr op_ptr_2 = Operand::OperandPtr(new ImmidiateOperand(register_2));

BOOST_AUTO_TEST_SUITE(Instruction_test)

BOOST_AUTO_TEST_CASE(Constructors)
{
    cout<<"Testy instrukcji\n";
    Instruction::InsPtr ptr = Instruction::InsPtr(new MOVInstruction( op_ptr_1, op_ptr_2 ));
    BOOST_CHECK(dynamic_cast<MOVInstruction*>(ptr.get()));
    BOOST_CHECK(dynamic_cast<DirectOperand*>(ptr->operandA().get()) );
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>(ptr->operandB().get()) );

    BOOST_CHECK(ptr->operandA()->getValue() == register_1 );
    BOOST_CHECK(ptr->operandB()->getValue() == register_2 );
//nieprzetestowane konstruktor kopiujący i przenoszący
    //Instruction::InsPtr ptr_2 = Instruction::InsPtr(new MOVInstruction(*ptr));

}
BOOST_AUTO_TEST_CASE(getters_and_setters)
{
    Instruction::InsPtr ins_ptr = Instruction::InsPtr(new DATInstruction( op_ptr_1, op_ptr_2 ));
    BOOST_CHECK(dynamic_cast<DATInstruction*>(ins_ptr.get()));
    BOOST_CHECK(dynamic_cast<DirectOperand*>(ins_ptr->operandA().get()) );
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>(ins_ptr->operandB().get()) );

    const IntegerRegister one(CORE_SIZE, 45), two(CORE_SIZE, 37);
    Operand::OperandPtr ptr_1 = Operand::OperandPtr(new DirectOperand(one));
    Operand::OperandPtr ptr_2 = Operand::OperandPtr(new ImmidiateOperand(two));
    ins_ptr->setOperandA(ptr_1);
    ins_ptr->setOperandB(ptr_2);

    BOOST_CHECK(ins_ptr->operandA()->getValue() == one );
    BOOST_CHECK(ins_ptr->operandB()->getValue() == two );

}
BOOST_AUTO_TEST_CASE(clone)
{
    Instruction::InsPtr ins_ptr = Instruction::InsPtr(new DATInstruction( op_ptr_1, op_ptr_2 ));
    BOOST_CHECK(dynamic_cast<DATInstruction*>(ins_ptr.get()));
    BOOST_CHECK(dynamic_cast<DirectOperand*>(ins_ptr->operandA().get()) );
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>(ins_ptr->operandB().get()) );

    BOOST_CHECK(ins_ptr->operandA()->getValue() == register_1 );
    BOOST_CHECK(ins_ptr->operandB()->getValue() == register_2 );

    Instruction::InsPtr clone_ins = ins_ptr->clone();
    BOOST_CHECK(dynamic_cast<DATInstruction*>(clone_ins.get()));
    BOOST_CHECK(dynamic_cast<DirectOperand*>(clone_ins->operandA().get()) );
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>(clone_ins->operandB().get()) );
    BOOST_CHECK(clone_ins->operandA()->getValue() == register_1 );
    BOOST_CHECK(clone_ins->operandB()->getValue() == register_2 );
}



BOOST_AUTO_TEST_SUITE_END()
