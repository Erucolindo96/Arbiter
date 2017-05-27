
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/RealInstructions.hpp"
#include"../Arbiter/RealCoreCreators.hpp"
#include<string>

using namespace boost::unit_test;
//using namespace boost::unit_test_framework;
using namespace arbiter;
using namespace std;


class MokeObserver: public Observer
{
public:
    virtual void update(const IntegerRegister &modified_ins_address)
    {
        cout<<"Aktualizacja Obserwatora\n";
    }
};


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

BOOST_AUTO_TEST_CASE(Execute_of_DAT)
{

    const IntegerRegister ZERO(CORE_SIZE, 0);
    Instruction::InsPtr dat_ins = Instruction::InsPtr(new DATInstruction(op_ptr_1, op_ptr_2));

    unique_ptr<Observer> observer = unique_ptr<Observer>(new MokeObserver() );

    Warrior war_1, war_2;
    war_1.instuctions_.push_back(dat_ins->clone() );
    war_2.instuctions_.push_back(dat_ins->clone() );
    unique_ptr<CoreCreator> creator_ptr = unique_ptr<CoreCreator>(new DATCreator(CORE_SIZE, war_1, war_2));

    Core::CorePtr core_ptr = creator_ptr->createCore(observer);
    Instruction::InsPtr executed_ins = core_ptr->getInstructionCopy(ZERO);
    ExecutionLog log_exec = executed_ins->execute(core_ptr, ZERO);
    BOOST_CHECK(log_exec.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 1));
    BOOST_CHECK(log_exec.is_proc_live_ == false);
    BOOST_CHECK(log_exec.is_proc_split_ == false);
    //sprawdzamy czy DAT nie zmodyfikował rdzenia
    for(unsigned int i = 0; i<CORE_SIZE;++i)
    {
        Instruction::InsPtr ins_ = core_ptr->getInstructionCopy( IntegerRegister(CORE_SIZE, i) );
        BOOST_CHECK( dynamic_cast<DATInstruction*>(ins_.get()) );
        BOOST_CHECK( ins_->getValueOperandA() == dat_ins->getValueOperandA() );
        BOOST_CHECK( ins_->getValueOperandB() == dat_ins->getValueOperandB() );
    }
}
BOOST_AUTO_TEST_CASE(exec_of_MOV)
{
    //stworzymy wojownika zawierajacego jedna isntrukcje MOV(0,1)
    //powinien on skopiowac samego siebie do kolejnek komorki pamieci
    Operand::OperandPtr op_mov_1 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, 0)) );
    Operand::OperandPtr op_mov_2 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, 1)) );

    Instruction::InsPtr mov_ins = Instruction::InsPtr(new MOVInstruction(op_mov_1, op_mov_2));
    Instruction::InsPtr dat_ins = Instruction::InsPtr(new DATInstruction(op_ptr_1, op_ptr_2));
    Warrior war_1, war_2;
    war_1.instuctions_.push_back(mov_ins->clone() );
    war_2.instuctions_.push_back(mov_ins->clone() );

    unique_ptr<Observer> moke = unique_ptr<Observer>(new MokeObserver() );
    unique_ptr<CoreCreator> creator = unique_ptr<CoreCreator>(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr core_ptr = creator->createCore(moke);

    //wykonujemy pierwszy raz MOV

    for(unsigned int i = 0; i<CORE_SIZE;++i)
    {
        Instruction::InsPtr exec_mov = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, i) );
        ExecutionLog exec_log = exec_mov->execute(core_ptr, IntegerRegister(CORE_SIZE, i) );
        BOOST_CHECK(exec_log.is_proc_live_ == true);
        BOOST_CHECK(exec_log.is_proc_split_ == false);
        BOOST_CHECK(exec_log.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, i+1));

        Instruction::InsPtr &our_ins = core_ptr->getInstructionRef(IntegerRegister(CORE_SIZE, i) );
        Instruction::InsPtr &next_pc_ins = core_ptr->getInstructionRef(IntegerRegister(CORE_SIZE, i+1) );
        BOOST_CHECK(dynamic_cast<MOVInstruction*>(our_ins.get() ) );
        BOOST_CHECK(dynamic_cast<MOVInstruction*>(next_pc_ins.get() ) );
        BOOST_CHECK(our_ins->getValueOperandA() == IntegerRegister(CORE_SIZE,0 )  );
        BOOST_CHECK(our_ins->getValueOperandB() == IntegerRegister(CORE_SIZE,1 )  );
        BOOST_CHECK(next_pc_ins->getValueOperandA() == IntegerRegister(CORE_SIZE,0 )  );
        BOOST_CHECK(next_pc_ins->getValueOperandB() == IntegerRegister(CORE_SIZE,1 )  );
    }
}
BOOST_AUTO_TEST_CASE(exec_of_ADD)
{
    //wojownik_1 = instrukcja ADD(1,@1), DAT(#1,#1), DAT(#1,#1)
    //wojownik_2 = instrukcja ADD(1,@1), DAT(#1,#1), DAT(#1,#1)
    //wykonanie tej instrukcji powinno dodac instrukcje DAT(#1, #1) do instrukcji za tą instrukcją DAT (bo drugi argument jest posredni)
    //po wykonaniu ADD warriora 1 w instrukcji o adresie 2 znajdziemy odpowiedz jak sie wykonala instrukcja
    //w przypadku drugiego warriora pod adresem 7
    Operand::OperandPtr op_add_1 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, 1)) );
    Operand::OperandPtr op_add_2 = Operand::OperandPtr(new IndirectOperand(IntegerRegister(CORE_SIZE, 1)) );

    Operand::OperandPtr op_dat_1 = Operand::OperandPtr(new ImmidiateOperand(IntegerRegister(CORE_SIZE, 1)) );
    Operand::OperandPtr op_dat_2 = Operand::OperandPtr(new ImmidiateOperand(IntegerRegister(CORE_SIZE, 1)) );

    Instruction::InsPtr add_ins = Instruction::InsPtr(new ADDInstruction(op_add_1, op_add_2));
    Instruction::InsPtr dat_ins = Instruction::InsPtr(new DATInstruction(op_dat_1, op_dat_2));

    Warrior war_1, war_2;
    war_1.instuctions_.push_back(add_ins->clone() );
    war_1.instuctions_.push_back(dat_ins->clone() );
    war_1.instuctions_.push_back(dat_ins->clone() );

    war_2.instuctions_.push_back(add_ins->clone() );
    war_2.instuctions_.push_back(dat_ins->clone() );
    war_2.instuctions_.push_back(dat_ins->clone() );

    unique_ptr<Observer> moke = unique_ptr<Observer>(new MokeObserver() );
    unique_ptr<CoreCreator> creator = unique_ptr<CoreCreator>(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr core_ptr = creator->createCore(moke);

    //wykonujemy instrukcje ADD
    Instruction::InsPtr exec_add = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 0) );
    ExecutionLog exec_log = exec_add->execute(core_ptr, IntegerRegister(CORE_SIZE, 0) );

    BOOST_CHECK(exec_log.is_proc_live_ == true);
    BOOST_CHECK(exec_log.is_proc_split_== false);
    BOOST_CHECK(exec_log.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 1));
    //teraz instrukcja o adresie 2 powinna byc instrukcją DAT(#2, #2)
    Instruction::InsPtr modified_ins = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 2) );
    BOOST_CHECK(dynamic_cast<DATInstruction*>(modified_ins.get()));
    //cout<<modified_ins->getValueOperandA().getValue()<<endl;
    //cout<<modified_ins->getValueOperandB().getValue()<<endl;

    BOOST_CHECK(modified_ins->getValueOperandA() == IntegerRegister(CORE_SIZE, 2));
    BOOST_CHECK(modified_ins->getValueOperandB() == IntegerRegister(CORE_SIZE, 2));
    //teraz to samo dla warriora_2 - czyli wykonujemy instrukcję o adresie 5, wynik powinniśmy znaleźć pod adresem 7

    Instruction::InsPtr exec_add_2 = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 5) );
    ExecutionLog exec_log_2 = exec_add_2->execute(core_ptr, IntegerRegister(CORE_SIZE, 5) );

    BOOST_CHECK(exec_log_2.is_proc_live_ == true);
    BOOST_CHECK(exec_log_2.is_proc_split_== false);
    BOOST_CHECK(exec_log_2.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 6));
    //teraz instrukcja o adresie 2 powinna byc instrukcją DAT(#2, #2)
    Instruction::InsPtr modified_ins_2 = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 7) );
    BOOST_CHECK(dynamic_cast<DATInstruction*>(modified_ins_2.get()));
    //cout<<modified_ins_2->getValueOperandA().getValue()<<endl;
    //cout<<modified_ins_2->getValueOperandB().getValue()<<endl;

    BOOST_CHECK(modified_ins_2->getValueOperandA() == IntegerRegister(CORE_SIZE, 2));
    BOOST_CHECK(modified_ins_2->getValueOperandB() == IntegerRegister(CORE_SIZE, 2));

}

