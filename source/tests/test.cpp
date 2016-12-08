#include "CppUTest/TestHarness.h"

TEST_GROUP(ExampleTests)
{
};


TEST(ExampleTests, Example1)
{
    CHECK_EQUAL(1+1, 2);
}