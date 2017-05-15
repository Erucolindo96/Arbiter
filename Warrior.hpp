#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include<vector>
#include"Instruction.hpp"
#include"Warrior.hpp"

namespace arbiter
{

class Instruction;

/**
     * @brief The Warrior struct Struktura przechowująca kod wojownika.
     * Wykorzystuje ją Arbiter oraz CoreCreator do tworzenia rdzenia.
     *
     * Klasa nie ma składowych prywatnych, ponieważ unique_ptry przechowywane w vectorze nie maja konstruktora kopiującego - co nie pozwala zwracać skopiowanego vectora przez wartość.
     * Każdy, kto chce dostać kopię Warriora musi sam zadbać o napisanie funkcji kopiującej jego kod.
     *
     * Działa natomiast konstruktor kopiujący,settery oraz getter nazwy wojownika, i jego również można używać do kopiowania.
     */
    struct Warrior
    {
    public:
        typedef std::unique_ptr<Instruction> InsPtr;

        Warrior();
        Warrior(const std::string &name,const  std::vector<InsPtr> &code_of_warrior);
        Warrior(const Warrior &other);


        /**
          Cholera wie jak to sie zachowa, lepiej nie używać
          Ale teraz uzywa konstrukotra przenoszącego vectora, to moze bedzie lepiej
         */
        Warrior(const std::string &name, std::vector<InsPtr> &&code_of_warrior);



        Warrior& operator=(const Warrior &other);

        std::string getName()const;

        void setName(const std::string &name);
        void setInstructions(const std::vector<InsPtr> &instructions);

        std::vector<InsPtr> instuctions_;
        std::string name_;


    };



}

#endif // WARRIOR_HPP
