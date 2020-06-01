#include "custom_allocator.h"

#include <gtest/gtest.h>
/*
TEST(test_version, test_version)
{
    ASSERT_TRUE(NHelloWorld::GetVersion() > 0);
} */

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
