#ifndef INTEGERREGISTER_HPP
#define INTEGERREGISTER_HPP

#include<stdexcept>

namespace arbiter
{
/**
 * @brief The InteregRegister class Klasa przechowująca agrumenty instrukcji. Pozwala wykonywać na sobie operacje dodawania i odejmowania modulo rozmiar rdzenia.
 */
class IntegerRegister
{
public:
    IntegerRegister(const IntegerRegister &other);
    explicit IntegerRegister( const unsigned int CORE_SIZE, const int value = 0);

    IntegerRegister& operator=(const IntegerRegister &other);

    IntegerRegister operator+(const IntegerRegister &added);
    IntegerRegister operator-(const IntegerRegister &added);

    IntegerRegister operator++();
    IntegerRegister operator++(int);

    IntegerRegister operator--();
    IntegerRegister operator--(int);


protected:
    const unsigned int CORE_SIZE_;
    int value_;

    IntegerRegister() = delete ;//zabroniony - aby pamietac o zainicjowaniu rozmiaru rdzenia)

    void checkArgument(const IntegerRegister &other);//sprawdza czy rejestry maja taki sam CORE_SIZE. Rzuca wyjątek std::invalidArgument
};


}


#endif // INTEGERREGISTER_HPP
