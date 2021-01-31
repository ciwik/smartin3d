#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "STime.h"

int sum(int a, int b) { return a + b; }

TEST_CASE("A+B") {
    REQUIRE(sum(3, 5) == 8);
    smartin::utils::time::GetDeltaTime();
}