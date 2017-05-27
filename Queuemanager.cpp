#include "Queuemanager.hpp"

#include <stdexcept>

namespace arbiter
{


    QueueManager::QueueManager(const unsigned int CORE_SIZE)
        :actual_process_(CORE_SIZE), isFirstTour_(true)
    {}

    void QueueManager::createFirstProcesses(const IntegerRegister &pc_war_1, const IntegerRegister &pc_war_2)
    {
        Process proc_war_1(pc_war_1), proc_war_2(pc_war_2);
        queue_1.push(proc_war_1);
        queue_2.push(proc_war_2);

        actual_process_ = proc_war_1;
        isFirstTour_ = true;
    }

    void QueueManager::addProcessToActualWarrior(const IntegerRegister &new_proc_next_pc)
    {
        Process new_proc(new_proc_next_pc);
        if(isFirstTour_)
        {
            queue_1.push(new_proc);
        }
        else
        {
            queue_2.push(new_proc);
        }
    }

    void QueueManager::saveProcess(const IntegerRegister &next_pc)
    {
        Process proc(next_pc);
        if(isFirstTour_)
        {
            queue_1.push(proc);
        }
        else
        {
            queue_2.push(proc);
        }
    }

    bool QueueManager::removeActualProcess()
    {
        //tak na prawdę nic po prostu nie robimy - nie dodajemy procesu który sie wykonał z powrotem do kolejki.
        if(isFirstTour_)//tylko sprawdzamy czy po poprzednim zwróceniu i wykonaniu procesu nie został jeszcze jakiś w kolejce aktualnego gracza
        {
            return queue_1.size()!=0?true:false;
        }
        else
        {
            return queue_2.size()!=0?true:false;
        }
    }

    Process QueueManager::getProcessToExecute()
    {
        if(isFirstTour_)
        {
            isFirstTour_ = false;
            actual_process_ = queue_1.front();
            queue_1.pop();
            return actual_process_;
        }
        else
        {
            isFirstTour_ = true;
            actual_process_ = queue_2.front();
            queue_2.pop();
            return actual_process_;
        }
    }

    bool QueueManager::checkIfAny2WarriorsExist() const
    {
        if(queue_1.size()==0 || queue_2.size()==0)
            return false;//w ktorejś kolejce nie ma już wojowników
        return true;
    }
    WINNER QueueManager::getWinner()const
    {
        if(queue_1.size()!=0 && queue_2.size()!=0)//jeśli w obydwu kolejkach są procesy do wykonania
            return NONE;

        if(queue_1.size()==0)
            return FIRST;
        else
            return SECOND;
    }






}
