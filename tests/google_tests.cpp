#include <gtest/gtest.h>
#include "user.h"

TEST(User, UserCreation) {
    User user{};
    EXPECT_TRUE(1 == 1);
}
