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

class MoveCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.Backward();
        } else {
            poseHandler.Forward();
        }
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
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();

            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();

        } else {
            poseHandler.TurnLeft();
        }
    };
};

class TurnRightCommand final  // : public ICommand
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
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
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.Backward();
        } else {
            poseHandler.Forward();
        }
        poseHandler.UTurn();
    };
};

}  // namespace adas