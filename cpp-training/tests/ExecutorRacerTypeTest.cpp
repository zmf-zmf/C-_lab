#include <gtest/gtest.h>

#include <memory>

#include "../src/ExecutorImpl.hpp"
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// Tests for Racer behavior as described in the image
TEST(ExecutorRacerTypeTest, Racer_Moves_2_on_M)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'N'}, VehicleType::Racer));
    executor->Execute("M");
    const Pose target{0, 2, 'N'};  // Racer normal M: move forward 2
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorRacerTypeTest, Racer_Fast_Moves_4_on_FM)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'N'}, VehicleType::Racer));
    executor->Execute("FM");
    const Pose target{0, 4, 'N'};  // Racer fast M: move forward 4
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorRacerTypeTest, Racer_L_normal_behavior)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'E'}, VehicleType::Racer));
    executor->Execute("L");
    const Pose target{0, 1, 'N'};  // Racer L normal: turn left then forward 1
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorRacerTypeTest, Racer_BM_backward_2)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'E'}, VehicleType::Racer));
    executor->Execute("BM");
    const Pose target{-2, 0, 'E'};  // Racer B + M -> backward 2
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
