#include <gtest/gtest.h>
#include <string>

#include "MyDynamicArray.h"

// the following file tests the iterator MyDynamicArray<T>::Iterator

TEST(MyDynamicArrayTest, aggregation) {
    MyDynamicArray<std::string> individual_strings(4);
    individual_strings.insert("Hello, ");
    individual_strings.insert("world, ");
    individual_strings.insert("this ");
    individual_strings.insert("message ");
    individual_strings.insert("should ");
    individual_strings.insert("be ");
    individual_strings.insert("joined.");
    
    std::string result = "";
    for(auto s : individual_strings) {
        result += s;
    }

    EXPECT_EQ(result, "Hello, world, this message should be joined.");
}

TEST(MyDynamicArrayTest, yodaAggregation) {
    MyDynamicArray<std::string> individual_strings(4);
    individual_strings.insert("Hello, ");
    individual_strings.insert("world, ");
    individual_strings.insert("this ");
    individual_strings.insert("message ");
    individual_strings.insert("should ");
    individual_strings.insert("be ");
    individual_strings.insert("reversed.");
    
    std::string result = "";
    for(auto it = individual_strings.rbegin(); it != individual_strings.rend(); ++it) {
        result += *it;
    }

    EXPECT_EQ(result, "reversed.be should message this world, Hello, ");
}
