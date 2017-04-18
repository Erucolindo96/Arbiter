#ifndef OPERAND_HPP
#define OPERAND_HPP


namespace arbiter
{


/**
 * @brief The AdressingType enum
 * Represent type of adressing
 *
 *
 *
 */
/*
typedef enum AdressingType
{
        IMMIDIATE,
        DIRECT,
        INDIRECT,
        INDIRECT_DECREMENT,
        INDIRECT_INCREMENT,
        NULL
}AdressingType;

*/


/**
 * Klasa reprezentująca argumenty i typ adresowania instrukcji. Jest to klasa abstrakcyjna, z której będą dziedziczyły rzeczywiste tryby adresowania.
 * Wykonanie instrukcji countArgument powoduje obliczenie argumentu i zwrócenie go w postaci IntegerRegister(operacje wykonywane modulo rozmiar rdzenia).
 * Aby klasa mogła obliczać argumenty potrzebuje dostępu do rdzenia. Posiada więc shared_ptr do niego.
 *
 * @brief The Operand class
 */
class Operand
{
public:
    typedef shared_ptr<Core> CorePtr;

    Operand(int value = 0);
    Operand(const Operand& other);
    Operand& operator=(const Operand& other);

    int getValue();
    void setValue(int value);

    IntegerRegister countArgument() = 0;


protected:
    CorePtr core_;
    int value_;


};

}
#endif // OPERAND_HPP
