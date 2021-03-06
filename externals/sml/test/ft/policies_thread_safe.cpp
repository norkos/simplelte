//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/sml.hpp>
#include <mutex>
#include <thread>

namespace sml = boost::sml;

struct e1 {};
struct e2 {};

const auto idle = sml::state<class idle>;
const auto s1 = sml::state<class s1>;
const auto s2 = sml::state<class s2>;

test process_the_same_event = [] {
  struct actions_guards {
    auto operator()() {
      using namespace sml;
      // clang-format off
      return make_transition_table(
         *idle + event<e1> [([this]{ guard1_calls++; return true; })] / [this] { action1_calls++; } = s1
        , idle + event<e2> [([this]{ guard2_calls++; return true; })] / [this] { action2_calls++; } = s2
      );
      // clang-format on
    }

    int guard1_calls = 0;
    int guard2_calls = 0;
    int action1_calls = 0;
    int action2_calls = 0;
  };

  actions_guards ag;
  sml::sm<actions_guards, sml::thread_safe<std::mutex>> sm{ag};
  std::thread t1{[&] { sm.process_event(e1{}); }};
  std::thread t2{[&] { sm.process_event(e2{}); }};
  t1.join();
  t2.join();
  using namespace sml;
  expect(1 == ag.guard1_calls + ag.guard2_calls);
  expect(1 == ag.action1_calls + ag.action2_calls);
  expect(sm.is(s1) || sm.is(s2));
};

test process_event_reentrant = [] {
  struct c {
    auto operator()() const {
      using namespace sml;
      // clang-format off
      return make_transition_table(
         *idle + event<e1> / process(e2{})
        , idle + event<e2> = s2
      );
      // clang-format on
    }
  };

  sml::sm<c, sml::thread_safe<std::recursive_mutex>> sm;
  // Hangs forever awaiting lock if mutex is not reentrant.
  sm.process_event(e1{});
};
