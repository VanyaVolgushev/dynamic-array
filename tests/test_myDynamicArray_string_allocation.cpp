#include <gtest/gtest.h>
#include <string>

#include "MyDynamicArray.h"

// the following file tests the string allocation and deallocation
// functionalities of the myDynamicArray class.

TEST(MyDynamicArrayStringAllocationTest, AllocateAndDeallocateStrings) {
    MyDynamicArray<std::string> stringArray;

    stringArray.insert("Hello");
    stringArray.insert("World");
    stringArray.insert("Test");

    EXPECT_EQ(stringArray.size(), 3);
    EXPECT_EQ(stringArray[0], "Hello");
    EXPECT_EQ(stringArray[1], "World");
    EXPECT_EQ(stringArray[2], "Test");

    stringArray.remove(2);
    EXPECT_EQ(stringArray.size(), 2);
    EXPECT_EQ(stringArray[0], "Hello");
    EXPECT_EQ(stringArray[1], "World");
}

TEST(MyDynamicArrayStringAllocationTest, InsertAtSpecificIndex) {
    MyDynamicArray<std::string> stringArray;

    stringArray.insert("First");
    stringArray.insert("Second");
    stringArray.insert("Fourth");

    stringArray.insert(2, "Third");

    EXPECT_EQ(stringArray.size(), 4);
    EXPECT_EQ(stringArray[0], "First");
    EXPECT_EQ(stringArray[1], "Second");
    EXPECT_EQ(stringArray[2], "Third");
    EXPECT_EQ(stringArray[3], "Fourth");
}

TEST(MyDynamicArrayStringAllocationTest, ResizingArray) {
    MyDynamicArray<std::string> stringArray(2); // Start with small capacity

    stringArray.insert("One");
    stringArray.insert("Two");
    stringArray.insert("Three"); // This should trigger a resize

    EXPECT_EQ(stringArray.size(), 3);
    EXPECT_EQ(stringArray.capacity(), 4);
    EXPECT_EQ(stringArray[0], "One");
    EXPECT_EQ(stringArray[1], "Two");
    EXPECT_EQ(stringArray[2], "Three");
}