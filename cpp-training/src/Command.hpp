#pragma once
#include <functional>

#include "ExecutorImpl.hpp"
#include "PoseHandler.hpp"
namespace adas
{

// class ICommand
// {
// public:
//     virtual ~ICommand() = default;
//     virtual void DoOperate(PoseHandler& executor) const noexcept = 0;
// };

class MoveCommand final  // : public ICommand
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.Move();
    };
};

class FastCommand final  // : public ICommand
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        poseHandler.Fast();
    };
};

class TurnLeftCommand final  // : public ICommand
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();
    };
};

class TurnRightCommand final  // : public ICommand
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    };
};

class BackUpCommand final  //: public ICommand
{
    // public:
    //     void DoOperate(PoseHandler& executor) const noexcept override
    //     {
    //         if (executor.IsFast()) {
    //             executor.BackUp();
    //         }
    //         executor.BackUp();
    //     }
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.BackUp();
        }
        poseHandler.BackUp();
    };
};

class UTurnCommand final  //: public ICommand
{
    // public:
    //     void DoOperate(PoseHandler& executor) const noexcept override
    //     {
    //         if (executor.IsFast()) {
    //             executor.Move();
    //         }
    //         executor.UTurn();
    //     }
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.UTurn();
    };
};

}  // namespace adas