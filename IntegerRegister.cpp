#include "IntegerRegister.hpp"



namespace arbiter
{

int getModulo(const int MODULE, int value)
{
    //operator % dziwnie działa dla liczb ujemnych, powinien dawac dodatni adres komorki pamieci pomniejszonej o value
    //dlatego robimy to ręcznie

    if(value >= 0)
    {
        return value%MODULE;
    }
    else
    {
        while(value < 0)
        {
            value+=MODULE;//poczatkowo jest tam value, teraz zwiekszamy dopoki nie dostaniemy dodatniej liczby - i to bdzie nasz wynik
        }
        return value;
    }
}

 IntegerRegister::IntegerRegister(const IntegerRegister &other): CORE_SIZE_(other.CORE_SIZE_), value_(other.value_)
{}

 IntegerRegister::IntegerRegister(const IntegerRegister &&other):CORE_SIZE_(other.CORE_SIZE_), value_(other.value_)
 {}

 IntegerRegister::IntegerRegister( const unsigned int CORE_SIZE, const int value ): CORE_SIZE_(CORE_SIZE), value_()
{
    //operator % dziwnie działa dla liczb ujemnych, powinien dawac dodatni adres komorki pamieci pomniejszonej o value
    //dlatego robimy to ręcznie

    value_ = getModulo(CORE_SIZE_, value);
}


IntegerRegister& IntegerRegister::operator=(const IntegerRegister &other)
{
    checkArgument(other);

    if(this == &other)
        return *this;

    value_ = other.value_;
    return *this;
}

IntegerRegister& IntegerRegister::operator=(const IntegerRegister &&other)
{

    checkArgument(other);
    if(this == &other)
        return *this;

    value_ = other.value_;
    return *this;
}


unsigned int IntegerRegister::getValue()const
{
    return value_;
}

void IntegerRegister::setValue(const int value)
{
    value_ = getModulo(CORE_SIZE_, value);

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
    return IntegerRegister(CORE_SIZE_, getModulo(CORE_SIZE_, value_ - added.value_) );

}

IntegerRegister IntegerRegister::operator++()
{
    ++value_;
    value_ = value_%CORE_SIZE_;
    return *this;
}

IntegerRegister IntegerRegister::operator++(int)
{
    IntegerRegister prev = *this;
    operator++();
    return prev;
}

IntegerRegister IntegerRegister::operator--()
{
    --value_;
    value_ = getModulo(CORE_SIZE_, value_);
    return *this;
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
