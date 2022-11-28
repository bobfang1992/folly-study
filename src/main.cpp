#include <folly/experimental/coro/Task.h>
#include <folly/experimental/coro/BlockingWait.h>
#include <folly/futures/Future.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/init/Init.h>
#include <iostream>

#include "demolib.h"

folly::coro::Task<int> slow()
{
    std::cout << "before sleep" << std::endl;
    co_await folly::futures::sleep(std::chrono::seconds{1});
    std::cout << "after sleep" << std::endl;
    co_return 1;
}

int main(int argc, char **argv)
{
    folly::init(&argc, &argv);
    auto result = folly::coro::blockingWait(
        slow().scheduleOn(folly::getGlobalCPUExecutor().get()));
    std::cout << result << std::endl;
    std::cout << Demolib::add(1, 2) << std::endl;
    return 0;
}
