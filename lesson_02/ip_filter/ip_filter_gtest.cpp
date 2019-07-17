#include "ip_filter.h"

#include <gtest/gtest.h>

#include <sstream>

using namespace NIpFilter;
using namespace std;

TEST(test_ip_filter, test_version)
{
    ASSERT_TRUE(NIpFilter::GetVersion() > 0);
}

TEST(test_ip_filter, test_ip_comparison)
{
    const IpAddress a1 = {1,1,1,1};
    const IpAddress a2 = {1,2,1,1};
    const IpAddress a3 = {1,2,3,4};
    const IpAddress a4 = {0,2,4,3};
    const IpAddress a5 = {1,2,4,3};

    ASSERT_FALSE(a1 < a1);

    ASSERT_TRUE(a1 < a2);
    ASSERT_FALSE(a2 < a1);

    ASSERT_TRUE(a4 < a1);
    ASSERT_FALSE(a1 < a4);

    ASSERT_TRUE(a3 < a5);
    ASSERT_FALSE(a5 < a3);
}

TEST(test_ip_filter, test_ip_io)
{
    const string str1 = "1.1.1.1";
    const string str2 = "1.1.1.1\t2\t3";

    const IpAddress a1 = {1,1,1,1};

    IpAddress a2;
    stringstream ss1(str1);
    ss1 >> a2;
    ASSERT_TRUE(a2 == a1);

    IpAddress a3;
    stringstream ss2(str2);
    ss2 >> a3;
    ASSERT_TRUE(a3 == a1);

    stringstream ss3;
    ss3 << a3;
    ASSERT_TRUE(str1 == ss3.str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
