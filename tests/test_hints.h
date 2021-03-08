#ifndef SMARTIN3D_TEST_HINTS_H
#define SMARTIN3D_TEST_HINTS_H

#include <catch2/catch.hpp>
#include <cmath>
#include <glm/glm.hpp>

#define REQUIRE_EQ(x, y) REQUIRE(x == y)
#define REQUIRE_EQ_FLOAT(x, y, a) REQUIRE(std::abs(x - y) < a)
#define REQUIRE_EQ_VEC3(v1, v2, a) REQUIRE((std::abs(v1.x - v2.x) < a && std::abs(v1.y - v2.y) < a && std::abs(v1.z - v2.z) < a))
#define REQUIRE_EQ_VEC4(v1, v2, a) REQUIRE((std::abs(v1.x - v2.x) < a && std::abs(v1.y - v2.y) < a && std::abs(v1.z - v2.z) < a && std::abs(v1.w - v2.w) < a))

#endif //SMARTIN3D_TEST_HINTS_H
