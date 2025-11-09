#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// B指令+移动测试 - 反向状态下移动
TEST(ExecutorReverseTest, should_return_x_minus_1_given_commands_are_BM_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BM");

    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

// B指令+左转测试 - 反向状态下左转（方向相反）
TEST(ExecutorReverseTurnTest, should_return_heading_S_given_commands_are_BL_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BL");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

// BF组合指令测试 - 先反向再快速（反向快速移动）
TEST(ExecutorReverseFastTest, should_return_x_minus_2_given_commands_are_BFM_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

// BB组合指令测试 - 连续两次反向（状态重置）
TEST(ExecutorDoubleReverseTest, should_return_normal_forward_given_commands_are_BBM_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("BBM");

    // then
    const Pose target{0, 1, 'N'};  // 正常向前移动
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas