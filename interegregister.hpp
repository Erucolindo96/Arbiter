#ifndef INTEREGREGISTER_HPP
#define INTEREGREGISTER_HPP

namespace arbiter
{
/**
 * @brief The InteregRegister class Klasa przechowująca agrumenty instrukcji. Pozwala wykonywać na sobie operacje dodawania i odejmowania modulo rozmiar rdzenia.
 */
class InteregRegister
{
public:
    explicit InteregRegister() = delete;//zabroniony - aby pamietac o zainicjowaniu rozmiaru rdzenia)
    explicit InteregRegister(const IntegerRegister &other);
    explicit IntegerRegister( const unsigned int CORE_SIZE, const int value = 0);

    InteregRegister operator=(const InteregRegister &other);

    InteregRegister operator+(const IntegerRegister &added);
    InteregRegister operator-(const IntegerRegister &added);

    InteregRegister operator++();
    InteregRegister operator++(int);

    InteregRegister operator--();
    InteregRegister operator--(int);


protected:
    const unsigned int CORE_SIZE;
    int value_;
};


}


#endif // INTEREGREGISTER_HPP
