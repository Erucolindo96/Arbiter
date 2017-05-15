#include "Arbiter.hpp"


namespace arbiter
{

    Arbiter::Arbiter(ObserverPtr &obs_ptr, CoreCreatorPtr core_creator):manager(), warriors_(core_creator->getWarriorsCopy() ) , core_ptr_(), processor_(core_ptr_), observer_ptr_(obs_ptr)
    {
        createCore(std::move(core_creator) );

    }

    void Arbiter::createCore(CoreCreatorPtr core_creator)
    {
        throw std::runtime_error("TODO");
    }
}