BOOST_AUTO_TEST_CASE(exec_of_SUB)
{
    Operand::OperandPtr op_sub_1 = Operand::OperandPtr(new DirectOperand(IntegerRegister  (CORE_SIZE, 1)) );
    Operand::OperandPtr op_sub_2 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, 2)) );

    Operand::OperandPtr op_dat_1 = Operand::OperandPtr(new ImmidiateOperand(IntegerRegister(CORE_SIZE, 1)) );
    Operand::OperandPtr op_dat_2 = Operand::OperandPtr(new ImmidiateOperand(IntegerRegister(CORE_SIZE, 1)) );

    Instruction::InsPtr sub_ins = Instruction::InsPtr(new SUBInstruction(op_sub_1, op_sub_2));
    Instruction::InsPtr dat_ins = Instruction::InsPtr(new DATInstruction(op_dat_1, op_dat_2));

    Warrior war_1, war_2;
    war_1.instuctions_.push_back(sub_ins->clone() );
    war_1.instuctions_.push_back(dat_ins->clone() );
  //  war_1.instuctions_.push_back(dat_ins->clone() );

    war_2.instuctions_.push_back(sub_ins->clone() );
    war_2.instuctions_.push_back(dat_ins->clone() );
  //  war_2.instuctions_.push_back(dat_ins->clone() );

    unique_ptr<Observer> moke = unique_ptr<Observer>(new MokeObserver() );
    unique_ptr<CoreCreator> creator = unique_ptr<CoreCreator>(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr core_ptr = creator->createCore(moke);

    //wykonujemy instrukcje SUB na pierwszym wojowniku
    Instruction::InsPtr exec_sub = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 0) );
    ExecutionLog exec_log = exec_sub->execute(core_ptr, IntegerRegister(CORE_SIZE, 0) );

    BOOST_CHECK(exec_log.is_proc_live_ == true);
    BOOST_CHECK(exec_log.is_proc_split_== false);
    BOOST_CHECK(exec_log.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 1));
    //teraz instrukcja o adresie 2 powinna byc instrukcją DAT(#-1, #-1) (lub raczej DAT(#9, #9) )
    Instruction::InsPtr modified_ins = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 2) );
    BOOST_CHECK(dynamic_cast<DATInstruction*>(modified_ins.get()));
    //cout<<modified_ins->getValueOperandA().getValue()<<endl;
    //cout<<modified_ins->getValueOperandB().getValue()<<endl;

    BOOST_CHECK(modified_ins->getValueOperandA() == IntegerRegister(CORE_SIZE, -1));
    BOOST_CHECK(modified_ins->getValueOperandB() == IntegerRegister(CORE_SIZE, -1));
    //teraz to samo dla warriora_2 - czyli wykonujemy instrukcję o adresie 5, wynik powinniśmy znaleźć pod adresem 7

    Instruction::InsPtr exec_sub_2 = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 5) );
    ExecutionLog exec_log_2 = exec_sub_2->execute(core_ptr, IntegerRegister(CORE_SIZE, 5) );

    BOOST_CHECK(exec_log_2.is_proc_live_ == true);
    BOOST_CHECK(exec_log_2.is_proc_split_== false);
    BOOST_CHECK(exec_log_2.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 6));
    //teraz instrukcja o adresie 2 powinna byc instrukcją DAT(#-1, #-1)
    Instruction::InsPtr modified_ins_2 = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 7) );
    BOOST_CHECK(dynamic_cast<DATInstruction*>(modified_ins_2.get()));
  //  cout<<modified_ins_2->getValueOperandA().getValue()<<endl;
