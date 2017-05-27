#ifndef QUEUEMANAGER_HPP
#define QUEUEMANAGER_HPP

#include<vector>
#include<queue>
#include"Core.hpp"
#include<memory>
#include"Process.hpp"
#include"Warrior.hpp"
namespace arbiter
{

/**
     * Odpowiedzialności:
     * 1. Zarządza kolejkami procesów graczy
     * 2. Zwraca Proces do wykowania
     * 3. Tworzy nowe procesy
     * 4. Kasuje te, które wykonały nielegalną instrukcję.
     *
     *  @brief The QueueManager class
     */

    enum WINNER
    {
        FIRST,
        SECOND,
        NONE
    };

    class QueueManager
    {
    public:
        typedef std::unique_ptr<Core> CorePtr;
        //typedef std::shared_ptr<Warrior> WarriorPtr;
        QueueManager( const unsigned int CORE_SIZE);
     //   void addWarrior(const WarriorPtr &war, const Parameters &param);

        /**
         * @brief createFirstProcesses Tworzy początkowe procesy graczy.
         * @param pc_war_1 PC pierwszego wojownika
         * @param pc_war_2 PC drugiego wojownika
         */
        void createFirstProcesses(const IntegerRegister &pc_war_1, const IntegerRegister &pc_war_2);

        /**
         * @brief createProcessToActualWarrior Dodaje nowy proces do kolejki wojownika, który się aktualnie wykonywał.
         * Czyli tego, do kogo nalezy proces actual_process_
         */
        void addProcessToActualWarrior(const IntegerRegister &new_proc_next_pc);//dodaje nowy proces, stworzony w wyniki działania instrukcji SPLIT

        /**
         * @brief getProcessToExecute Wybiera proces do wykonania, zapisuje go w swoim polu, oraz zwraca jego kopię.
         * @return Proces do wykonania
         */
        Process getProcessToExecute();//zwraca arbitrowi proces do wykowania

        /**
         * @brief saveProcess Zapisuje proces przechowywany w Managerze do odpowiedniej kolejki procesów.
         * Jest to proces zwrócony wcześniej przez getProcessToExecute() - saveProcess() zachowuje tenże proces w kolejce posiadającego go gracza.
         */
        void saveProcess(const IntegerRegister &next_pc);

        /**
         * @brief removeActualProcess Jeżeli okazało się, że proces wykonał nielegalna instrukcję to manager usuwa aktualny proces z kolejki.
         * @return Informację, czy wojownik może dalej waliczyć(posiada procesy w swojej kolejce po usunięciu tego)
         */
        bool removeActualProcess();//usuwa aktualnie wykonywany proces, jesli arbiter stwierdzi, że wykonał instrukcję DAT

        /**
         * @brief checkIfAny2WarriorsExist Zwraca informację, czy istnieje jeszcze jakichkolwiek dwóch żywych graczy.
         * @return Zwraca true, jeśli istnieje jeszcze dwóch żywych graczy. False, jeśli pozostał tylko jeden lub żaden
         */
        bool checkIfAny2WarriorsExist()const;
        /**
         * @brief getWinner Zwraca zwycięzcę, jeśli istnieje.
         * @return Zwycięzca walki.
         * @throws Rzuca wyjątek jeśli walka jest nierozstrzygnięta.
         */
        WINNER getWinner()const;



    protected:
        std::queue<Process> queue_1, queue_2;
        Process actual_process_;

        bool isFirstTour_;


    };

}
#endif // QUEUEMANAGER_HPP
