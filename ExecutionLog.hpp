#ifndef EXECUTIONLOG_HPP
#define EXECUTIONLOG_HPP

#include"IntegerRegister.hpp"


namespace arbiter
{
    /**
     * @brief The ExecutionLog class Klasa przechowująca wyniki wykonania instrukcji.
     * Zwraca informację o nextPC, czy proces umarł po wykonaniu instrukcji, czy proces utworzył nowy proces,
     */
    struct ExecutionLog
    {
        IntegerRegister next_pc_;
        bool is_proc_live_;
        bool is_proc_split_;

        ExecutionLog(const IntegerRegister &next_pc, const bool is_proc_live = false, const bool is_proc_split = false);
        ExecutionLog(const ExecutionLog& other);


        ExecutionLog() = delete;
    };
}



#endif // EXECUTIONLOG_HPP

