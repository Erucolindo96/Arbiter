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
        /**
         * @brief next_pc_current_proc_ next_pc procesu który wykonał instrukcję
         */
        IntegerRegister next_pc_current_proc_;//next_pc procesu który wykonał instrukcję, oraz next_pc procesu który został utworzony w instrukcji SPL
        /**
         * @brief next_pc_new_proc_ Next_pc nowo utworzonego procesu. Jeśli nie powstał - zawiera dowolną wartość.
         */
        IntegerRegister  next_pc_new_proc_;
        bool is_proc_live_;
        bool is_proc_split_;

        ExecutionLog(const IntegerRegister &next_pc,const IntegerRegister &next_pc_new_proc, const bool is_proc_live , const bool is_proc_split );
        ExecutionLog(const ExecutionLog& other);


        ExecutionLog() = delete;
    };
}



#endif // EXECUTIONLOG_HPP

