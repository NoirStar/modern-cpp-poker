#pragma once
#include "../strategy.hpp"

namespace poker {

class ConservativeAI : public Strategy<ConservativeAI> {
public:
    Decision decide_impl(const Hand<5>& hand, [[maybe_unused]] size_t pot, size_t to_call) {
        auto rank = hand.evaluate();
        
        // 투페어 이상만 베팅
        if (rank >= HandRank::TwoPair) {
            return Decision{Action::Call, to_call};
        }
        
        // 원페어면 체크/콜만
        if (rank >= HandRank::OnePair) {
            if (to_call == 0) return Decision{Action::Check, 0};
            return Decision{Action::Call, to_call};
        }
        
        // 그 외는 폴드
        if (to_call > 0) return Decision{Action::Fold, 0};
        return Decision{Action::Check, 0};
    }
};

} // namespace poker
