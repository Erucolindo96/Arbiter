#include "Process.hpp"



namespace arbiter
{
    Process::Process(const unsigned int CORE_SIZE):proc_PC_(CORE_SIZE, 0)
    {}

    Process::Process(const IntegerRegister &proc_pc):proc_PC_(proc_pc)
    {}

    Process::Process(const Process &other): proc_PC_(other.proc_PC_)
    {}

    Process& Process::operator =(const Process &other)
    {
        if(this==&other)
            return *this;

        proc_PC_ = other.proc_PC_;
        return *this;
    }

    IntegerRegister Process::getProcPc()const
    {
        return proc_PC_;
    }

    IntegerRegister Process::updateProcPC(IntegerRegister next_pc)
    {
        proc_PC_ = next_pc;
        return proc_PC_;
    }

    IntegerRegister Process::incrementPC()
    {
        return ++proc_PC_;
    }


}
