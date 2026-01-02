#pragma once
#include "../strategy.hpp"
#include <random>

namespace poker {

class SmartAI : public Strategy<SmartAI> {
public:
    Decision decide_impl(const Hand<5>& hand, size_t pot, size_t to_call) {
        double hand_strength = calculate_strength(hand);
        
        // 기대값 계산
        // EV = (이길 확률 × 이길 때 이득) - (질 확률 × 잃을 금액)
        double ev = hand_strength * pot - (1.0 - hand_strength) * to_call;
        
        // 랜덤 요소 추가 (예측 불가능하게)
        double randomness = random_factor();
        
        if (ev > pot * 0.3 + randomness) {
            // 강한 핸드 + 긍정적 EV → 레이즈
            size_t raise = static_cast<size_t>(pot * (0.5 + hand_strength * 0.5));
            return Decision{Action::Raise, raise};
        } else if (ev > randomness * 10) {
            // 약간 긍정적 → 콜
            if (to_call == 0) return Decision{Action::Check, 0};
            return Decision{Action::Call, to_call};
        } else if (to_call == 0) {
            // 콜할 필요 없으면 체크
            return Decision{Action::Check, 0};
        } else if (hand_strength > 0.5 && should_bluff()) {
            // 가끔 블러핑
            return Decision{Action::Raise, to_call * 2};
        }
        
        return Decision{Action::Fold, 0};
    }

private:
    // 족보별 대략적인 승률
    double calculate_strength(const Hand<5>& hand) const {
        switch (hand.evaluate()) {
            case HandRank::RoyalFlush:    return 1.00;
            case HandRank::StraightFlush: return 0.99;
            case HandRank::FourOfKind:    return 0.98;
            case HandRank::FullHouse:     return 0.95;
            case HandRank::Flush:         return 0.90;
            case HandRank::Straight:      return 0.85;
            case HandRank::ThreeOfKind:   return 0.75;
            case HandRank::TwoPair:       return 0.60;
            case HandRank::OnePair:       return 0.40;
            default:                      return 0.20;
        }
    }
    
    double calculate_pot_odds(size_t pot, size_t to_call) const {
        if (to_call == 0) return 1.0;
        return static_cast<double>(pot) / (pot + to_call);
    }
    
    // -0.1 ~ 0.1 랜덤 값
    double random_factor() {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_real_distribution<double> dist(-0.1, 0.1);
        return dist(rng);
    }
    
    // 15% 확률로 블러핑
    bool should_bluff() {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_int_distribution<int> dist(1, 100);
        return dist(rng) <= 15;
    }
};

} // namespace poker
