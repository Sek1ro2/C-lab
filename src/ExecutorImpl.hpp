#pragma once

#include "Executor.hpp"
#include <string>

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
        // 仅新增这一行：Move方法声明（实验二第一步唯一修改）
        void Move(void) noexcept;

        Pose pose;
    };
}