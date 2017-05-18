#include"RealInstructions.hpp"


namespace arbiter
{

//DAT

    DATInstruction::DATInstruction():Instruction()
    {}

    DATInstruction::DATInstruction(const OperandPtr& operand_A, const OperandPtr& operand_B): Instruction(operand_A, operand_B)
    {}

    DATInstruction::DATInstruction(const DATInstruction& other):Instruction(other)
    {}

    DATInstruction& DATInstruction::operator =(const DATInstruction& other)
    {
        Instruction::operator =(other) ;
        return *this;
    }


    ExecutionLog DATInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        return ExecutionLog(next_pc, false, false);
    }

    Instruction::InsPtr DATInstruction::clone()const
    {
        return Instruction::InsPtr(new DATInstruction(*this) );
    }

    DATInstruction::~DATInstruction()
    {}

//MOV

    MOVInstruction::MOVInstruction():Instruction()
    {}

    MOVInstruction::MOVInstruction(const MOVInstruction &other):Instruction(other)
    {}
    MOVInstruction::MOVInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    MOVInstruction& MOVInstruction::operator =(const MOVInstruction &other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog MOVInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        if(dynamic_cast<ImmidiateOperand*>(operand_A_.get()) )//jesli argumentA jest natychmiastowy
        {//wstawiamy wartosc argumentu natychmiastowego do komorki spod adresu operandu B
            IntegerRegister destination_address = operandB()->countArgument(core, instruction_PC);
            Core::InsPtr &destination_ins  = core->getInstructionRef(destination_address);
            destination_ins->getOperandBRef()->setValue( operand_A_->getValue() );//przenosimy wartosc argumentu A do pola B komorki wskazywanej przez nasz argument B
            //uwaga - ta wersja nie informuje obserwatora o modyfikacji rdzenia
        }
        else//przenosimy całą komorke
        {
            IntegerRegister source_address = operand_A_->countArgument(core, instruction_PC);//szukamy komorki ktora bedziemy kopiować
            Core::InsPtr clone_source = core->getInstructionCopy(source_address);
            IntegerRegister destination_address = operand_B_->countArgument(core, instruction_PC);//szukamy komórki którą zmienimy
            core->modifyInstruction(destination_address, std::move(clone_source));//zapisujemy komorke pod znaleziony adres
        }
        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr MOVInstruction::clone()const
    {
        return Instruction::InsPtr(new MOVInstruction(*this) );
    }

    MOVInstruction::~MOVInstruction()
    {}


    //ADD
    ADDInstruction::ADDInstruction(): Instruction()
    {}

    ADDInstruction::ADDInstruction(const ADDInstruction &other): Instruction(other)
    {}

    ADDInstruction::ADDInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B): Instruction(operand_A, operand_B)
    {}

    ADDInstruction& ADDInstruction::operator=(const ADDInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog ADDInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        if(dynamic_cast<ImmidiateOperand*>(operand_A_.get()) )//jesli argumentA jest natychmiastowy
        {
            //dodajemy wartosc atego argumentu do pola B komorki wskazywanej przez argument B
            IntegerRegister destination_address = operandB()->countArgument(core, instruction_PC);
            Core::InsPtr &destination_ins  = core->getInstructionRef(destination_address);
            destination_ins->getOperandBRef()->addValue( operand_A_->getValue() );
            //uwaga - ta wersja nie informuje obserwatora o modyfikacji rdzenia
        }
        else//dodajemy pola A i B komorki wskazywanej przez A do pół A i B komórki wskazywanej przez B
        {
            IntegerRegister source_address = operand_A_->countArgument(core, instruction_PC);
            Core::InsPtr &source = core->getInstructionRef(source_address);

            IntegerRegister destination_address = operand_B_->countArgument(core, instruction_PC);
            Core::InsPtr &destination = core->getInstructionRef(destination_address);

            destination->getOperandARef()->addValue( source->getValueOperandA() );//dodajemy odpowiednie operandy zrodlowe do odpowiednich operandow docelowych
            destination->getOperandBRef()->addValue( source->getValueOperandB() );
        }
        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr ADDInstruction::clone()const
    {
        return Instruction::InsPtr(new ADDInstruction(*this));
    }

    ADDInstruction::~ADDInstruction()
    {}

    //SUB

    SUBInstruction::SUBInstruction():Instruction()
    {}

    SUBInstruction::SUBInstruction(const SUBInstruction &other):Instruction(other)
    {}

    SUBInstruction::SUBInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    SUBInstruction& SUBInstruction::operator=(const SUBInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog SUBInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        if(dynamic_cast<ImmidiateOperand*>(operand_A_.get()) )//jesli argumentA jest natychmiastowy
        {
            //odejmujemy od pola B komorki docelowej wartosc natychmiastowego operandu A
            IntegerRegister destination_address = operandB()->countArgument(core, instruction_PC);
            Core::InsPtr &destination_ins  = core->getInstructionRef(destination_address);
            destination_ins->getOperandBRef()->subValue( operand_A_->getValue() );
            //uwaga - ta wersja nie informuje obserwatora o modyfikacji rdzenia
        }
        else//odejmujemy od pola A i B komorki wskazywanej przez operand B pola A i B komorki wskazywanej przez operand A
        {
            IntegerRegister source_address = operand_A_->countArgument(core, instruction_PC);
            Core::InsPtr &source = core->getInstructionRef(source_address);

            IntegerRegister destination_address = operand_B_->countArgument(core, instruction_PC);
            Core::InsPtr &destination = core->getInstructionRef(destination_address);

            destination->getOperandARef()->subValue( source->getValueOperandA() );//odejmujemy odpowiednie operandy zrodlowe od odpowiednich operandow docelowych
            destination->getOperandBRef()->subValue( source->getValueOperandB() );
        }
        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr SUBInstruction::clone()const
    {
        return Instruction::InsPtr(new SUBInstruction(*this));
    }

    SUBInstruction::~SUBInstruction()
    {}

    //JMP

    JMPInstruction::JMPInstruction():Instruction()
    {}

    JMPInstruction::JMPInstruction(const JMPInstruction &other):Instruction(other)
    {}

    JMPInstruction::JMPInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    JMPInstruction& JMPInstruction::operator=(const JMPInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog JMPInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister next_pc = operand_A_->countArgument(core, instruction_PC);
        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr JMPInstruction::clone()const
    {
        return Instruction::InsPtr(new JMPInstruction(*this) );
    }

    JMPInstruction::~JMPInstruction()
    {}


    //JMZ
    JMZInstruction::JMZInstruction():Instruction()
    {}
    JMZInstruction::JMZInstruction(const JMZInstruction &other):Instruction(other)
    {}

    JMZInstruction::JMZInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    JMZInstruction& JMZInstruction::operator=(const JMZInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog JMZInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister conditional_value(core->getCoreSize() );//wartość, która jeśli będzie wynosić zero to nastąpi skok
        const IntegerRegister ZERO(core->getCoreSize(), 0);

        if(dynamic_cast<ImmidiateOperand*>(operand_B_.get() ) )
        {
            conditional_value = operand_B_->getValue();
        }
        else
        {
            IntegerRegister arg_ptr = operand_B_->countArgument(core, instruction_PC);//wyliczmay adres
            Core::InsPtr &ins_arg = core->getInstructionRef(arg_ptr);
            conditional_value = ins_arg->getValueOperandB();//i pobieramy spod wyliczonego adresu
        }

        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        if(conditional_value == ZERO)//jeśli wyliczony argument B jest równy 0 - skaczemu pod adres z operandu A
        {
            next_pc = operand_A_->countArgument(core, instruction_PC);
        }

        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr JMZInstruction::clone()const
    {
        return Instruction::InsPtr(new JMZInstruction(*this) );
    }

    JMZInstruction::~JMZInstruction()
    {}

//JMN

    JMNInstruction::JMNInstruction():Instruction()
    {}

    JMNInstruction::JMNInstruction(const JMNInstruction &other):Instruction(other)
    {}

    JMNInstruction::JMNInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    JMNInstruction& JMNInstruction::operator=(const JMNInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog JMNInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister conditional_value(core->getCoreSize() );//wartość, która jeśli będzie wynosić zero to nastąpi skok
        const IntegerRegister ZERO(core->getCoreSize(), 0);

        if(dynamic_cast<ImmidiateOperand*>(operand_B_.get() ) )
        {
            conditional_value = operand_B_->getValue();
        }
        else
        {
            IntegerRegister arg_ptr = operand_B_->countArgument(core, instruction_PC);//wyliczmay adres
            Core::InsPtr &ins_arg = core->getInstructionRef(arg_ptr);
            conditional_value = ins_arg->getValueOperandB();//i pobieramy spod wyliczonego adresu
        }

        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        if(conditional_value != ZERO)//jeśli wyliczony argument B jest różny od 0 - skaczemu pod adres z operandu A
        {
            next_pc = operand_A_->countArgument(core, instruction_PC);
        }

        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr JMNInstruction::clone()const
    {
        return Instruction::InsPtr(new JMNInstruction(*this) );
    }

    JMNInstruction::~JMNInstruction()
    {}

    //DJN

    DJNInstruction::DJNInstruction():Instruction()
    {}

    DJNInstruction::DJNInstruction(const DJNInstruction &other):Instruction(other)
    {}

    DJNInstruction::DJNInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    DJNInstruction& DJNInstruction::operator=(const DJNInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog DJNInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister conditional_value(core->getCoreSize() );//wartość, która jeśli będzie różna od zera to nastąpi skok
        const IntegerRegister ZERO(core->getCoreSize(), 0 );
        const IntegerRegister ONE(core->getCoreSize(),  1 );

        if(dynamic_cast<ImmidiateOperand*>(operand_B_.get() ) )
        {
            operand_B_->subValue(ONE);//dekrementujemy operand B
            conditional_value = operand_B_->getValue();//czytamy warunek skoku
        }
        else
        {
            IntegerRegister arg_ptr = operand_B_->countArgument(core, instruction_PC);//wyliczmay adres
            Core::InsPtr &ins_arg = core->getInstructionRef(arg_ptr);
            ins_arg->getOperandBRef()->subValue(ONE);//dekrementujemy operand B
            conditional_value = ins_arg->getValueOperandB();//i czytamy warunek skoku
        }

        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        if(conditional_value != ZERO)//jeśli wyliczony argument B jest różny od 0 - skaczemu pod adres z operandu A
        {
            next_pc = operand_A_->countArgument(core, instruction_PC);
        }

        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr DJNInstruction::clone()const
    {
        return Instruction::InsPtr(new DJNInstruction(*this) );
    }

    DJNInstruction::~DJNInstruction()
    {}

    //CMP - compare, skip if equal

    CMPInstruction::CMPInstruction():Instruction()
    {}

    CMPInstruction::CMPInstruction(const CMPInstruction &other):Instruction(other)
    {}

    CMPInstruction::CMPInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B):Instruction(operand_A, operand_B)
    {}

    CMPInstruction& CMPInstruction::operator=(const CMPInstruction& other)
    {
        Instruction::operator =(other);
        return *this;
    }

    ExecutionLog CMPInstruction::execute(CorePtr &core, const IntegerRegister &instruction_PC)
    {
        IntegerRegister conditional_value(core->getCoreSize() );//wartość, która jeśli będzie wynosić zero to nastąpi skok
        const IntegerRegister ZERO(core->getCoreSize(), 0);

        if(dynamic_cast<ImmidiateOperand*>(operand_B_.get() ) )
        {
            conditional_value = operand_B_->getValue();
        }
        else
        {
            IntegerRegister arg_ptr = operand_B_->countArgument(core, instruction_PC);//wyliczmay adres
            Core::InsPtr &ins_arg = core->getInstructionRef(arg_ptr);
            conditional_value = ins_arg->getValueOperandB();//i pobieramy spod wyliczonego adresu
        }

        IntegerRegister next_pc = instruction_PC;
        ++next_pc;
        if(conditional_value != ZERO)//jeśli wyliczony argument B jest różny od 0 - skaczemu pod adres z operandu A
        {
            next_pc = operand_A_->countArgument(core, instruction_PC);
        }

        return ExecutionLog(next_pc, true, false);
    }

    Instruction::InsPtr CMPInstruction::clone()const
    {
        return Instruction::InsPtr(new CMPInstruction(*this) );
    }

    CMPInstruction::~CMPInstruction()
    {}

}
