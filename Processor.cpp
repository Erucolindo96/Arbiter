#include "Processor.hpp"

namespace arbiter
{

   // Processor::Processor(const int CORE_SIZE):core_ptr_(), loaded_instruction_(), exec_log_(), actual_proc_(CORE_SIZE)
   // {}

    Processor::Processor(CorePtr &core, const unsigned int CORE_SIZE): core_ptr_(core), loaded_instruction_(), exec_log_(IntegerRegister(CORE_SIZE), IntegerRegister(CORE_SIZE), true, false )//, actual_proc_(core->getCoreSize())
    {}


    Processor::CorePtr& Processor::getCorePtr()const
    {
        return core_ptr_;
    }


    ExecutionLog Processor::executeProcess(const Process &proc)
    {
        loadInstruction(proc);
        return loaded_instruction_->execute(core_ptr_, proc.getProcPc());
    }

    void Processor::loadInstruction(const Process &proc)
    {
        loaded_instruction_ = core_ptr_->getInstructionCopy(proc.getProcPc());
    }



}

