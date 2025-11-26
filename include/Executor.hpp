#pragma once

#include <string>

namespace adas
{
    struct Pose
    {
        int x{0};
        int y{0};
        char heading{'E'};
    };

    // PDF要求的PoseEq函数（非运算符重载，纯函数形式）
    inline bool PoseEq(const Pose &lhs, const Pose &rhs) noexcept
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.heading == rhs.heading;
    }

    class Executor
    {
    public:
        virtual ~Executor() = default;
        virtual Pose Query(void) const noexcept = 0;
        virtual void Execute(const std::string &commands) noexcept = 0;
        static Executor *NewExecutor(const Pose &pose) noexcept;
    };
}