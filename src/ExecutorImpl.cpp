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
            std::unique_ptr<Command> cmder;
            if (cmd == 'M')
            {
                cmder = std::make_unique<MoveCommand>();
            }
            else if (cmd == 'L')
            {
                cmder = std::make_unique<TurnLeftCommand>();
            }
            else if (cmd == 'R')
            {
                cmder = std::make_unique<TurnRightCommand>();
            }
            if (cmder)
            {
                cmder->DoOperate(*this);
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

    void ExecutorImpl::MoveCommand::DoOperate(ExecutorImpl &executor) const noexcept
    {
        executor.Move();
    }

    void ExecutorImpl::TurnLeftCommand::DoOperate(ExecutorImpl &executor) const noexcept
    {
        executor.TurnLeft();
    }

    void ExecutorImpl::TurnRightCommand::DoOperate(ExecutorImpl &executor) const noexcept
    {
        executor.TurnRight();
    }
}
