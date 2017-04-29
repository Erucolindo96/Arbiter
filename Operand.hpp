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
    typedef std::shared_ptr<Core> CorePtr;
    typedef std::unique_ptr<Operand> OperandPtr;

    Operand(CorePtr core = nullptr, int value = 0);
    Operand(const Operand& other);
    Operand(const Operand &&other);

    Operand& operator=(const Operand& other);
    Operand& operator=(const Operand &&other);

    int getValue()const;
    void setValue(const int value);

    CorePtr getCorePtr()const;
    void setCorePtr(const CorePtr ptr);

    virtual IntegerRegister countArgument() = 0;
    virtual OperandPtr clone()const = 0;


protected:
    CorePtr core_;
    int value_;
    /**
     * @brief chechCorePtr Sprawdza czy wskaznik na rdzeń jest taki sam jak w Opetandzie other
     * @param other Porownywany Operand
     * @throw std::inva
     */
    void chechCorePtr(const Operand& other)const;

};

}
#endif // OPERAND_HPP
