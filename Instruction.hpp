#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"Operand.hpp"

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
    typedef shared_ptr<Core> CorePtr;

    explicit Instruction();
    explicit Instruction(const Instruction& other);
    explicit Instruction(const Operand& operand_A, const Operand& operand_B, CorePtr core);
    Instruction& operator=(const Instruction& other) ;

    Operand operandA() const;
    Operand operandB() const;
    void setOperandA(const Operand& operand);
    void setOperandB(const Operand& operand);

    /**
     * @brief execute Wykonuje instrukcję, tzn oblicza argumenty, modyfikuje rdzeń, i zwraca do wołającego informację o wykonaniu
     * @return Informacja o wykonaniu instrukcji.
     */
    virtual ExecutionLog execute() = 0;


    virtual ~Instruction();//chyba nie bedzie trzeba dziedziczyć po tym - w dodatku chyba niepotrzebny

protected:

    //const unsigned int CORE_SIZE_;
    CorePtr core_;
    Operand operand_A_;
    Operand operand_B_;




};
}
#endif // INSTRUCTION_HPP
