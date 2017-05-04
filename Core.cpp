#include "Core.hpp"


namespace arbiter
{


    Core::Core():core_memory_(), mutex_()
    {}

    Core::Core(const Core &other): core_memory_(other.core_memory_), mutex_()
    {}

    Core::Core(std::vector<InsSharedPtr> &&memory_of_core):core_memory_(std::move(memory_of_core)), mutex_()
    {}

    Core& Core::operator =(const Core &other)
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        if(this == &other)
            return *this;

        std::lock_guard<std::mutex> other_lock(other.mutex_);

        core_memory_ = other.core_memory_;

        return *this;

    }


    Core::InsSharedPtr Core::getInstructionPtr(const IntegerRegister address_of_ins)const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        //jesli IntegerRegister nie ma takiego samego rozmiaru jak rdzen
        if(address_of_ins.getSize() != getCoreSize())
            throw std::invalid_argument("Core::getInstructionPtr : address_of_ins have other CORE_SIZE than real core size");

        return core_memory_[address_of_ins.getValue()];
    }

    void Core::modifyInstruction(const IntegerRegister address_of_ins, InsPtr new_ins)
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        InsSharedPtr temp_ptr = getInstructionPtr(address_of_ins);
        temp_ptr = std::move(new_ins);//nie wiem czy to sie zachowa poprawnie - i czy nie bedzie tu wyciekow
    }

    Core::InsPtr Core::getInstructionCopy(const IntegerRegister address_of_ins)const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        InsSharedPtr temp = getInstructionPtr(address_of_ins);
        return temp->clone();
    }

    Core::InsSharedPtr Core::operator[](const IntegerRegister address_of_ins)
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        return getInstructionPtr(address_of_ins);
    }

    unsigned int Core::getCoreSize()const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        return core_memory_.size();
    }


}
