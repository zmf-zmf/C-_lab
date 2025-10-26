#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"
namespace adas
{
TEST(ExecutorTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when - 执行FM指令（快速移动）
    executor->Execute("FM");

    // then
    const Pose target({2, 0, 'E'});  // 朝东快速移动，X+2
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when - 执行FL指令（快速左转）
    executor->Execute("FL");

    // then
    const Pose target({1, 0, 'N'});  // 朝东快速左转：X+1，方向变为北
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_S_and_x_plus_1_given_status_is_fast_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when - 执行FR指令（快速右转）
    executor->Execute("FR");

    // then
    const Pose target({1, 0, 'S'});  // 朝东快速右转：X+1，方向变为南
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when - 执行FFM指令（双倍快速移动）
    executor->Execute("FFM");

    // then
    const Pose target({0, 1, 'N'});  // 朝北双倍快速移动：Y+1
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
