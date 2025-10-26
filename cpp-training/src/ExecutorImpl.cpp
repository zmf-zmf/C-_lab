#include "ExecutorImpl.hpp"

#include <memory>
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto cmd : commands) {
        std::unique_ptr<ICommand> cmder;
        if (cmd == 'M') {
            cmder = std::make_unique<MoveCommand>();
        } else if (cmd == 'B') {
            // 后退指令
            cmder = std::make_unique<BackUpCommand>();
        } else if (cmd == 'L') {
            // 左转指令
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            // 右转指令
            cmder = std::make_unique<TurnRightCommand>();
        } else if (cmd == 'U') {
            // 调头指令
            cmder = std::make_unique<UTurnCommand>();
        } else if (cmd == 'F') {
            // 快速状态切换指令
            cmder = std::make_unique<FastCommand>();
        }
        if (cmder) {
            cmder->DoOperate(*this);
        }
        // 其他指令被忽略
    }
}
void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}
bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 'E') {
        ++pose.x;

    } else if (pose.heading == 'W') {
        --pose.x;

    } else if (pose.heading == 'N') {
        ++pose.y;

    } else if (pose.heading == 'S') {
        --pose.y;
    }
}
void ExecutorImpl::TurnLeft() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    } else if (pose.heading == 'E') {
        pose.heading = 'N';
    }
}
void ExecutorImpl::TurnRight() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'E';
    } else if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    }
}
void ExecutorImpl::BackUp() noexcept
{
    if (pose.heading == 'E') {
        --pose.x;
    } else if (pose.heading == 'W') {
        ++pose.x;
    } else if (pose.heading == 'N') {
        --pose.y;
    } else if (pose.heading == 'S') {
        ++pose.y;
    }
}
void ExecutorImpl::UTurn() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'N';
    } else if (pose.heading == 'E') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'E';
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
