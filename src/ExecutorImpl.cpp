#include "ExecutorImpl.hpp"
#include <cctype>
#include <algorithm>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        for (size_t i = 0; i < commands.size();)
        {
            char cmd = std::toupper(commands[i]);
            if (!IsValidCommand(cmd))
            {
                ++i;
                continue;
            }

            if (cmd == 'F')
            {
                int steps = 0;
                ++i;
                while (i < commands.size() && std::isdigit(commands[i]))
                {
                    steps = steps * 10 + (commands[i] - '0');
                    ++i;
                }
                std::unique_ptr<Command> cmder = CreateCommand('F', steps > 0 ? steps : 1);
                if (cmder)
                    cmder->DoOperate(*this);
            }
            else
            {
                std::unique_ptr<Command> cmder = CreateCommand(cmd);
                if (cmder)
                    cmder->DoOperate(*this);
                ++i;
            }
        }
    }

    void ExecutorImpl::Move(void) noexcept
    {
        Move(1);
    }

    void ExecutorImpl::Move(int steps) noexcept
    {
        int abs_steps = std::abs(steps);
        for (int i = 0; i < abs_steps; ++i)
        {
            if (pose.heading == 'E')
                pose.x += steps > 0 ? 1 : -1;
            else if (pose.heading == 'W')
                pose.x += steps > 0 ? -1 : 1;
            else if (pose.heading == 'N')
                pose.y += steps > 0 ? 1 : -1;
            else if (pose.heading == 'S')
                pose.y += steps > 0 ? -1 : 1;
        }
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

    void ExecutorImpl::ForwardCommand::DoOperate(ExecutorImpl &executor) const noexcept
    {
        executor.Move(steps_);
    }

    std::unique_ptr<ExecutorImpl::Command> ExecutorImpl::CreateCommand(char cmd, int steps)
    {
        switch (cmd)
        {
        case 'M':
            return std::make_unique<MoveCommand>();
        case 'L':
            return std::make_unique<TurnLeftCommand>();
        case 'R':
            return std::make_unique<TurnRightCommand>();
        case 'F':
            return std::make_unique<ForwardCommand>(steps);
        default:
            return nullptr;
        }
    }

    bool ExecutorImpl::IsValidCommand(char cmd) noexcept
    {
        return cmd == 'M' || cmd == 'L' || cmd == 'R' || cmd == 'F';
    }
}