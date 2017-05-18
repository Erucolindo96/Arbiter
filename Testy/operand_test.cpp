
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/Operand.hpp"
#include"../Arbiter/RealOperands.hpp"

using namespace boost::unit_test;
//using namespace boost::unit_test_framework;
using namespace arbiter;

using namespace std;

const unsigned int CORE_SIZE = 10;
BOOST_AUTO_TEST_SUITE( Integer_Register_Test )


BOOST_AUTO_TEST_CASE(Constructor)
{
    cout<<"Testy Operandow\n";
    int value = -6;
    const IntegerRegister one(CORE_SIZE,value );
//immidiate
    Operand::OperandPtr ptr = Operand::OperandPtr(new ImmidiateOperand(one));
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>( ptr.get() ));
    BOOST_CHECK(ptr->getValue() == one );
//direct
    Operand::OperandPtr ptr_2 = Operand::OperandPtr(new DirectOperand(one));
    BOOST_CHECK(dynamic_cast<DirectOperand*>( ptr_2.get() ));
    BOOST_CHECK(ptr_2->getValue() == one );
//indirect
    Operand::OperandPtr ptr_3 = Operand::OperandPtr(new IndirectOperand(one));
    BOOST_CHECK(dynamic_cast<IndirectOperand*>( ptr_3.get() ));
    BOOST_CHECK(ptr_3->getValue() == one );
//decrement
    Operand::OperandPtr ptr_4 = Operand::OperandPtr(new IndirectDecrementOperand(one));
    BOOST_CHECK(dynamic_cast<IndirectDecrementOperand*>( ptr_4.get() ));
    BOOST_CHECK(ptr_4->getValue() == one );
//increment
    Operand::OperandPtr ptr_5 = Operand::OperandPtr(new IndirectIncrementOperand(one));
    BOOST_CHECK(dynamic_cast<IndirectIncrementOperand*>( ptr_5.get() ));
    BOOST_CHECK(ptr_5->getValue() == one );


//    Operand::OperandPtr new_ptr = Operand::OperandPtr(new ImmidiateOperand() )
}
BOOST_AUTO_TEST_CASE(clone)
{
    int value = -22;
    const IntegerRegister one(CORE_SIZE,value );
//immidiate
    Operand::OperandPtr ptr = Operand::OperandPtr(new ImmidiateOperand(one));
    Operand::OperandPtr new_ptr = ptr->clone();
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>( ptr.get() ));
    BOOST_CHECK(dynamic_cast<ImmidiateOperand*>( new_ptr.get() ));
    BOOST_CHECK(ptr->getValue() == one );
    BOOST_CHECK(new_ptr->getValue() == one );

    //direct
    Operand::OperandPtr ptr_2 = Operand::OperandPtr(new DirectOperand(one));
    Operand::OperandPtr new_ptr_2 = ptr_2->clone();
    BOOST_CHECK(dynamic_cast<DirectOperand*>( ptr_2.get() ));
    BOOST_CHECK(dynamic_cast<DirectOperand*>( new_ptr_2.get() ));
    BOOST_CHECK(ptr_2->getValue() == one );
    BOOST_CHECK(new_ptr_2->getValue() == one );

    //indirect
    Operand::OperandPtr ptr_3 = Operand::OperandPtr(new IndirectOperand(one));
    Operand::OperandPtr new_ptr_3 = ptr_3->clone();
    BOOST_CHECK(dynamic_cast<IndirectOperand*>( ptr_3.get() ));
    BOOST_CHECK(dynamic_cast<IndirectOperand*>( new_ptr_3.get() ));
    BOOST_CHECK(ptr_3->getValue() == one );
    BOOST_CHECK(new_ptr_3->getValue() == one );

    //decrement
    Operand::OperandPtr ptr_4 = Operand::OperandPtr(new IndirectDecrementOperand(one));
    Operand::OperandPtr new_ptr_4 = ptr_4->clone();
    BOOST_CHECK(dynamic_cast<IndirectDecrementOperand*>( ptr_4.get() ));
    BOOST_CHECK(dynamic_cast<IndirectDecrementOperand*>( new_ptr_4.get() ));
    BOOST_CHECK(ptr_4->getValue() == one );
    BOOST_CHECK(new_ptr_4->getValue() == one );

    //increment
    Operand::OperandPtr ptr_5 = Operand::OperandPtr(new IndirectIncrementOperand(one));
    Operand::OperandPtr new_ptr_5 = ptr_5->clone();
    BOOST_CHECK(dynamic_cast<IndirectIncrementOperand*>( ptr_5.get() ));
    BOOST_CHECK(dynamic_cast<IndirectIncrementOperand*>( new_ptr_5.get() ));
    BOOST_CHECK(ptr_5->getValue() == one );
    BOOST_CHECK(new_ptr_5->getValue() == one );

}
BOOST_AUTO_TEST_CASE(getters_and_settert)
{
    int value = 13;
    const IntegerRegister one(CORE_SIZE,value ), two(CORE_SIZE, value+4);
//immidiate
    //Operand::OperandPtr ptr = Operand::OperandPtr(new ImmidiateOperand(one));
    ImmidiateOperand operand(one);

    BOOST_CHECK(operand.getValue() == one );
    operand.setValue(two);
    BOOST_CHECK(operand.getValue() == two );
    operand.setValue(one);
    BOOST_CHECK(operand.getValue() == one );

}
/*
 *  jeszcze nie maja operatora przypisania - jak bedzie trzeba go sie go zrobi
BOOST_AUTO_TEST_CASE(assignement)
{
    int value = 28;
    const IntegerRegister one(CORE_SIZE,value ), two(CORE_SIZE, value+4);
//immidiate
    //Operand::OperandPtr ptr = Operand::OperandPtr(new ImmidiateOperand(one));
    ImmidiateOperand operand(two), operand_2(one);

    BOOST_CHECK(operand.getValue() == two );

    operand = operand_2;
    BOOST_CHECK(operand.getValue() == one );
    BOOST_CHECK(operand_2.getValue() = one);

    operand.setValue(two);
    BOOST_CHECK(operand.getValue() == two );


}
*/


BOOST_AUTO_TEST_SUITE_END()
