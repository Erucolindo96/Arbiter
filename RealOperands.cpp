#include"RealOperands.hpp"

namespace arbiter
{

    ImmidiateOperand::ImmidiateOperand(const ImmidiateOperand& other): Operand(other)
    {}

    ImmidiateOperand::ImmidiateOperand(const IntegerRegister &value): Operand(value)
    {}

    ImmidiateOperand::ImmidiateOperand(const ImmidiateOperand &&other): Operand(other)
    {}


    Operand::OperandPtr ImmidiateOperand::clone()const
    {
        return Operand::OperandPtr(new ImmidiateOperand(*this) );
    }

    IntegerRegister ImmidiateOperand::countArgument(CorePtr &core,const IntegerRegister &instruction_PC)const
    {
        return instruction_PC;//jest natychmiastowy, wiec zwraca adres swojej instrukcji
    }

    //direct

    DirectOperand::DirectOperand(const DirectOperand &other):Operand(other)
    {}
    DirectOperand::DirectOperand(const IntegerRegister &value):Operand(value)
    {}
    DirectOperand::DirectOperand(const DirectOperand &&other):Operand(other)
    {}


    Operand::OperandPtr DirectOperand::clone()const
    {
        return Operand::OperandPtr(new DirectOperand(*this));
    }

    IntegerRegister DirectOperand::countArgument(CorePtr &core,const IntegerRegister &instruction_PC )const
    {
        //wydaje mi sie, że wartością argumentu bezpośredniego jest wartość operandu B komorki pamieci wskazywanej przez argument
       // Core::InsPtr &ins_ref = core->getInstructionRef(value_+ instruction_PC);//bierzemy komorke spod adresu, będącego wartościa operandu
       // return ins_ref->getValueOperandB();//i zwracamy wartosc operandu B

        //to powinno byc inaczej - wartosc operandu sumujemy z wartoscią PC isntruckji i zwracamy
        return value_ + instruction_PC;
    }

    //indirect

    IndirectOperand::IndirectOperand(const IndirectOperand &other):Operand(other)
    {}
    IndirectOperand::IndirectOperand(const IntegerRegister &value):Operand(value)
    {}
    IndirectOperand::IndirectOperand(const IndirectOperand &&other):Operand(other)
    {}

    Operand::OperandPtr IndirectOperand::clone()const
    {
        return Operand::OperandPtr(new IndirectOperand(*this));
    }
    IntegerRegister IndirectOperand::countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const
    {
        /*
        IntegerRegister ptr_arg = value_ +instruction_PC;//liczymy adres posredniej instrukcji
        Core::InsPtr &ins_indirect_ref = core->getInstructionRef(ptr_arg);//ladujemy ją
        ptr_arg = ptr_arg + ins_indirect_ref->getValueOperandB();//dodajemy do jej adresu wartosc jej pola argumentu B
        Core::InsPtr &ins_destination = core->getInstructionRef(ptr_arg);//czytamy instrukcje z wlasciwym argumentem
        return ins_destination->getValueOperandB();//i zwracamy odczytana wartosc argumentu
        */
        //to powinno byc inaczej - wartosc argumentu wskazuje nam na komorke która zawiera wartosc argumentu - do ktorej trzeba dodac jej PC
        IntegerRegister ptr_arg = value_ + instruction_PC;//liczymy adres posredniej instrukcji
        Core::InsPtr &ins_indirect_ref = core->getInstructionRef(ptr_arg);//ladujemy ją
        ptr_arg = ptr_arg + ins_indirect_ref->getValueOperandB();//dodajemy jej wartosc pola B do jej adresu (czyli nasza wartość operandu+ nasze PC)
        return ptr_arg;//i zwracamy to

    }

    //indirect decrement
    IndirectDecrementOperand::IndirectDecrementOperand(const IndirectDecrementOperand &other):Operand(other)
    {}
    IndirectDecrementOperand::IndirectDecrementOperand(const IntegerRegister &value): Operand(value)
    {}
    IndirectDecrementOperand::IndirectDecrementOperand(const IndirectDecrementOperand &&other):Operand(other)
    {}

    Operand::OperandPtr IndirectDecrementOperand::clone()const
    {
        return Operand::OperandPtr(new IndirectDecrementOperand(*this));
    }
    IntegerRegister IndirectDecrementOperand::countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const
    {/*
        IntegerRegister arg_ptr = value_ + instruction_PC;//liczymy adres posrednniej isntrukcji
        Core::InsPtr &ins_indirect = core->getInstructionRef(arg_ptr);//ładujemy instrukcję pośrednią

        //dekrementujemy wartosc argumentu B instrukcji posredniej
        OperandPtr& dec_op = ins_indirect->getOperandBRef();
        dec_op->setValue( --dec_op->getValue() );

        arg_ptr = arg_ptr + ins_indirect->getValueOperandB();//pobieramy z niej wartosc jej argumentu B
        //--arg_ptr;//i zmiejszamy go
        Core::InsPtr &ins_destination = core->getInstructionRef(arg_ptr);//ładujemy właściwą instrukcję
        return ins_destination->getValueOperandB();//i zwracamy poszukiwany argument
    */
        //to chyba powinno byc inaczej - ze liczymy jak jakby to byl posredni, tylko przed pobraniem argumentu zmniejszamy go o 1
        IntegerRegister arg_ptr = value_ + instruction_PC;//liczymy adres posrednniej isntrukcji
        Core::InsPtr &ins_indirect = core->getInstructionRef(arg_ptr);//ładujemy instrukcję pośrednią

        //dekrementujemy wartosc argumentu B instrukcji posredniej
        OperandPtr& dec_op = ins_indirect->getOperandBRef();
        dec_op->setValue( --dec_op->getValue() );
        arg_ptr = arg_ptr + ins_indirect->getValueOperandB();//pobieramy z niej wartosc jej argumentu B
        return arg_ptr;//i zwracamy
    }

    //IndirectIncrementOperand
    IndirectIncrementOperand::IndirectIncrementOperand(const IndirectIncrementOperand &other):Operand(other)
    {}
    IndirectIncrementOperand::IndirectIncrementOperand(const IntegerRegister &value):Operand(value)
    {}
    IndirectIncrementOperand::IndirectIncrementOperand(const IndirectIncrementOperand &&other):Operand(other)
    {}

    Operand::OperandPtr IndirectIncrementOperand::clone()const
    {
        return Operand::OperandPtr(new IndirectIncrementOperand(*this));
    }
    IntegerRegister IndirectIncrementOperand::countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const
    {
        throw std::runtime_error("TODO");
/*
        IntegerRegister arg_ptr = value_ + instruction_PC;//liczymy adres posrednniej isntrukcji
        Core::InsPtr &ins_indirect = core->getInstructionRef(arg_ptr);//ładujemy instrukcję pośrednią
        arg_ptr = arg_ptr + ins_indirect->getValueOperandB();//pobieramy z niej wartosc jej argumentu B
        ++arg_ptr;//i Zwiekszamy go
        Core::InsPtr &ins_destination = core->getInstructionRef(arg_ptr);//ładujemy właściwą instrukcję
        return ins_destination->getValueOperandB();//i zwracamy poszukiwany argument
*/
    }

}


