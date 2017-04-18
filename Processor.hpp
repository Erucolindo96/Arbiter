#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP


namespace arbiter
{

    class Processor
    {
        typedef shared_ptr<Core> CorePtr;
        typedef shared_ptr<Instruction> InsPtr;
    public:
        Processor();

        void setCore(CorePtr core_ptr);
        CorePtr getCore();
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
        //bool isIlligal(); //czy pobrana do wykonania instrukcja była nielegalna
        //void execution(); //wykonuje pobraną instrukcję - modyfikuje rdzeń


        CorePtr core_ptr_;

        InsPtr loaded_instruction_;
        ExecutionLog exec_log_;
        Process actual_proc_;
        /*
        ArgumentRegister arg_reg_A_, arg_reg_B_;
        PointerRegister ptr_reg_A_, ptr_reg_B_;
        AddressRegister adr_reg_A_, adr_reg_B_;
        ValueRegister val_reg_A_, val_reg_B_;
        ProgramCounter pc_;
*/
};



}

#endif // PROCESSOR_HPP
