
#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>

#include<random>
#include<iostream>
#include<stdexcept>

#include"../Arbiter/IntegerRegister.hpp"

using namespace boost::unit_test;
//using namespace boost::unit_test_framework;
using namespace arbiter;

const unsigned int MAX_COUNT = 100, ITERATIONS = 10;

int getModulo(const int MODULE, int value)
{
    if(value >= 0)
    {
        return value%MODULE;
    }
    else
    {
        while(value < 0)
        {
            value+=MODULE;//poczatkowo jest tam value, teraz zwiekszamy dopoki nie dostaniemy dodatniej liczby - i to bdzie nasz wynik
        }
        return value;
    }
}



BOOST_AUTO_TEST_SUITE( Integer_Register_Test )



BOOST_AUTO_TEST_CASE(GetModulo_function)
{
    int ret = getModulo(10, 104);
    BOOST_CHECK(ret == 4);
    ret = getModulo(10, -104);
    BOOST_CHECK(ret == 6);
}


BOOST_AUTO_TEST_CASE(Constructors)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);


    IntegerRegister int_1(MAX_COUNT), int_2(MAX_COUNT, 0);
//czy getter dziala poprawnie
    BOOST_CHECK(int_2.getValue() == 0);
    BOOST_CHECK(int_2.getSize() == MAX_COUNT);

    //czy konstruktor bez parametru value daje takie same rezultaty jak z value
    BOOST_CHECK(int_1.getSize()==int_2.getSize());
    BOOST_CHECK(int_1.getValue()==int_2.getValue());

    for(unsigned int i =0;i< ITERATIONS; ++i)
    {
        random_num = distribution(generator);
        std::cout<<std::endl<<random_num;

        IntegerRegister other(int_1), other_2(MAX_COUNT, random_num);
    //czy , jesli wylosujemy liczbe wieksza niz CORE_SIZE, to zainicjuje rejestr liczbą dodatnią mmodulo CORE_SIZE
        BOOST_CHECK(other.getValue() == int_1.getValue());
        BOOST_CHECK(other_2.getValue() == getModulo(MAX_COUNT, random_num));
        BOOST_CHECK(other.getSize() == other_2.getSize());
    }
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+30);
    int random_num = distribution(generator);


    IntegerRegister one(MAX_COUNT, 10), two(MAX_COUNT+10, 20), tree(one), four(MAX_COUNT);

    BOOST_CHECK_THROW(one=two, std::invalid_argument)
    BOOST_CHECK_NO_THROW(tree=four);

    tree.setValue(50);
    four.setValue(70);
    tree=four;
    BOOST_CHECK(tree.getValue() == 70);
    BOOST_CHECK(four.getValue() == 70);
    BOOST_CHECK(tree.getValue() == four.getValue());

    //sam do siebie
    tree.setValue(-33);
    tree=tree;
    BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, -33));

    for(unsigned int i=0;i<ITERATIONS;++i)
    {
        random_num=distribution(generator);
        four.setValue(random_num);
        BOOST_CHECK(four.getValue() == getModulo(MAX_COUNT, random_num));
        tree=four;
        BOOST_CHECK(tree.getValue()==  getModulo(MAX_COUNT, random_num));
    }
}

BOOST_AUTO_TEST_CASE(Adding)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);

    IntegerRegister one(MAX_COUNT), two(MAX_COUNT, 5), tree(MAX_COUNT);
//dodawanie
    tree.setValue(50);
    one = two+tree;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, 50+5 ));
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 5);

    for(unsigned int i=0;i<ITERATIONS;++i)
    {
        random_num = distribution(generator);
        tree.setValue(random_num);
        one = two+tree;
        BOOST_CHECK(one.getValue() == (getModulo(MAX_COUNT, tree.getValue()+5) ) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num));
        BOOST_CHECK(two.getValue() == 5);

        one = tree+two;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, tree.getValue()+5) ) ;
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num));
        BOOST_CHECK(two.getValue() == 5);
    }

}

BOOST_AUTO_TEST_CASE(Subracting)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);

    IntegerRegister one(MAX_COUNT), two(MAX_COUNT, 5), tree(MAX_COUNT);
