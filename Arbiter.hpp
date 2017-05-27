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


public:




    typedef std::unique_ptr<Core> CorePtr;
    typedef std::unique_ptr<CoreCreator> CoreCreatorPtr;
    typedef std::unique_ptr<Observer> ObserverPtr;


    /**
     * @brief Arbiter Tworzy Arbitra, posiadającego wskazanie na Obserwatora, oraz przejmującego CoreCreator
     * CoreCreator zawieja już w sobie wojowników - nie trzeba ich dodatkowo tworzyć.
     *
     * @param obs_ptr Wskazanie na obserwatora, rejestrującego zmiany w rdzeniu.
     * @param core_creator Obiekt tworzący rdzeń według zadanych przez użytkownika parametrów.
     */
    Arbiter(ObserverPtr &obs_ptr, CoreCreatorPtr core_creator);

    /**
     * @brief executeNextInstruction Zleca wykonanie następnej instrukcji.
     * @return Informacja, czy walka wciąż trwa(gdy zwróci false można pobrać zwyciezcę).
     */
    bool executeNextInstruction();

    WINNER getWinner()const; //jezeli walka nierozstrzygnięta lub trwa zwraca nulla, w przeciwnym wypadku - zwyciezce



private:

    /**
     * @brief createCore Tworzy rdzeń o podanych parametrach
     * @param core_creator Klasa tworząca rdzeń.
     */
    void createCore(const CoreCreatorPtr &core_creator);


    Arbiter() = delete;

    Warrior warrior1_, warrior2_;
    CorePtr core_ptr_ ;
    Processor processor_;
    QueueManager manager_;//zarządza kolejkami procesów
    ObserverPtr &observer_ptr_;

};



}
#endif // ARBITER_HPP
