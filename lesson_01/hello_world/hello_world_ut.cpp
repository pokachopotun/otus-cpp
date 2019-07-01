#define BOOST_TEST_MODULE test_version

#include "hello_world.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(hello_world_ut)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
	BOOST_CHECK(NHelloWorld::GetVersion() > 0);
}

}
