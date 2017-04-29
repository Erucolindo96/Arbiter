#include "Operand.hpp"
namespace arbiter
{

    typedef std::shared_ptr<Core> CorePtr;

    //public
    Operand::Operand(CorePtr core, int value ): core_(core), value_(value)
    {}

    Operand::Operand(const Operand& other): core_(other.core_), value_(other.value_)
    {}

    Operand::Operand(const Operand &&other): core_(other.core_), value_(other.value_)
    {}

    Operand& Operand::operator=(const Operand& other)
    {
        if(this == &other)
            return *this;

        //chechCorePtr(other);
        core_ = other.core_;
        value_ = other.value_;
        return *this;
    }

    Operand& Operand::operator=(const Operand &&other)
    {
        if(this == &other)
            return *this;

        //chechCorePtr(other);
        core_ = other.core_;
        value_ = other.value_;
        return *this;
    }

    int Operand::getValue()const
    {
        return value_;
    }

    void Operand::setValue(int value)
    {
        value_ = value;
    }


    CorePtr Operand::getCorePtr()const
    {
        return core_;
    }

    void Operand::setCorePtr(const CorePtr ptr)
    {
        core_ = ptr;
    }



    //protected

    void Operand::chechCorePtr(const Operand &other)const
    {
        if(other.core_ != core_)
            throw std::invalid_argument("Arbiter::Operand::chechCorePtr - Core pointers not equal\n");
    }

}
