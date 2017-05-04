#include "IntegerRegister.hpp"



namespace arbiter
{


 IntegerRegister::IntegerRegister(const IntegerRegister &other): CORE_SIZE_(other.CORE_SIZE_), value_(other.value_)
{}

 IntegerRegister::IntegerRegister( const unsigned int CORE_SIZE, const int value ): CORE_SIZE_(CORE_SIZE), value_(value)
{}


IntegerRegister& IntegerRegister::operator=(const IntegerRegister &other)
{
    checkArgument(other);

    if(this == &other)
        return *this;

    value_ = other.value_;
    return *this;
}

int IntegerRegister::getValue()const
{
    return value_;
}

void IntegerRegister::setValue(const int value)
{
    value_ = value;
}

unsigned int IntegerRegister::getSize()const
{
    return CORE_SIZE_;
}

IntegerRegister IntegerRegister::operator+(const IntegerRegister &added)
{
    checkArgument(added);
    return IntegerRegister(CORE_SIZE_, (value_+ added.value_)%CORE_SIZE_);
}

IntegerRegister IntegerRegister::operator-(const IntegerRegister &added)
{
    checkArgument(added);
    return IntegerRegister(CORE_SIZE_, (value_- added.value_)%CORE_SIZE_ );

}

IntegerRegister IntegerRegister::operator++()
{
    return IntegerRegister(CORE_SIZE_, (value_+1)%CORE_SIZE_);
}

IntegerRegister IntegerRegister::operator++(int)
{
    IntegerRegister prev = *this;
    operator++();
    return prev;
}

IntegerRegister IntegerRegister::operator--()
{
    return IntegerRegister(CORE_SIZE_, (value_-1)%CORE_SIZE_);
}

IntegerRegister IntegerRegister::operator--(int)
{
    IntegerRegister prev = *this;
    operator--();
    return prev;
}


void IntegerRegister::checkArgument(const IntegerRegister &other)
{
    if(CORE_SIZE_ != other.CORE_SIZE_)
        throw std::invalid_argument("IntegerRegister: Comparision, Adding or Subtracting beetwen registers with another Core sizes");
}



}
