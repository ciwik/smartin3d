#ifndef SMARTIN3D_TRANSFORM_TESTS_H
#define SMARTIN3D_TRANSFORM_TESTS_H

#include "test_hints.h"

#include "Transform.h"

TEST_CASE("Transform default constructor", "[require]") {
    smartin::base::Transform* transform = new smartin::base::Transform();

    REQUIRE_EQ(transform->GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE_EQ(transform->GetSize(), glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE_EQ(transform->GetEulerAngles(), glm::vec3(0.0f, 0.0f, 0.0f));

    REQUIRE_EQ(transform->GetRight(), glm::vec3(1.0f, 0.0f, 0.0f));
    REQUIRE_EQ(transform->GetUp(), glm::vec3(0.0f, 1.0f, 0.0f));
    REQUIRE_EQ(transform->GetForward(), glm::vec3(0.0f, 0.0f, 1.0f));

    delete transform;
}

TEST_CASE("Transform 90 degrees rotation", "[require]") {
    smartin::base::Transform* transform = new smartin::base::Transform();

    transform->RotateAround(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);

    REQUIRE_EQ(transform->GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE_EQ(transform->GetSize(), glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE_EQ_VEC3(transform->GetEulerAngles(), glm::vec3(0.0f, 90.0f, 0.0f), 1.0f);

    REQUIRE_EQ_VEC3(transform->GetRight(), glm::vec3(0.0f, 0.0f, -1.0f), 0.01f);
    REQUIRE_EQ_VEC3(transform->GetUp(), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);
    REQUIRE_EQ_VEC3(transform->GetForward(), glm::vec3(1.0f, 0.0f, 0.0f), 0.01f);

    delete transform;
}

TEST_CASE("Transform rotation by euler angles", "[require]") {
    smartin::base::Transform* transform = new smartin::base::Transform();
    REQUIRE_EQ_VEC4(transform->GetRotation(), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 0.01f);

    transform->Rotate(glm::vec3(90.0f, 0.0f, 0.0f));

    REQUIRE_EQ(transform->GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE_EQ(transform->GetSize(), glm::vec3(1.0f, 1.0f, 1.0f));

    REQUIRE_EQ_VEC3(transform->GetEulerAngles(), glm::vec3(90.0f, 0.0f, 0.0f), 1.0f);
    REQUIRE_EQ_VEC4(transform->GetRotation(), glm::quat(0.707f, 0.707f, 0.0f, 0.0f), 0.01f);

    REQUIRE_EQ_VEC3(transform->GetRight(), glm::vec3(1.0f, 0.0f, 0.0f), 0.01f);
    REQUIRE_EQ_VEC3(transform->GetUp(), glm::vec3(0.0f, 0.0f, 1.0f), 0.01f);
    REQUIRE_EQ_VEC3(transform->GetForward(), glm::vec3(0.0f, -1.0f, 0.0f), 0.01f);

    delete transform;
}


#endif //SMARTIN3D_TRANSFORM_TESTS_H