//    cout<<modified_ins_2->getValueOperandB().getValue()<<endl;

    BOOST_CHECK(modified_ins_2->getValueOperandA() == IntegerRegister(CORE_SIZE, -1));
    BOOST_CHECK(modified_ins_2->getValueOperandB() == IntegerRegister(CORE_SIZE, -1));

}

BOOST_AUTO_TEST_CASE(exec_of_jmp)
{
    Operand::OperandPtr op_jmp1_1 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, 5)) );
    Operand::OperandPtr op_jmp1_2 = Operand::OperandPtr(new IndirectOperand(IntegerRegister(CORE_SIZE, 1)) );

    Operand::OperandPtr op_jmp2_1 = Operand::OperandPtr(new DirectOperand(IntegerRegister(CORE_SIZE, -5)) );
    Operand::OperandPtr op_jmp2_2 = Operand::OperandPtr(new IndirectDecrementOperand(IntegerRegister(CORE_SIZE, 2)) );

    Instruction::InsPtr jmp1_ins = Instruction::InsPtr(new JMPInstruction(op_jmp1_1, op_jmp1_2));
    Instruction::InsPtr jmp2_ins = Instruction::InsPtr(new JMPInstruction(op_jmp2_1, op_jmp2_2));

    Warrior war_1, war_2;
    war_1.instuctions_.push_back(jmp1_ins->clone() );

    war_2.instuctions_.push_back(jmp2_ins->clone() );

    unique_ptr<Observer> moke = unique_ptr<Observer>(new MokeObserver() );
    unique_ptr<CoreCreator> creator = unique_ptr<CoreCreator>(new DATCreator(CORE_SIZE, war_1, war_2) );
    Core::CorePtr core_ptr = creator->createCore(moke);
