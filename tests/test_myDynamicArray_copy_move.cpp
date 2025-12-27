#include "MyDynamicArray.h"
#include <gtest/gtest.h>
#include <string>

TEST(MyDynamicArrayCopyTest, CopyConstructorWithStrings) {
    MyDynamicArray<std::string> a;
    a.insert(std::string("one"));
    a.insert(std::string("two"));
    a.insert(std::string("three"));

    // copy-construct
    MyDynamicArray<std::string> b(a);

    // sizes should match
    ASSERT_EQ(a.size(), b.size());
    ASSERT_EQ(a.capacity(), b.capacity());

    // elements should be equal
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }

    // modifying original should not change the copy (deep copy)
    a[0] = "changed";
    EXPECT_EQ(b[0], "one");
    EXPECT_EQ(a[0], "changed");
}

TEST(MyDynamicArrayMoveTest, MoveConstructorWithStrings) {
    MyDynamicArray<std::string> a;
    a.insert(std::string("alpha"));
    a.insert(std::string("beta"));
    a.insert(std::string("gamma"));

    // move-construct
    MyDynamicArray<std::string> moved(std::move(a));

    // moved should have elements
    ASSERT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[0], "alpha");
    EXPECT_EQ(moved[1], "beta");
    EXPECT_EQ(moved[2], "gamma");

    // original should be in a valid empty state
    EXPECT_EQ(a.size(), 0u);
    EXPECT_EQ(a.capacity(), 0u);
}
