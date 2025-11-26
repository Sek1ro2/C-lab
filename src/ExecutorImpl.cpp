#include <gtest/gtest.h>
#include "Executor.hpp"
#include "ExecutorImpl.hpp"

namespace adas
{
    TEST(ExecutorTest, FCommand_Forward5Steps_East)
    {
        Executor *executor = Executor::NewExecutor(Pose{0, 0, 'E'});
        executor->Execute("F5");
        Pose res = executor->Query();
        EXPECT_TRUE(PoseEq(res, Pose{5, 0, 'E'}));
        delete executor;
    }

    TEST(ExecutorTest, FCommand_Forward3Steps_North)
    {
        Executor *executor = Executor::NewExecutor(Pose{0, 0, 'N'});
        executor->Execute("L F3");
        Pose res = executor->Query();
        EXPECT_TRUE(PoseEq(res, Pose{0, 3, 'N'}));
        delete executor;
    }

    TEST(ExecutorTest, FCommand_NoNumber_Default1Step)
    {
        Executor *executor = Executor::NewExecutor(Pose{0, 0, 'S'});
        executor->Execute("F");
        Pose res = executor->Query();
        EXPECT_TRUE(PoseEq(res, Pose{0, -1, 'S'}));
        delete executor;
    }

    // 保留原有测试用例
    TEST(ExecutorTest, EmptyCommand)
    {
        Executor *executor = Executor::NewExecutor(Pose{0, 0, 'E'});
        executor->Execute("");
        Pose res = executor->Query();
        EXPECT_TRUE(PoseEq(res, Pose{0, 0, 'E'}));
        delete executor;
    }

    TEST(ExecutorTest, MCommand_East)
    {
        Executor *executor = Executor::NewExecutor(Pose{0, 0, 'E'});
        executor->Execute("M");
        Pose res = executor->Query();
        EXPECT_TRUE(PoseEq(res, Pose{1, 0, 'E'}));
        delete executor;
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}