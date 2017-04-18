#ifndef QUEUEMANAGER_HPP
#define QUEUEMANAGER_HPP

#include<vector>
#include<queue>
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
    class QueueManager
    {
    public:
        typedef shared_ptr<Core> CorePtr;
        typedef shared_ptr<Warrior> WarriorPtr;


        QueueManager();
        void addWarrior(const WarriorPtr &war, const Parameters &param);


        /**
         * @brief createProcessToActualWarrior Dodaje nowy proces do kolejki wojownika, który się aktualnie wykonywał.
         *
         */
        void createProcessToActualWarrior();//dodaje nowy proces, stworzony w wyniki działania instrukcji SPLIT



        /**
         * @brief getProcessToExecute Wybiera proces do wykonania, zapisuje go w swoim polu, oraz zwraca jego kopię.
         * @return Proces do wykonania
         */
        Process getProcessToExecute();//zwraca arbitrowi proces do wykowania


        /**
         * @brief removeActualProcess Jeżeli okazało się, że proces wykonał nielegalna isntrukcję to manager usuwa aktualny proces z kolejki.
         */
        void removeActualProcess();//usuwa aktualnie wykonywany proces, jesli arbiter stwierdzi, że wykonał instrukcję DAT

        /**
         * @brief checkIfAny2WarriorsExist Zwraca informację, czy istnieje jeszcze jakichkolwiek dwóch żywych graczy.
         * @return Zwraca true, jeśli istnieje jeszcze dwóch żywych graczy. False, jeśli pozostał tylko jeden lub żaden
         */
        bool checkIfAny2WarriorsExist();


    protected:
        std::vector<std::queue> queue_list;
        Process actual_process;
    };

}
#endif // QUEUEMANAGER_HPP