//dodawanie
    tree.setValue(50);
    one = two-tree;
    std::cout<<std::endl<<std::endl<<one.getValue()<<std::endl;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT,(5-50)) );
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 5);

    for(unsigned int i=0;i<ITERATIONS;++i)
    {
        random_num = distribution(generator);
        tree.setValue(random_num);
        one = two-tree;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT,(5 - tree.getValue() ) ) );
        BOOST_CHECK(tree.getValue() ==  getModulo(MAX_COUNT,random_num));
        BOOST_CHECK(two.getValue() == 5);

        one = tree-two;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, (tree.getValue()-5 )) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num) );
        BOOST_CHECK(two.getValue() == 5);
    }


}

BOOST_AUTO_TEST_CASE(Incrementing)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);

    IntegerRegister one(MAX_COUNT), two(MAX_COUNT, 5), tree(MAX_COUNT);
//incrementacja
    tree.setValue(50);
    one = ++two;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, 5+1) );
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 6);

    tree.setValue(50);
    one = two++;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, 5+1) );
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 7);

    for(unsigned int i=0;i<ITERATIONS;++i)
    {
        random_num = distribution(generator);
        tree.setValue(random_num);
        one = ++tree;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, random_num+1) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num+1));

        one = tree++;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, random_num+1) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num+2) );

    }

}


BOOST_AUTO_TEST_CASE(Decrementing)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);

    IntegerRegister one(MAX_COUNT), two(MAX_COUNT, 5), tree(MAX_COUNT);
//incrementacja
    tree.setValue(50);
    one = --two;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, 5-1 ) );
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 5-1);

    tree.setValue(50);
    one = two--;
    BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, 5-1 ) );
    BOOST_CHECK(tree.getValue() == 50);
    BOOST_CHECK(two.getValue() == 5-2);

    for(unsigned int i=0;i<ITERATIONS;++i)
    {
        random_num = distribution(generator);
        tree.setValue(random_num);
        one = --tree;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, random_num-1 ) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num-1 ));

        one = tree--;
        BOOST_CHECK(one.getValue() == getModulo(MAX_COUNT, random_num-1 ) );
        BOOST_CHECK(tree.getValue() == getModulo(MAX_COUNT, random_num-2 ) );

    }

}

BOOST_AUTO_TEST_CASE(comparing)
{
    IntegerRegister one(MAX_COUNT, 5), invalid(MAX_COUNT+1, 5), two(MAX_COUNT,5);
    BOOST_CHECK_THROW(one==invalid, std::invalid_argument);
    BOOST_CHECK(one == two);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-MAX_COUNT,MAX_COUNT+50);
    int random_num = distribution(generator);

    for(int i = 0;i<20;++i)
    {
        random_num = distribution(generator);
        one.setValue(random_num);
        two.setValue(random_num+1);
        BOOST_CHECK(!(one==two));

        two.setValue(random_num);
        BOOST_CHECK(one == two);
    }

}

BOOST_AUTO_TEST_CASE(All_other)
{
    //czy gdy wstawimy ujemna wartosc to da nam modulo tej wartosci
    //to wazne gdy argument bedzie ujemny w instrukcji, np. skoku, aby odwołanie nastąpiło do odpowiedniej komórki rdzenia
    int value_ = -2, this_addr = 3;
    IntegerRegister this_address(MAX_COUNT, this_addr), arg_address(MAX_COUNT, value_), result(MAX_COUNT);

    result = this_address+arg_address;

    BOOST_CHECK(arg_address.getValue() == getModulo(MAX_COUNT, value_) );
    BOOST_CHECK(result.getValue() == this_addr+value_ );

    value_ = -13;
    arg_address.setValue(value_);
    result = this_address+arg_address;

    BOOST_CHECK(arg_address.getValue() == getModulo(MAX_COUNT, value_) );
    BOOST_CHECK(result.getValue() == 90 );//ten wzor jest prawdziwy tylko dla danych  - value_ =-13, this_adr = 3, MAX = 100



}


BOOST_AUTO_TEST_SUITE_END()
