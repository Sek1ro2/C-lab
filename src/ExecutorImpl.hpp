#pragma once

#include "Executor.hpp"
#include <string>
#include <memory>

namespace adas
{
    class ExecutorImpl : public Executor
    {
    public:
        explicit ExecutorImpl(const Pose &pose) noexcept;
        ~ExecutorImpl() noexcept = default;
        ExecutorImpl(const ExecutorImpl &) = delete;
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

        Pose Query(void) const noexcept override;
        void Execute(const std::string &commands) noexcept override;

    private:
        void Move(void) noexcept;
        void Move(int steps) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;

        class Command
        {
        public:
            virtual ~Command() = default;
            virtual void DoOperate(ExecutorImpl &executor) const noexcept = 0;
        };

        class MoveCommand final : public Command
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override;
        };

        class TurnLeftCommand final : public Command
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override;
        };

        class TurnRightCommand final : public Command
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override;
        };

        class ForwardCommand final : public Command
        {
        public:
            explicit ForwardCommand(int steps) noexcept : steps_(steps) {}
            void DoOperate(ExecutorImpl &executor) const noexcept override;

        private:
            int steps_;
        };

        static std::unique_ptr<Command> CreateCommand(char cmd, int steps = 1);

        Pose pose;
    };
}