#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK


#include<boost/test/test_tools.hpp>
#include<boost/test/unit_test.hpp>
#include<boost/test/auto_unit_test.hpp>
#include<boost/test/unit_test_log.hpp>


using namespace boost::unit_test;
//using namespace boost::unit_test_framework;


BOOST_AUTO_TEST_SUITE( Integer_Register_Test )


BOOST_AUTO_TEST_CASE(Pierwszy_test)
{
    BOOST_REQUIRE(1==1);

}


BOOST_AUTO_TEST_SUITE_END()
