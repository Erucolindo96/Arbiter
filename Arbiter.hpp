#ifndef ARBITER_HPP
#define ARBITER_HPP

#include<memory>
#include"CoreCreator.hpp"
#include"Core.hpp"
#include"Queuemanager.hpp"
#include"Process.hpp"
#include"Processor.hpp"
#include "Warrior.hpp"
#include "Observer.hpp"

namespace arbiter
{



/**
 * @brief The Arbiter class
   Opis algorytmu działania:
   1.Arbiter dostaje CoreCreatora, reprezentującego wybrane przez usera parametry walki, oraz wojowników
   2.Arbiter każe CoreCreatorowi utworzyć rdzeń z wojownikami. Następnie zleca Managerowi kolejek utworzenie wojowników

   3.Dopoki manager mowi, że jakichkolwiek dwóch graczy ma proces w swojej kolejce:
        Arbiter każe managerowi zwrocić kolejny proces do wykowania.
        Przekazuje go do wykonania procesorowi.
        Ten zwraca wyniki wykonania instrukcji.
        Arbiter przekazuje wyniki wykonania instrukcji do managera i każe mu je wykonać.
        Goto ptk.3
   4. Gdy otrzymamy informację od managera, że został tylko jeden żywy wojownik, pobieramy od managera informację, który wojownik wygrał.
        Zapisujemy go, i pozwalamy zwrócić w metodzie getWinner()


*/
class Arbiter
{

typedef std::unique_ptr<Core> CorePtr;
//typedef std::shared_ptr<Warrior> WarriorPtr;
//typedef std::shared_ptr<Parameters> ParametersPtr;

typedef std::unique_ptr<CoreCreator> CoreCreatorPtr;
typedef std::unique_ptr<Observer> ObserverPtr;

public:
    Arbiter(ObserverPtr &obs_ptr, CoreCreatorPtr core_creator);

    /**
     * @brief addWarriors Dodaje wojowników, którzy maja rozegrać walkę
     * @param warriors Wektor wojowników
     */
    void addWarriors(const std::vector<Warrior> &warriors);

    /**
     * @brief addCoreObserver Dodaje istniejącemu rdzeniowi wskazanie na obserwatora. Jesli rdzeń nie istnieje - rzuca wyjątek.
     * @param observ_ptr Wskazanie na obserwatora, któremu rdzeń będzie raportował o zmianach.
     * @throw
     */
//    void addCoreObserver(const ObserverPtr observ_ptr);


    /**
     * @brief executeNextInstruction Zleca wykonanie następnej instrukcji.
     * @return Informacja, czy walka wciąż trwa(gdy zwróci false można pobrać zwyciezcę).
     */
    bool executeNextInstruction();

    std::unique_ptr<Warrior> getWinner(); //jezeli walka nierozstrzygnięta lub trwa zwraca nulla, w przeciwnym wypadku - zwyciezce



private:
    /**
     * @brief createProcess Tworzy nowy proces. Nowy proces jest tworzony w kolejce aktualnego procesu
     * @param actual_proc
     */
    void createProcess(Process actual_proc);

    /**
     * @brief createCore Tworzy rdzeń o podanych parametrach
     * @param core_creator Klasa tworząca rdzeń.
     */
    void createCore( CoreCreatorPtr core_creator);


    Arbiter() = delete;

    //CoreCreatorPtr core_creator_;
    QueueManager manager;//zarządza kolejkami procesów
    std::vector<Warrior> warriors_;

    CorePtr core_ptr_ ;

    Processor processor_;

    ObserverPtr &observer_ptr_;



};



}
#endif // ARBITER_HPP
