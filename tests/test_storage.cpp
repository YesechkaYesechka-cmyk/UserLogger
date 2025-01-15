#include <set>

#include  <gtest/gtest.h>
#include "storage.h"
#include "utils.h"
#include "log_session.h"

TEST(TEST_STORAGE, STORAGE_CREATOR) {
#include <string>
#include <vector>

    struct TestStruct {
        int id;
        std::string value;
        std::vector<std::string> params;
    };

    TestStruct ts_1{1, "value_1", {"arg_1", "arg_2"}};
    TestStruct ts_2{2, "value_2", {"param_1", "arg_2"}};
    TestStruct ts_3{3, "value_3", {"args"}};

    auto comparator = [](const TestStruct &l, const TestStruct &r) {
        return l.params.at(0) < r.params.at(0);
    };

    std::set<TestStruct, decltype(comparator)> ts_set{{ts_1, ts_2, ts_3}, comparator};

    for (const auto &ts: ts_set) {
        std::cout << ts.id << " " << ts.value << std::endl;
    }
}

TEST(GetMonthIntegerTest, ValidMonths) {

    EXPECT_EQ(GetMonthInteger("Jan"), Months::JAN);
    EXPECT_EQ(GetMonthInteger("Feb"), Months::FEB);
    EXPECT_EQ(GetMonthInteger("Mar"), Months::MAR);
    EXPECT_EQ(GetMonthInteger("Apr"), Months::APR);
    EXPECT_EQ(GetMonthInteger("May"), Months::MAY);
    EXPECT_EQ(GetMonthInteger("Jun"), Months::JUN);
    EXPECT_EQ(GetMonthInteger("Jul"), Months::JUL);
    EXPECT_EQ(GetMonthInteger("Aug"), Months::AUG);
    EXPECT_EQ(GetMonthInteger("Sep"), Months::SEP);
    EXPECT_EQ(GetMonthInteger("Oct"), Months::OCT);
    EXPECT_EQ(GetMonthInteger("Nov"), Months::NOV);
    EXPECT_EQ(GetMonthInteger("Dec"), Months::DEC);
}

TEST(GetMonthIntegerTest, InvalidMonths) {

    EXPECT_THROW(GetMonthInteger("January"), std::invalid_argument);
    EXPECT_THROW(GetMonthInteger(""), std::invalid_argument);
    EXPECT_THROW(GetMonthInteger("XYZ"), std::invalid_argument);
    EXPECT_THROW(GetMonthInteger("jan"), std::invalid_argument);
}


TEST(DateComparatorTests, CompareByMonth) {
    Date date1("Mon Jul  8 21:31");
    Date date2("Sun Jun  2 00:40");
    EXPECT_FALSE(date1 < date2);
    EXPECT_TRUE(date2 < date1);
}

TEST(DateComparatorTests, CompareByDay) {
    Date date1("Mon Jun  8 21:31");
    Date date2("Sun Jun  2 00:40");
    EXPECT_TRUE(date2 < date1);
    EXPECT_FALSE(date1 < date2);
}

TEST(DateComparatorTests, CompareByHour) {
    Date date1("Mon Jun  2 21:31");
    Date date2("Sun Jun  2 19:40");
    EXPECT_FALSE(date1 < date2);
    EXPECT_TRUE(date2 < date1);
}


TEST(DateComparatorTests, CompareByMinutes) {
    Date date1("Mon Jun  2 21:31");
    Date date2("Sun Jun  2 21:40");
    EXPECT_TRUE(date1 < date2);
    EXPECT_FALSE(date2 < date1);
}


TEST(DateComparatorTests, EqualDates) {
    Date date1("Mon Jun  2 21:31");
    Date date2("Mon Jun  2 21:31");
    EXPECT_FALSE(date1 < date2);
    EXPECT_FALSE(date2 < date1);
}

