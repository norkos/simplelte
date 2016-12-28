//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/sml.hpp>
#include <queue>
#include <vector>

namespace sml = boost::sml;

struct event1 {};
struct event2 {};

const auto state1 = sml::state<class state1>;
const auto state2 = sml::state<class state2>;
const auto state3 = sml::state<class state3>;
const auto state4 = sml::state<class state4>;
const auto state5 = sml::state<class state5>;
const auto state6 = sml::state<class state6>;

test defer_minimal = [] {
  const auto c = [] {
    using namespace sml;
    // clang-format off
      return make_transition_table(
       *state1 + event<event1> / defer,
        state1 + event<event2> = state2,
        state2 + event<event1> = X
      );
      // clang-format off
  };

  sml::sm<decltype(c), sml::defer_queue<std::queue>> sm{c};
  sm.process_event(event1());
  sm.process_event(event2());
  expect(sm.is(sml::X));
};

test defer_queue_check = [] {
  class A;
  class B;

  const auto c = [] {
      using namespace sml;
      // clang-format off
      return make_transition_table(
       *state1 + event<event1> / defer,
        state1 + event<event2> = state2,
        state2 + event<event1> = state<A>,
        state<A>   + event<event1> = state<B>
      );
      // clang-format off
  };

  sml::sm<decltype(c), sml::defer_queue<std::queue>> sm{c};
  sm.process_event(event1());
  sm.process_event(event2());
  expect(sm.is(sml::state<A>));
};

test defer_transition = [] {
  const auto c = [] {
      using namespace sml;
      // clang-format off
      return make_transition_table(
       *state1 + event<event1> / defer = state2,
        state2 + event<event1> = X
      );
      // clang-format off
  };

  sml::sm<decltype(c), sml::defer_queue<std::queue>> sm{c};
  sm.process_event(event1());
  expect(sm.is(sml::X));
};

test defer_and_transitions = [] {
  struct c {
    auto operator()() {
      using namespace sml;
      // clang-format off
      return make_transition_table(
       *state1 + event<event1> / defer,
        state1 + on_entry<_> / [this] { entries.emplace_back(1); },
        state2 + event<event1> / defer,
        state2 + on_entry<_> / [this] { entries.emplace_back(2); },
        state1 + event<event2> = state2,
        state2 + event<event2> = state3,
        state3 + event<event1> = state4,
        state3 + on_entry<_> / [this] { entries.emplace_back(3); },
        state4 + event<event1> = state5,
        state4 + on_entry<_> / [this] { entries.emplace_back(4); },
        state5 + event<event1> = state6,
        state5 + on_entry<_> / [this] { entries.emplace_back(5); },
        state6 + on_entry<_> / [this] { entries.emplace_back(6); }
      );
      // clang-format on
    }

    std::vector<int> entries;
  };

  c c_;
  sml::sm<c, sml::defer_queue<std::queue>> sm{c_};
  sm.process_event(event1());
  sm.process_event(event1());
  sm.process_event(event2());
  sm.process_event(event2());

  expect(5 == c_.entries.size());
  expect(1 == c_.entries[0]);
  expect(2 == c_.entries[1]);
  expect(3 == c_.entries[2]);
  expect(4 == c_.entries[3]);
  expect(5 == c_.entries[4]);
};

test defer_and_anonymous = [] {
  struct c {
    auto operator()() {
      using namespace sml;
      // clang-format off
      return make_transition_table(
       *state1 + event<event1> / defer,
        state1 + on_entry<_> / [this] { entries.emplace_back(1); },
        state1 + event<event2> = state2,
        state2 = state3,
        state2 + on_entry<_> / [this] { entries.emplace_back(2); },
        state3 + event<event1> = state4,
        state4 + on_entry<_> / [this] { entries.emplace_back(4); },
        state3 + on_entry<_> / [this] { entries.emplace_back(3); },
        state2 + event<event1> = state5,
        state5 + on_entry<_> / [this] { entries.emplace_back(5); }
      );
      // clang-format on
    }

    std::vector<int> entries;
  };

  c c_;
  sml::sm<c, sml::defer_queue<std::queue>> sm{c_};
  sm.process_event(event1());
  sm.process_event(event2());

  expect(4 == c_.entries.size());
  expect(1 == c_.entries[0]);
  expect(2 == c_.entries[1]);
  expect(3 == c_.entries[2]);
  expect(4 == c_.entries[3]);
};
