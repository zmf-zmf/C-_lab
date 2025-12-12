#include "ExecutorImpl.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>

#include "CmderFactory.hpp"
#include "Singleton.hpp"
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose, ::adas::VehicleType type) noexcept : poseHandler(pose, type)
{
}

// // std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap;
// // cmderMap.emplace('M', MoveCommand());
// // cmderMap.emplace('L', TurnLeftCommand());
// // cmderMap.emplace('R', TurnRightCommand());
// // cmderMap.emplace('F', FastCommand());
// // cmderMap.emplace('B', BackUpCommand());
// // cmderMap.emplace('U', UTurnCommand());
// const std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap{
//     {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
//     {'F', FastCommand()}, {'U', UTurnCommand()},    {'B', ReverseCommand()},
// };

// for (const auto cmd : commands) {
//     const auto it = cmderMap.find(cmd);
//     if (it != cmderMap.end()) {
//         it->second(poseHandler);
//     }
// }
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    CmderFactory cf;
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

    std::for_each(cmders.begin(), cmders.end(), [this](const Cmder& cmder) noexcept { cmder(poseHandler); });
}

void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}
bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

void ExecutorImpl::Reverse() noexcept
{
    reverse = !reverse;
}
bool ExecutorImpl::IsReverse() const noexcept
{
    return reverse;
}

void ExecutorImpl::Forward() noexcept
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
void ExecutorImpl::Backward() noexcept
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
    return poseHandler.Query();
}
}  // namespace adas
