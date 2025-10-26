#pragma once
#include "ExecutorImpl.hpp"
#include "PoseHandler.hpp"
namespace adas
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(PoseHandler& executor) const noexcept = 0;
};

class FastCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        executor.Fast();
    }
};

class MoveCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();
        }
        executor.Move();
    }
};

class TurnLeftCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();
        }
        executor.TurnLeft();
    }
};

class TurnRightCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();
        }
        executor.TurnRight();
    }
};

class BackUpCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.BackUp();
        }
        executor.BackUp();
    }
};

class UTurnCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();
        }
        executor.UTurn();
    }
};

}  // namespace adas