#ifndef OBSERVER_HPP
#define OBSERVER_HPP

namespace arbiter
{


    class Observer
    {
    public:
        virtual void update() = 0;
        virtual ~Observer() {}

    };

}
#endif // OBSERVER_HPP