//powinny skakać do sb nawzajem
    Instruction::InsPtr exec_jmp = core_ptr->getInstructionCopy(IntegerRegister(CORE_SIZE, 0) );
    ExecutionLog exec_log = exec_jmp->execute(core_ptr, IntegerRegister(CORE_SIZE, 0) );
    BOOST_CHECK(exec_log.is_proc_live_ == true);
    BOOST_CHECK(exec_log.is_proc_split_ == false);
    BOOST_CHECK(exec_log.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 5) );

    Instruction::InsPtr exec_jmp_2 = core_ptr->getInstructionCopy(exec_log.next_pc_current_proc_);
    ExecutionLog exec_log_2 = exec_jmp_2->execute(core_ptr, exec_log.next_pc_current_proc_);
    BOOST_CHECK(exec_log_2.is_proc_live_ == true);
    BOOST_CHECK(exec_log_2.is_proc_split_ == false);
    BOOST_CHECK(exec_log_2.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 0) );

    Instruction::InsPtr exec_jmp_3 = core_ptr->getInstructionCopy(exec_log_2.next_pc_current_proc_);
    ExecutionLog exec_log_3 = exec_jmp_3->execute(core_ptr, exec_log_2.next_pc_current_proc_);
    BOOST_CHECK(exec_log_3.is_proc_live_ == true);
    BOOST_CHECK(exec_log_3.is_proc_split_ == false);
    BOOST_CHECK(exec_log_3.next_pc_current_proc_ == IntegerRegister(CORE_SIZE, 5) );
}





BOOST_AUTO_TEST_SUITE_END()
