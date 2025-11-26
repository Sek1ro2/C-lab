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
                Move();
            }
            else if (cmd == 'L')
            {
                TurnLeft();
            }
            else if (cmd == 'R')
            {
                TurnRight();
            }
        }
    }

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

    void ExecutorImpl::TurnLeft(void) noexcept
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

    void ExecutorImpl::TurnRight(void) noexcept
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