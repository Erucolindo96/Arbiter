#include"RealInstructions.hpp"


namespace arbiter
{



    DATInstruction::DATInstruction():Instruction()
    {}

    DATInstruction::DATInstruction(const OperandPtr& operand_A, const OperandPtr& operand_B): Instruction(operand_A, operand_B)
    {}

    DATInstruction::DATInstruction(const DATInstruction& other):Instruction(other)
    {}

    DATInstruction& DATInstruction::operator =(const DATInstruction& other)
    {
        //Instruction& ins_ref = Instruction::operator =(other);
        //return static_cast<DATInstruction&>(ins_ref);//static_cast<const Instruction&>(other) );
        Instruction::operator =(other) ;
        return *this;
    }


    ExecutionLog DATInstruction::execute(CorePtr core)
    {
        throw std::runtime_error("TODO");
    }

    Instruction::InsPtr DATInstruction::clone()const
    {
        return Instruction::InsPtr(new DATInstruction(*this) );
    }

    DATInstruction::~DATInstruction()
    {}
}
