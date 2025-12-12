#pragma once
#include "../include/VehicleType.hpp"
#include "Executor.hpp"
namespace adas
{
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose, VehicleType type = VehicleType::Racer) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    // High level actions that encapsulate vehicle-specific behavior
    void MoveAction(void) noexcept;       // corresponds to 'M'
    void TurnLeftAction(void) noexcept;   // corresponds to 'L'
    void TurnRightAction(void) noexcept;  // corresponds to 'R'
    void UTurnAction(void) noexcept;      // corresponds to 'U'
    void UTurn(void) noexcept;
    // low-level primitives used internally
    void Forward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Backward(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;
    Pose Query(void) const noexcept;

private:
    Pose pose;
    VehicleType type{VehicleType::Racer};
    bool reverse{false};
    bool fast{false};
};
}  // namespace adas
