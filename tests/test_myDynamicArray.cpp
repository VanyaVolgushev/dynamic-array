#include <gtest/gtest.h>
#include "myDynamicArray.h"

TEST(MyDynamicArrayTest, DefaultConstructor) {
    MyDynamicArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 16);
}

TEST(MyDynamicArrayTest, ParameterizedConstructor) {
    MyDynamicArray<int> arr(32);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 32);
}

TEST(MyDynamicArrayTest, PushBackAndAccess) {
    MyDynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}