#ifndef ARBITER_HPP
#define ARBITER_HPP

#include<memory>

namespace arbiter
{



/**
 * @brief The Arbiter class
   Opis algorytmu działania:
   1.Arbiter dostaje wojowników, oraz parametry, z jakimi ma się odbyć walka(np. położenie wojowników)
   2.Arbiter wgrywa wojowników do rdzenia, oraz dodaje do kolejek procesów po jednym procesie o odpowiednim PC

   3.Dopoki manager mowi, że kolejny gracz ma proces w swojej kolejce:
        Arbiter każe managerowi zwrocić kolejny proces do wykowania.
        Przekazuje go do wykonania procesorowi.
        Ten zwraca wyniki wykonania instrukcji.
        Arbiter przekazuje wyniki wykonania instrukcji do managera i każe mu je wykonać.
        Goto ptk.3


*/
class Arbiter
{
typedef shared_ptr<Core> CorePtr;
typedef shared_ptr<Warrior> WarriorPtr;
public:
    Arbiter();

    CorePtr getCore();

    void createCore(const unsigned int CORE_SIZE);
    unsigned int getCoreSize();

    void createWarrior1(const WarriorPtr &war1, Parameters param);
    void createWarrior2(const WarriorPtr &war2, Parameters param);

    WarriorPtr getWinner(); //jezeli walka nierozstrzygnięta lub trwa zwraca nulla, w przeciwnym wypadku - zwyciezce

    bool executeNextInstruction();//zwraca informację, czy wciaz trwa walka



private:
    //void createProcess(ProcessQueue queue, ProgramCounter proc_pc);


    CorePtr core_ptr_ ;

    ProcessQueueManager manager;//zarządza kolejkami procesów

    Processor processor_;



};



}
#endif // ARBITER_HPP
