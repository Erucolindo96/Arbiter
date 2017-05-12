#include "Processor.hpp"

namespace arbiter
{

   // Processor::Processor(const int CORE_SIZE):core_ptr_(), loaded_instruction_(), exec_log_(), actual_proc_(CORE_SIZE)
   // {}

    Processor::Processor(CorePtr core): core_ptr_(core), loaded_instruction_(), exec_log_(IntegerRegister(core->getCoreSize()), true, false ), actual_proc_(core->getCoreSize())
    {}


    Processor::CorePtr Processor::getCorePtr()const
    {
        return core_ptr_;
    }


    ExecutionLog Processor::executeProcess(const Process &proc)
    {
        throw std::runtime_error("TODO");
    }

    void Processor::loadInstruction()
    {
        throw std::runtime_error("TODO");
    }



}

