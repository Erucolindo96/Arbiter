#include "Core.hpp"


namespace arbiter
{

//public
    Core::Core(std::unique_ptr<Observer> &obs_ptr):core_memory_(), mutex_(), observer_ptr_(obs_ptr)
    {}

//    Core::Core(const Core &other): core_memory_(other.core_memory_), mutex_(), observer_ptr_(other.observer_ptr_)
  //  {}

//    Core::Core(std::vector<InsSharedPtr> &&memory_of_core):core_memory_(std::move(memory_of_core)), mutex_(), observer_ptr_()
//    {}

    //moze być kłopotliwy gdy dwa wątki jednocześnie będa przypisywać rdzenie do siebie(1.wątek this==other, 2.wątek other==this)
    //spowoduje to najprawdopoboniej zakleszczenie
/*    Core& Core::operator =(const Core &other)
    {

        std::lock_guard<std::mutex> this_lock(mutex_);

        if(this == &other)
            return *this;

        std::lock_guard<std::mutex> other_lock(other.mutex_);

        core_memory_ = other.core_memory_;
        //observer_ref_ = other.observer_ref_;
        return *this;

    }
*/
    void Core::modifyInstruction(const IntegerRegister address_of_ins, InsPtr new_ins)
    {
        InsPtr &ins_ref = getInstructionRef(address_of_ins);
        ins_ref = std::move(new_ins);

        //notifyObserver();
    }


    Core::InsPtr Core::getInstructionCopy(const IntegerRegister address_of_ins)const
    {
        InsPtr &ref = getInstructionRef(address_of_ins);
        return ref->clone();
    }


    unsigned int Core::getCoreSize()const
    {

        return core_memory_.size();
    }

//private

    Core::InsPtr& Core::getInstructionRef(const IntegerRegister address_of_ins)const
    {
        //jesli IntegerRegister nie ma takiego samego rozmiaru jak rdzen
        if(address_of_ins.getSize() != getCoreSize())
            throw std::invalid_argument("Core::getInstructionPtr : address_of_ins have other CORE_SIZE than real core size");

        return const_cast<Core::InsPtr&> ( core_memory_.at(address_of_ins.getValue() ) ) ;
    }

    void Core::notifyObserver(const IntegerRegister &modified_ins)
    {
        observer_ptr_->update(modified_ins);
    }



}
