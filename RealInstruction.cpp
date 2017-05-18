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

        }
        else
        {

        }
    }

    Instruction::InsPtr MOVInstruction::clone()const
    {
        return Instruction::InsPtr(new MOVInstruction(*this) );
    }

    MOVInstruction::~MOVInstruction()
    {}
}
