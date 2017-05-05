#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"Operand.hpp"
#include <stdexcept>
#include <memory>
#include "IntegerRegister.hpp"
#include"Core.hpp"
#include"ExecutionLog.hpp"
namespace arbiter
{


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


     class Core;
     class Operand;

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

    typedef std::unique_ptr<Instruction> InsPtr;
    typedef std::shared_ptr<Instruction> InsSharedPtr;

    OperandPtr operandA() const;
    OperandPtr operandB() const;

    void setOperandA(const OperandPtr& operand);
    void setOperandB(const OperandPtr& operand);

    /**
     * @brief execute Wykonuje instrukcję, tzn oblicza argumenty, modyfikuje rdzeń, i zwraca do wołającego informację o wykonaniu
     * @return Informacja o wykonaniu instrukcji.
     */
    virtual ExecutionLog execute(CorePtr core) = 0;
    virtual InsPtr clone()const = 0;

    virtual ~Instruction() = 0;

protected:

    OperandPtr operand_A_;
    OperandPtr operand_B_;


    Instruction();
    Instruction(const Instruction& other);
  //  Instruction(const Instruction &&other);

    Instruction(const OperandPtr& operand_A, const OperandPtr& operand_B);

    virtual Instruction& operator=(const Instruction& other);
 //   Instruction& operator =(const Instruction &&other);




};
}
#endif // INSTRUCTION_HPP
