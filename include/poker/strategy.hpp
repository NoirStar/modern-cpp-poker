#pragma once
#include "hand.hpp"
#include "action.hpp"

namespace poker {

template<typename Derived, size_t N = 5>
class Strategy {
public:
    Decision decide(const Hand<N>& hand, size_t pot, size_t to_call) {
        return static_cast<Derived*>(this)->decide_impl(hand, pot, to_call);
    }
};

} // namespace poker