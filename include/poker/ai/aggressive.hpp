#pragma once
#include "../strategy.hpp"
#include <random>

namespace poker {

class AggressiveAI : public Strategy<AggressiveAI> {
public:
    Decision decide_impl(const Hand<5>& hand, size_t pot, size_t to_call) {
        auto rank = hand.evaluate();
        
        // 원페어 이상이면 레이즈
        if (rank >= HandRank::OnePair) {
            size_t raise_amount = pot / 2;  // 하프
            if (raise_amount < to_call) raise_amount = to_call * 2;  // 최소 따당
            return Decision{Action::Raise, raise_amount};
        }
        
        // 탑카드여도 50% 확률로 블러핑
        if (bluff()) {
            return Decision{Action::Bet, pot / 4};
        }
        
        // 콜할 금액 있으면 폴드, 없으면 체크
        if (to_call > 0) return Decision{Action::Fold, 0};
        return Decision{Action::Check, 0};
    }

private:
    bool bluff() {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_int_distribution<int> dist(0, 1);
        return dist(rng) == 1;
    }
};

} // namespace poker
