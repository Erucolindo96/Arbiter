#ifndef INTEGERREGISTER_HPP
#define INTEGERREGISTER_HPP

#include<stdexcept>


/**
UWAGA : Być może zajdzie potrzeba przerobić ta klasę tak, aby mogła przechowywać równiez liczby ujemne modulo rozmiar rdzenia.
*/



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
    IntegerRegister(const IntegerRegister &&other);

    IntegerRegister& operator=(const IntegerRegister &other);
    IntegerRegister& operator=(const IntegerRegister &&other);

    unsigned int getValue()const;
    void setValue(const int value);

    unsigned int getSize()const;

    IntegerRegister operator+(const IntegerRegister &added)const;
    IntegerRegister operator-(const IntegerRegister &added)const;

    IntegerRegister operator++();
    IntegerRegister operator++(int);

    IntegerRegister operator--();
    IntegerRegister operator--(int);

    bool operator==(const IntegerRegister &other)const;
    bool operator!=(const IntegerRegister &other)const;

protected:
    const unsigned int CORE_SIZE_;
    int value_;

    IntegerRegister() = delete ;//zabroniony - aby pamietac o zainicjowaniu rozmiaru rdzenia)

    void checkArgument(const IntegerRegister &other)const;//sprawdza czy rejestry maja taki sam CORE_SIZE. Rzuca wyjątek std::invalidArgument
};


}


#endif // INTEGERREGISTER_HPP
