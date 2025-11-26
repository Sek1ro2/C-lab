#include "ExecutorImpl.hpp"

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        for (const auto cmd : commands)
        {
            if (cmd == 'M')
            {
                // 仅修改这一行：调用抽取的Move方法（替代原有逻辑）
                Move();
            }
            else if (cmd == 'L')
            {
                
                if (pose.heading == 'E')
                    pose.heading = 'N';
                else if (pose.heading == 'N')
                    pose.heading = 'W';
                else if (pose.heading == 'W')
                    pose.heading = 'S';
                else if (pose.heading == 'S')
                    pose.heading = 'E';
            }
            else if (cmd == 'R')
            {
                
                if (pose.heading == 'E')
                    pose.heading = 'S';
                else if (pose.heading == 'S')
                    pose.heading = 'W';
                else if (pose.heading == 'W')
                    pose.heading = 'N';
                else if (pose.heading == 'N')
                    pose.heading = 'E';
            }
        }
    }

    // 仅新增这一段：Move方法实现（从原有M指令逻辑抽取）
    void ExecutorImpl::Move(void) noexcept
    {
        if (pose.heading == 'E')
            ++pose.x;
        else if (pose.heading == 'W')
            --pose.x;
        else if (pose.heading == 'N')
            ++pose.y;
        else if (pose.heading == 'S')
            --pose.y;
    }
}