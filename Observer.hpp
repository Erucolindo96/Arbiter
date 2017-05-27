#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include"IntegerRegister.hpp"
namespace arbiter
{

/**
     * @brief The Observer class Obserwator, występujący w klasie Core.
     * Gdy stan rdzenia się zmienił(np. została wykonana instrukcja) jest wołany obserwator.
     * Metoda update() informuje go, która instrukcja została zmodyfikowana.
     * @see Core
     */
    class Observer
    {
    public:
        virtual void update(const IntegerRegister &modified_ins_address) = 0;
        virtual ~Observer() {}

    };

}
#endif // OBSERVER_HPP
