#ifndef SMARTIN3D_INPUT_H
#define SMARTIN3D_INPUT_H

#define KEYS_NUMBER 348

#include "precompiled.h"

#include "graphics/Window.h"
#include "TimeUtils.h"

namespace smartin::utils::input {
    enum KeyCode : int;

    void Init(std::shared_ptr<graphics::Window> window);
    void Update();

    namespace keyboard {
        void Init(GLFWwindow* window);
        void Update();

        bool IsKey(KeyCode key);
        bool IsKeyUp(KeyCode key);
        bool IsKeyDown(KeyCode key);
    }

    namespace mouse {
        void Init(GLFWwindow* window);
        void Update();

        glm::vec2 GetCursorPosition();
        glm::vec2 GetCursorDelta();

        namespace settings {
            static bool invertYAxis = false;
            static bool showCursor = false;
        }
    }

    namespace gamepad {
        void Init(GLFWwindow* window);
        void Update();

        // TODO
    }
}

// Stolen from glfw3.h
enum smartin::utils::input::KeyCode : int {
    // Printable keys
    space         = 32,
    apostrophe    = 39,  // '
    comma         = 44,  // ,
    minus         = 45,  // -
    period        = 46,  // .
    slash         = 47,  // /
    n0            = 48,
    n1            = 49,
    n2            = 50,
    n3            = 51,
    n4            = 52,
    n5            = 53,
    n6            = 54,
    n7            = 55,
    n8            = 56,
    n9            = 57,
    semicolon     = 59,  // ;
    equal         = 61,  // =
    a             = 65,
    b             = 66,
    c             = 67,
    d             = 68,
    e             = 69,
    f             = 70,
    g             = 71,
    h             = 72,
    i             = 73,
    j             = 74,
    k             = 75,
    l             = 76,
    m             = 77,
    n             = 78,
    o             = 79,
    p             = 80,
    q             = 81,
    r             = 82,
    s             = 83,
    t             = 84,
    u             = 85,
    v             = 86,
    w             = 87,
    x             = 88,
    y             = 89,
    z             = 90,
    l_bracket     = 91,  // [
    backslash     = 92,
    r_bracket     = 93,  // ]
    grave_accent  = 96,  // `
    world_1       = 161, // non-us #1
    world_2       = 162, // non-us #2

    // Function keys
    esc          = 256,
    enter        = 257,
    tab          = 258,
    backspace    = 259,
    insert       = 260,
    del          = 261,
    right        = 262,
    left         = 263,
    down         = 264,
    up           = 265,
    page_up      = 266,
    page_down    = 267,
    home         = 268,
    end          = 269,
    caps_lock    = 280,
    scroll_lock  = 281,
    num_lock     = 282,
    print_screen = 283,
    pause        = 284,
    f1           = 290,
    f2           = 291,
    f3           = 292,
    f4           = 293,
    f5           = 294,
    f6           = 295,
    f7           = 296,
    f8           = 297,
    f9           = 298,
    f10          = 299,
    f11          = 300,
    f12          = 301,
    f13          = 302,
    f14          = 303,
    f15          = 304,
    f16          = 305,
    f17          = 306,
    f18          = 307,
    f19          = 308,
    f20          = 309,
    f21          = 310,
    f22          = 311,
    f23          = 312,
    f24          = 313,
    f25          = 314,
    kp_0         = 320,
    kp_1         = 321,
    kp_2         = 322,
    kp_3         = 323,
    kp_4         = 324,
    kp_5         = 325,
    kp_6         = 326,
    kp_7         = 327,
    kp_8         = 328,
    kp_9         = 329,
    kp_decimal   = 330,
    kp_divide    = 331,
    kp_multiply  = 332,
    kp_subtract  = 333,
    kp_add       = 334,
    kp_enter     = 335,
    kp_equal     = 336,
    l_shift      = 340,
    l_ctrl       = 341,
    l_alt        = 342,
    l_super      = 343,
    r_shift      = 344,
    r_ctrl       = 345,
    r_alt        = 346,
    r_super      = 347,
    menu         = 348
};

#endif //SMARTIN3D_INPUT_H