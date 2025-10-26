#pragma once
#include "Executor.hpp"
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

private:
    Pose pose;
    class MoveCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept

        {
            executor.Move();
        }
    };
    class TurnLeftCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept

        {
            executor.TurnLeft();
        }
    };
    class TurnRightCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept

        {
            executor.TurnRight();
        }
    };
    class BackUpCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept

        {
            executor.BackUp();
        }
    };
    class UTurnCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept

        {
            executor.UTurn();
        }
    };
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void BackUp(void) noexcept;
    void UTurn(void) noexcept;
};
}  // namespace adas
