#pragma once
#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
class CmderFactory final
{
public:
    CmderFactory(void) noexcept = default;
    CmderFactory(const CmderFactory&) noexcept = delete;
    CmderFactory& operator=(const CmderFactory&) noexcept = delete;

public:
    std::list<std::function<void(PoseHandler& poseHandler)>> Cmders(const std::string& commands) const noexcept;

private:
    const std::unordered_map<char, std::function<void(PoseHandler& poseHandler)>> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},
    };
};

}  // namespace adas