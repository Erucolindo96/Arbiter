#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP


namespace arbiter
{

    class Processor
    {
        typedef shared_ptr<Core> CorePtr;

    public:
        Processor();

        void setCore(CorePtr core_ptr);
        CorePtr getCore();

        ExecutionLog execute(const ProgramCounter &pc);//zwraca informację, czy operacja sie powiodla



    private:
        void loadArguments();
        bool isIlligal(); //czy pobrana do wykonania instrukcja była nielegalna
        void execution(); //wykonuje pobraną instrukcję - modyfikuje rdzeń


        CorePtr core_ptr_;

        InstructionRegister actual_ins_;

        ArgumentRegister arg_reg_A_, arg_reg_B_;
        PointerRegister ptr_reg_A_, ptr_reg_B_;
        AddressRegister adr_reg_A_, adr_reg_B_;
        ValueRegister val_reg_A_, val_reg_B_;

        ProgramCounter pc_;
    };



}

#endif // PROCESSOR_HPP
