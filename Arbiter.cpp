#include "Arbiter.hpp"


namespace arbiter
{

    Arbiter::Arbiter(ObserverPtr &obs_ptr, CoreCreatorPtr core_creator):
    warrior1_(core_creator->getWarrior1Ref()), warrior2_(core_creator->getWarrior2Ref()),
    core_ptr_(), manager(), processor_(core_ptr_), observer_ptr_(obs_ptr)
    {
        createCore(core_creator);

    }

    void Arbiter::createCore(const CoreCreatorPtr &core_creator)
    {
        throw std::runtime_error("TODO");
    }
}
