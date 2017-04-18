#ifndef ARBITER_HPP
#define ARBITER_HPP

#include<memory>

namespace arbiter
{



/**
 * @brief The Arbiter class
   Opis algorytmu działania:
   1.Arbiter dostaje wojowników, oraz parametry, z jakimi ma się odbyć walka(np. położenie wojowników)
   2.Arbiter wgrywa wojowników do rdzenia, oraz każe managerowi utworzyć kolejki procesów danych wojowników.

   3.Dopoki manager mowi, że jakichkolwiek dwóch graczy ma proces w swojej kolejce:
        Arbiter każe managerowi zwrocić kolejny proces do wykowania.
        Przekazuje go do wykonania procesorowi.
        Ten zwraca wyniki wykonania instrukcji.
        Arbiter przekazuje wyniki wykonania instrukcji do managera i każe mu je wykonać.
        Goto ptk.3
   4. Gdy otrzymamy informację od managera, że został tylko jeden żywy wojownik, pobieramy od managera informację, który wojownik wygrał. Zapisujemy ją, i pozwalamy zwrócić w metodzie getWinner()


*/
class Arbiter
{
typedef shared_ptr<Core> CorePtr;
typedef shared_ptr<Warrior> WarriorPtr;
typedef shared_ptr<Parameters> ParametersPtr;

public:
    Arbiter();

    CorePtr getCore();

    void createCore(const unsigned int CORE_HEIGHT, const unsigned int CORE_WIDTH);
    /**
     * @brief getCoreSize Zwraca ilość komórek rdzenia
     * @return Całtowity rozmiar rdzenia(HEIGHT*WIDTH)
     */
    unsigned int getCoreSize() const;

    /**
     * @brief createWarrior Tworzy wojownika.
     * @param war1 Program tworzonego wyjownika.
     * @param param Parametry z jakimi ma być stworzony)
     */
    void createWarrior(const WarriorPtr &war1, const ParametersPtr &param);

    WarriorPtr getWinner(); //jezeli walka nierozstrzygnięta lub trwa zwraca nulla, w przeciwnym wypadku - zwyciezce

    bool executeNextInstruction();//zwraca informację, czy wciaz trwa walka



private:
    /**
     * @brief createProcess Tworzy nowy proces. Nowy proces jest tworzony w kolejce aktualnego procesu
     * @param actual_proc
     */
    void createProcess(Process actual_proc);


    CorePtr core_ptr_ ;

    ProcessQueueManager manager;//zarządza kolejkami procesów
    WarriorPtr winner_;

    Processor processor_;



};



}
#endif // ARBITER_HPP
