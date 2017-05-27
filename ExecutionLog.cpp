#include"ExecutionLog.hpp"

namespace arbiter
{
    ExecutionLog::ExecutionLog(const IntegerRegister &next_pc,const IntegerRegister &next_pc_new_proc, const bool is_proc_live, const bool is_proc_split):next_pc_current_proc_(next_pc), next_pc_new_proc_(next_pc_new_proc), is_proc_live_(is_proc_live), is_proc_split_(is_proc_split)
    {}

    ExecutionLog::ExecutionLog(const ExecutionLog &other): next_pc_current_proc_(other.next_pc_current_proc_), next_pc_new_proc_(other.next_pc_new_proc_),  is_proc_live_(other.is_proc_live_), is_proc_split_(other.is_proc_split_)
    {}


}
