#include "gtest/gtest.h"
#include "example.h"

TEST(AddTest, CanPass) {
    EXPECT_EQ(1, sum(0, 1));
}

TEST(AddTest2, CanPass) {
    EXPECT_EQ(-1, minus(0, 1));
}

class MyTestFixture : public ::testing::Test {
public:
    MyTestFixture() {

    }
    void SetUp()
    {
        printf("[%s:%d]\n", __FUNCTION__, __LINE__);
    }

    void TearDown()
    {
        printf("[%s:%d]\n", __FUNCTION__, __LINE__);
    }

    int sum(int a, int b)
    {
        return (a + b);
    }
};

TEST_F(MyTestFixture, TestSum)
{
    ASSERT_GT(10, sum(1, 2));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
