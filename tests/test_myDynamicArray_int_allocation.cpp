#include <gtest/gtest.h>
#include "MyDynamicArray.h"

TEST(MyDynamicArrayTest, DefaultConstructor) {
    MyDynamicArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 16);
}

TEST(MyDynamicArrayTest, ParameterizedConstructor) {
    MyDynamicArray<int> arr(33);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 33);
}

TEST(MyDynamicArrayTest, PushBackAndAccess) {
    MyDynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(MyDynamicArrayTest, InsertAtMiddle) {
    MyDynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(1, 15);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 15);
    EXPECT_EQ(arr[2], 20);
}

TEST(MyDynamicArrayTest, RemoveElement) {
    MyDynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST(MyDynamicArrayTest, ResizeOnInsert) {

    MyDynamicArray<int> arr(2);
    // insert 16 elements
    for (int i = 1; i <= 16; i++) {
        arr.insert(i * 10);
    }

    EXPECT_EQ(arr.size(), 16);
    EXPECT_EQ(arr.capacity(), 16);
    
    //insert another element at index 1
    arr.insert(1, 1337);
    EXPECT_EQ(arr.size(), 17);
    EXPECT_EQ(arr.capacity(), 32);
    
    for (int i = 0; i < 16; i++) {
        if (i == 0) {
            EXPECT_EQ(arr[i], 10);
        } else if (i == 1) {
            EXPECT_EQ(arr[i], 1337);
        } else {
            EXPECT_EQ(arr[i], (i) * 10);
        }
    }
}

TEST(MyDynamicArrayTest, ConstAccess) {
    MyDynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    const MyDynamicArray<int>& constArr = arr;
    EXPECT_EQ(constArr[0], 10);
    EXPECT_EQ(constArr[1], 20);
}
