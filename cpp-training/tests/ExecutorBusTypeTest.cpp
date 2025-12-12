#include <gtest/gtest.h>

#include <memory>

#include "../src/ExecutorImpl.hpp"
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// Tests for Bus behavior as described in the image
TEST(ExecutorBusTypeTest, Bus_Moves_1_on_M)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'N'}, VehicleType::Bus));
    executor->Execute("M");
    const Pose target{0, 1, 'N'};  // Bus normal M: move forward 1
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTypeTest, Bus_Fast_Moves_2_on_FM)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'N'}, VehicleType::Bus));
    executor->Execute("FM");
    const Pose target{0, 2, 'N'};  // Bus fast M: move forward 2
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTypeTest, Bus_L_normal_behavior)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'E'}, VehicleType::Bus));
    executor->Execute("L");
    const Pose target{1, 0, 'N'};  // Bus L normal: forward1 then left turn
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTypeTest, Bus_BM_backward_1)
{
    std::unique_ptr<Executor> executor(new ExecutorImpl({0, 0, 'E'}, VehicleType::Bus));
    executor->Execute("BM");
    const Pose target{-1, 0, 'E'};  // Bus B + M -> backward 1
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
