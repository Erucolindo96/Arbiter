#include "Core.hpp"


namespace arbiter
{

//public
    Core::Core():core_memory_(), mutex_(), observer_ptr_()
    {}

    Core::Core(const Core &other): core_memory_(other.core_memory_), mutex_(), observer_ptr_(other.observer_ptr_)
    {}

    Core::Core(std::vector<InsSharedPtr> &&memory_of_core):core_memory_(std::move(memory_of_core)), mutex_(), observer_ptr_()
    {}

    //moze być kłopotliwy gdy dwa wątki jednocześnie będa przypisywać rdzenie do siebie(1.wątek this==other, 2.wątek other==this)
    //spowoduje to najprawdopoboniej zakleszczenie
    Core& Core::operator =(const Core &other)
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        if(this == &other)
            return *this;

        std::lock_guard<std::mutex> other_lock(other.mutex_);

        core_memory_ = other.core_memory_;
        observer_ptr_ = other.observer_ptr_;
        return *this;

    }

    void Core::modifyInstruction(const IntegerRegister address_of_ins, InsPtr new_ins)
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        InsSharedPtr temp_ptr = getInstructionPtr(address_of_ins);
        temp_ptr = std::move(new_ins);//nie wiem czy to sie zachowa poprawnie - i czy nie bedzie tu wyciekow

        notifyObserver();
    }

    Core::InsPtr Core::getInstructionCopy(const IntegerRegister address_of_ins)const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        InsSharedPtr temp = getInstructionPtr(address_of_ins);
        return temp->clone();
    }


    unsigned int Core::getCoreSize()const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        return core_memory_.size();
    }

//private

    Core::InsSharedPtr Core::getInstructionPtr(const IntegerRegister address_of_ins)const
    {
        std::lock_guard<std::mutex> this_lock(mutex_);

        //jesli IntegerRegister nie ma takiego samego rozmiaru jak rdzen
        if(address_of_ins.getSize() != getCoreSize())
            throw std::invalid_argument("Core::getInstructionPtr : address_of_ins have other CORE_SIZE than real core size");

        return core_memory_[address_of_ins.getValue()];
    }

    void Core::notifyObserver()
    {
        observer_ptr_->update();
    }



}
