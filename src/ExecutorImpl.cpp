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
            std::unique_ptr<Command> cmder = CreateCommand(cmd);
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

    std::unique_ptr<ExecutorImpl::Command> ExecutorImpl::CreateCommand(char cmd)
    {
        switch (cmd)
        {
        case 'M':
            return std::make_unique<MoveCommand>();
        case 'L':
            return std::make_unique<TurnLeftCommand>();
        case 'R':
            return std::make_unique<TurnRightCommand>();
        default:
            return nullptr;
        }
    }
}