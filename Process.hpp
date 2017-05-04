#ifndef PROCESS_HPP
#define PROCESS_HPP

#include"IntegerRegister.hpp"

namespace arbiter
{
/**
     * @brief The Process class Klasa reprezentująca proces.
     * Zawiera PC tego procesu, tzn adres instrukcji, która ma zostac wykonana po pobraniu tego procesu z kolejki instrukcji.
     * Po wykonaniu go, PC procesu należy zmodyfikować do nowej wartości. Można to zrobić za pomocą metody incrementPc (zwieksza ona PC o 1, tzn proces przechodzi na instrukcję następną)
     * lub updateProcPC (np. gdy wykonano skok - ładujemy adres instrukcji do której skoczyliśmy)
     */
    class Process
    {
    public:
        explicit Process(const unsigned int CORE_SIZE);
        explicit Process(const IntegerRegister &proc_pc);
        Process(const Process &other);

        Process& operator =(const Process &other);

        IntegerRegister getProcPc()const;
        IntegerRegister updateProcPC(IntegerRegister next_pc);
        IntegerRegister incrementPC();


    protected:
        IntegerRegister proc_PC_;
        Process() = delete;//poniewaz nie znamy rozmiaru rdzenia to nie mozemy ustawic domyslnej wartosci proc_PC_

    };
}
#endif // PROCESS_HPP
