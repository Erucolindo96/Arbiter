#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"Operand.hpp"
#include <stdexcept>
#include <memory>
#include "IntegerRegister.hpp"

namespace arbiter
{

/**
  @class Operand

  Class Operand represent an Operand of istruction Red Code Assembler


  */

/*
typedef enum Opcode
{
DAT,
MOV,
ADD,
SUB,
JMP,
JMZ,
JMN,
DJN,
CMP,
SPL,
SLT
} Opcode;
*/




/**
 * Instrukcja - klasa implementująca wzorzec komendy. Jest to klasa abstrakcyjna - z niej będą dziedziczyć rzeczywiste instrukcje.
 * Instrukcje znajdują się w rdzeniu. Zawierają dwa operandy(również komendy), reprezentujące sposoby adresowania. Zawiera również rozmiar swojego rdzenia(operacje muszą być wykonywane modulo rozmiar rdzenia).
 * Aby mogła nadpisać rdzeń musi mieć do niego dostęp, Dajemy więc jej shared_ptr do rdzenia.
 *
 * Wykonanie instrukcji:
 * 1.Najpierw obliczane są operandy.
 * 2.Potem modyfikowany jest rdzeń(w zależności od tego jaka jest to instrukcja rzeczywista - metoda czysto wirtualna).
 * 3.Zwraca też wyniki wykonania instrukcji
 * @brief The Instruction class
 */

class Instruction
{
public:
    typedef std::shared_ptr<Core> CorePtr;
    typedef std::unique_ptr<Operand> OperandPtr;

    explicit Instruction();
    explicit Instruction(const Instruction& other);
  //  Instruction(const Instruction &&other);

    explicit Instruction(const OperandPtr& operand_A, const OperandPtr& operand_B, CorePtr core);

    Instruction& operator=(const Instruction& other);
 //   Instruction& operator =(const Instruction &&other);

    OperandPtr operandA() const;
    OperandPtr operandB() const;

    void setOperandA(const OperandPtr& operand);
    void setOperandB(const OperandPtr& operand);

    /**
     * @brief execute Wykonuje instrukcję, tzn oblicza argumenty, modyfikuje rdzeń, i zwraca do wołającego informację o wykonaniu
     * @return Informacja o wykonaniu instrukcji.
     */
    virtual ExecutionLog execute() = 0;
    virtual std::unique_ptr<Instruction> clone()const = 0;

    virtual ~Instruction();

protected:

    //const unsigned int CORE_SIZE_;
    CorePtr core_;
    OperandPtr operand_A_;
    OperandPtr operand_B_;




};
}
#endif // INSTRUCTION_HPP
