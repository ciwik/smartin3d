#ifndef SMARTIN3D_TEST_HINTS_H
#define SMARTIN3D_TEST_HINTS_H

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cmath>

#include <glm/glm.hpp>

#define REQUIRE_EQ(x, y) REQUIRE(x == y)
#define REQUIRE_EQ_FLOAT(x, y, a) REQUIRE(std::abs(x - y) < a)
#define REQUIRE_EQ_VEC(v1, v2, a) REQUIRE((std::abs(v1.x - v2.x) < a && std::abs(v1.y - v2.y) < a && std::abs(v1.z - v2.z) < a))

#endif //SMARTIN3D_TEST_HINTS_H
