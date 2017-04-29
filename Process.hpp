#ifndef PROCESS_HPP
#define PROCESS_HPP

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
        Process();

        IntegerRegister getProcPc();
        void updateProcPC(IntegerRegister next_pc);
        void incrementPC();


    protected:
        InteregRegister proc_PC_;

    };
}
#endif // PROCESS_HPP
