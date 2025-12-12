#pragma once
#include <functional>

#include "PoseHandler.hpp"
namespace adas
{

// class ICommand
// {
// public:
//     virtual ~ICommand() = default;
//     virtual void DoOperate(PoseHandler& executor) const noexcept = 0;
// };

class MoveCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        poseHandler.MoveAction();
    }
};

class FastCommand final  // : public ICommand
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    };
};
class ReverseCommand final  // : public ICommand
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    };
};

class TurnLeftCommand final  // : public ICommand
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeftAction();
    };
};

class TurnRightCommand final  // : public ICommand
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRightAction();
    }
};

class UTurnCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.UTurnAction();
    };
};

}  // namespace adas