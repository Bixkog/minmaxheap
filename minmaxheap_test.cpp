#include <algorithm>
#include <gtest/gtest.h>
#include "minmaxheap.h"

class minmaxheap_test : public ::testing::Test
{
public:
    void SetUp()
    {
        std::vector<int> v{1,2,3,4};
        sut = minmaxheap<int>(v);
    }

    minmaxheap<int> sut;
};


TEST_F(minmaxheap_test, BASEMIN)
{
    for(int i = 1; i < 5; i++)
    {
        int out = sut.popMin();
        EXPECT_EQ(i, out);
    }
    EXPECT_TRUE(sut.empty());
}

TEST_F(minmaxheap_test, BASEMAX)
{
    for(int i = 4; i > 0; i--)
    {
        int out = sut.popMax();
        EXPECT_EQ(i, out);
    }
    EXPECT_TRUE(sut.empty());
}

TEST_F(minmaxheap_test, INSERTMIN)
{
    sut.insert(0);
    int out = sut.popMin();
    EXPECT_EQ(0, out);
}

TEST_F(minmaxheap_test, INSERTMAX)
{
    sut.insert(5);
    int out = sut.popMax();
    EXPECT_EQ(5, out);
}

TEST_F(minmaxheap_test, CREATION)
{
    std::vector<int> v{12,34,1,23,42,153,22,16,21,34,2,3,
        72,6,12,30,5,23,41,29,4,10,38,27,35,123,343,123,432,23};
    sut = minmaxheap<int>(v);
    std::sort(v.begin(), v.end());
    for(int e : v)
    {
        int res = sut.popMin();
        EXPECT_EQ(e, res);
    }
    EXPECT_TRUE(sut.empty());
}

