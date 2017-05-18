#ifndef CORE_HPP
#define CORE_HPP

#include<vector>
#include"Instruction.hpp"
#include<memory>
#include<mutex>
#include"IntegerRegister.hpp"
//#include"CoreCreator.hpp"
#include"Observer.hpp"
namespace arbiter
{


    class Instruction;
    class CoreCreator;


/**
     * @brief The Core class Klasa reprezentująca rdzeń, w którym ma toczyć się walka.
     * Pozwala pobierać instrukcję o danym adresie(jako wskazania typu shared_ptr lub kopia głęboka unique_ptr), oraz modyfikować instrukcję o danym adresie.
     * Aby mogła być użyta przez kilka wątków jest chroniona mutexem.
     *
     */
    class Core
    {

       // typedef std::shared_ptr<Instruction> InsSharedPtr;


    public:
        typedef std::unique_ptr<Instruction> InsPtr;

        typedef std::unique_ptr<Core> CorePtr;


        Core(std::unique_ptr<Observer> &obs_ptr);

//        Core(const Core &other);

       // Core& operator =(const Core &other);

        /**
         * @brief Core Tworzy rdzeń na podstawie vectora wskazań na instrukcje. Przejmuje ten vector i ustawia jako swój.
         * @param memory_of_core Vector reprezentujący instniejące instrukcje w rdzeniu.
         */
     //   Core(std::vector<InsSharedPtr> &&memory_of_core);



        /**
         * @brief modifyInstruction Zapisuje nową instrukcję pod adresem w rdzeniu wskazanym przez addres_of_ins
         * @param address_of_ins Adres modyfikowanej instruckji
         * @param new_ins Nowa instrukcja, która ma zostać zapisana(UWAGA! Jest przenoszona do rdzenia, i tracona dla zewnętrznego posiadacza)
         */
        void modifyInstruction(const IntegerRegister address_of_ins, InsPtr new_ins);

        /**
         * @brief getInstruction Zwraca referencje na instrukcję o podanym adresie w rdzeniu.
         * @param address_of_ins Adres pobieranej instrukcji
         * @return Wskazanie na instrukcję pod danym adresem
         */
        InsPtr& getInstructionRef(const IntegerRegister address_of_ins)const;


        /**
         * @brief getInstructionCopy Tworzy kopię głęboką instrukcji o podanym adresie w rdzeniu.
         * @param address_of_ins Adres pobieranej instrukcji.
         * @return Wskazanie na kopię głęboką instrukcji.
         */
        InsPtr getInstructionCopy(const IntegerRegister address_of_ins)const;

        /**
         * @brief getCoreSize Zwraca rozmiar rdzenia(uwaga - maksymalny dostępny adres to (core_size - 1)
         * @return Rozmiar rdzenia
         */
        unsigned int getCoreSize()const;

        /**
         * @brief setObserver Dodaje wskazanie na istniejącego obserwatora. Jeżeli wskazanie na obserwatora juz istnieje to zostanie usunięte i zastąpione nowym
         * @param obs_ptr Istniejący obserwator, który będzie informowany o zmianach stanu obiektu
         */
//        void setObserver(std::unique_ptr<Observer> &obs_ptr);





    private:
        std::vector<InsPtr> core_memory_;
        mutable std::mutex mutex_;

        std::unique_ptr<Observer> &observer_ptr_;

        friend class CoreCreator;
        friend class Observer;
        friend class DATCreator;


        Core() = delete;//musimy podac w konstruktorze obserwatora



        /**
         * @brief notifyObserver Informuje obserwatora, że stan obiektu się zmienił
         */
        void notifyObserver();

    };

}

#endif // CORE_HPP
