#ifndef OPERAND_HPP
#define OPERAND_HPP

#include<stdexcept>
#include"IntegerRegister.hpp"
#include"Core.hpp"
#include<memory>


namespace arbiter
{



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
    class Core;

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

    typedef std::unique_ptr<Core> CorePtr;
    typedef std::unique_ptr<Operand> OperandPtr;

    explicit Operand(const IntegerRegister value);
    Operand(const Operand& other);
    Operand(const Operand &&other);

    Operand& operator=(const Operand& other);
    Operand& operator=(const Operand &&other);

    IntegerRegister getValue()const;
    void setValue(const IntegerRegister value);

    virtual IntegerRegister countArgument(CorePtr &core) = 0;
    virtual OperandPtr clone()const = 0;


protected:
    IntegerRegister value_;
    Operand() = delete;//nalezy zainicjowac wielkosc rdzenia w IntegerRegister value_
};

}
#endif // OPERAND_HPP
