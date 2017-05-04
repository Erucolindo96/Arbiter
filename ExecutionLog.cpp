#include"ExecutionLog.hpp"

namespace arbiter
{
    ExecutionLog::ExecutionLog(const IntegerRegister &next_pc, const bool is_proc_live, const bool is_proc_split):next_pc_(next_pc), is_proc_live_(is_proc_live), is_proc_split_(is_proc_split)
    {}

    ExecutionLog::ExecutionLog(const ExecutionLog &other): next_pc_(other.next_pc_), is_proc_live_(other.is_proc_live_), is_proc_split_(other.is_proc_split_)
    {}


}
