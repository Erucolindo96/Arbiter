#ifndef CORE_HPP
#define CORE_HPP

#include<vector>
#include"Instruction.hpp"
#include<memory>
#include<mutex>
#include"IntegerRegister.hpp"

namespace arbiter
{
    typedef std::shared_ptr<Instruction> InsPtr;
    typedef std::shared_ptr<Core> CorePtr;

/**
     * @brief The Core class Klasa reprezentująca rdzeń, w którym ma toczyć się walka.
     * Pozwala pobierać instrukcję o danym adresie, oraz modyfikować instrukcję o danym adresie.
     * Aby mogła być użyta przez kilka wątków jest chroniona mutexem.
     *
     */
    class Core
    {
    public:
        Core();
        Core(const Core &other);
        Core& operator =(const Core &other);
        /**
         * @brief Core Tworzy rdzeń na podstawie vectora wskazań na instrukcje. Przejmuje ten vector i ustawia jako swój.
         * @param memory_of_core Vector reprezentujący instniejące instrukcje w rdzeniu.
         */
        Core(std::vector<InsPtr> &&memory_of_core);

        /**
         * @brief getInstruction Zwraca wskazanie na instrukcję o podanym adresie w rdzeniu.
         * @param address_of_ins Adres pobieranej instrukcji
         * @return Wskazanie na instrukcję pod danym adresem
         */
        InsPtr getInstruction(const IntegerRegister address_of_ins);

        /**
         * @brief modifyInstruction Zapisuje nową instrukcję pod adresem w rdzeniu wskazanym przez addres_of_ins
         * @param address_of_ins Adres modyfikowanej instruckji
         * @param new_ins Nowa instrukcja, która ma zostać zapisana
         */
        void modifyInstruction(const IntegerRegister address_of_ins, std::unique_ptr<Instruction> new_ins);

        /**
         * @brief getInstructionCopy Tworzy kopię głęboką instrukcji o podanym adresie w rdzeniu.
         * @param address_of_ins Adres pobieranej instrukcji.
         * @return Wskazanie na kopię głęboką instrukcji.
         */
        std::unique_ptr<Instruction> getInstructionCopy(const IntegerRegister address_of_ins);

        /**
         * @brief operator [] Zwraca wskazanie na instrukcję o podanym adresie w rdzeniu.
         * @param address_of_ins Adres instrukcji, do której wskazanie będziemy zwracać
         * @return Wskazanie na instrukcję.
         */
        InsPtr operator[](const IntegerRegister address_of_ins);


    private:
        std::vector<InsPtr> core_memory;
        std::mutex mutex;

    };

}

#endif // CORE_HPP
