#pragma once
#include "Command.hpp"  // 包含新的命令头文件
#include "Executor.hpp"
#include "PoseHandler.hpp"  // 包含姿态处理类头文件
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose, ::adas::VehicleType type = ::adas::VehicleType::Racer) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

    // 供命令类调用的方法
    bool IsFast(void) const noexcept;
    void Fast(void) noexcept;
    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;
    void Forward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void UTurn(void) noexcept;
    void Backward(void) noexcept;

private:
    bool fast{false};
    bool reverse{false};
    Pose pose;
    PoseHandler poseHandler;
};
}  // namespace adas