#pragma once
#include "Command.hpp"  // 包含新的命令头文件
#include "Executor.hpp"
#include "PoseHandler.hpp"  // 包含姿态处理类头文件
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

    // 供命令类调用的方法
    bool IsFast(void) const noexcept
    {
        return fast;
    }
    void Fast(void) noexcept
    {
        fast = true;
    }
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void BackUp(void) noexcept;
    void UTurn(void) noexcept;

private:
    bool fast{false};
    Pose pose;
    PoseHandler poseHandler;
};
}  // namespace adas