#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP


#include"Process.hpp"
#include"ExecutionLog.hpp"
#include"Instruction.hpp"
#include"IntegerRegister.hpp"
#include <memory>
namespace arbiter
{

    class Processor
    {
        typedef std::shared_ptr<Core> CorePtr;
        typedef std::shared_ptr<Instruction> InsPtr;
    public:
        //Processor(const int CORE_SIZE);
        Processor(CorePtr core);

        //void setCorePtr(CorePtr core_ptr);
        CorePtr getCorePtr()const;


        /**
         * @brief executeProcess Wykonuje instrukcję podanego procesu, i zwraca wyniki wykonania instrukcji
         * @param proc Proces do wykonania
         * @return Wyniki wykonania instrukcji(nextPC procesu, czy instrukcja była legalna, itp. )
         */
        ExecutionLog executeProcess(const Process &proc);


    private:
        /**
         * @brief loadInstruction Ładuje instrukcję procesu actual_proc_ do procesora
         */
        void loadInstruction();
        Processor() = delete;//nie znamy rozmiaru rdzenia, wiec nie mozemy zainicjowac proc_pc procesu actual_proc

        CorePtr core_ptr_;

        InsPtr loaded_instruction_;
        ExecutionLog exec_log_;//byc moze niepotrzebne
        Process actual_proc_;

};



}

#endif // PROCESSOR_HPP
