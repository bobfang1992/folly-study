#include <folly/dynamic.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/experimental/coro/BlockingWait.h>
#include <folly/experimental/coro/Task.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <iostream>

#include <fmt/format.h>

#include "demolib.h"

folly::coro::Task<int> slow() {
  std::cout << "before sleep" << std::endl;
  co_await folly::futures::sleep(std::chrono::seconds{1});
  std::cout << "after sleep" << std::endl;
  co_return 1;
}

double folly_to_test(std::string_view str) { return folly::to<double>(str); }

int main(int argc, char **argv) {
  folly::Init init(&argc, &argv, {});
  auto result = folly::coro::blockingWait(
      slow().scheduleOn(folly::getGlobalCPUExecutor().get()));
  std::cout << result << std::endl;
  std::cout << Demolib::add(1, 2) << std::endl;
  fmt::print("hello world from fmt\n");

  fmt::print("{}\n", folly_to_test("123.456"));
  fmt::print("{}\n", folly_to_test("0.0000000001"));
  return 0;
}
