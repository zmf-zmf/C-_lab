#include "PoseHandler.hpp"
namespace adas
{
PoseHandler::PoseHandler(const Pose& pose, VehicleType type) noexcept : pose(pose), type(type)
{
}

// low-level primitives
void PoseHandler::Forward() noexcept
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
void PoseHandler::Backward() noexcept
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
void PoseHandler::TurnLeft() noexcept
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
void PoseHandler::TurnRight() noexcept
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
void PoseHandler::UTurn() noexcept
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

// High-level actions implementing vehicle-specific rules from the diagram
void PoseHandler::MoveAction() noexcept
{
    // 'M' behavior differs between Racer and Bus
    if (type == VehicleType::Racer) {
        // Normal: move 2; Fast doubles movement; Reverse flips to backward
        int step = 2;
        if (fast)
            step *= 2;  // fast doubles steps (2 -> 4)
        for (int i = 0; i < step; ++i) {
            if (reverse)
                Backward();
            else
                Forward();
        }
    } else {  // Bus
        // Bus length 2: head coordinate moves; normal M = 1 step; fast doubles to 2; reverse moves backward
        int step = 1;
        if (fast)
            step = 2;
        for (int i = 0; i < step; ++i) {
            if (reverse)
                Backward();
            else
                Forward();
        }
    }
}

void PoseHandler::TurnLeftAction() noexcept
{
    if (type == VehicleType::Racer) {
        if (fast) {
            // Racer Fast + L: forward1, left turn, forward1
            if (reverse) {
                // if reverse+fast: backward1, right turn, backward1
                Backward();
                TurnRight();
                Backward();
            } else {
                Forward();
                TurnLeft();
                Forward();
            }
        } else {
            // Normal: left then forward1; Reverse: right then backward1
            if (reverse) {
                TurnRight();
                Backward();
            } else {
                TurnLeft();
                Forward();
            }
        }
    } else {  // Bus
        // Bus: L normally: forward1 then left turn; if fast: forward1, forward1, then left
        if (fast) {
            if (reverse) {
                // reverse+fast: backward1, backward1, then right turn
                Backward();
                Backward();
                TurnRight();
            } else {
                Forward();
                Forward();
                TurnLeft();
            }
        } else {
            if (reverse) {
                Backward();
                TurnRight();
            } else {
                Forward();
                TurnLeft();
            }
        }
    }
}

void PoseHandler::TurnRightAction() noexcept
{
    if (type == VehicleType::Racer) {
        if (fast) {
            if (reverse) {
                // reverse+fast: backward1, left turn, backward1
                Backward();
                TurnLeft();
                Backward();
            } else {
                Forward();
                TurnRight();
                Forward();
            }
        } else {
            if (reverse) {
                TurnLeft();
                Backward();
            } else {
                TurnRight();
                Forward();
            }
        }
    } else {  // Bus
        if (fast) {
            if (reverse) {
                Backward();
                Backward();
                TurnLeft();
            } else {
                Forward();
                Forward();
                TurnRight();
            }
        } else {
            if (reverse) {
                Backward();
                TurnLeft();
            } else {
                Forward();
                TurnRight();
            }
        }
    }
}

void PoseHandler::UTurnAction() noexcept
{
    // Keep a simple behavior: optionally move one step when fast, then u-turn.
    if (fast) {
        if (reverse)
            Backward();
        else
            Forward();
    }
    UTurn();
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}
bool PoseHandler::IsFast() const noexcept
{
    return fast;
}
void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}
bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}
}  // namespace adas
