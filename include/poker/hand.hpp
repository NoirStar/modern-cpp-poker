#pragma once

#include "card.hpp"
#include "concepts.hpp"
#include <array>
#include <algorithm>

namespace poker {

enum class HandRank : std::uint8_t {
    TopCard,
    OnePair,
    TwoPair,
    ThreeOfKind,
    Straight,
    Flush,
    FullHouse,
    FourOfKind,
    StraightFlush,
    RoyalFlush
};

template<size_t N>
class Hand {
public:
    template<CardLike... Cards>
        requires (sizeof...(Cards) == N)
    Hand(Cards&&... cards)
        : cards_{std::forward<Cards>(cards)...} 
    {
        sort_descending();
    }
    ~Hand() = default;

    Hand(const Hand&) = delete;
    Hand& operator=(const Hand&) = delete;
    
    Hand(Hand&&) = default;
    Hand& operator=(Hand&&) = default;

    const Card& operator[](size_t i) const {
        return cards_[i];
    }

    const std::array<Card, N>& cards() const {
        return cards_;
    }

    HandRank evaluate() const {
        return evaluate_impl<
            HandRank::RoyalFlush,
            HandRank::StraightFlush,
            HandRank::FourOfKind,
            HandRank::FullHouse,
            HandRank::Flush,
            HandRank::Straight,
            HandRank::ThreeOfKind,
            HandRank::TwoPair,
            HandRank::OnePair
        >();
    }

    // (A, B) 콤마연산자. A를 실행하고, B를 전체 표현식의 값으로 설정한다.
    template<HandRank... Ranks>
    HandRank evaluate_impl() const {
        HandRank result = HandRank::TopCard;
        
        // 높은 순서대로 하나씩 실행하보며 덱을 파악.
        // ( (check<Rank1>() && (result = Rank1, true)) ) || 
        // ( (check<Rank2>() && (result = Rank2, true)) ) || ...생략
        // 위의 코드를 아래와 같이 fold expression을 써서 축약

        ((check<Ranks>() && (result = Ranks, true)) || ...);
        return result;
    }

private:
    std::array<Card, N> cards_;

    void sort_descending() {
        std::sort(cards_.begin(), cards_.end(),
            [](const Card& a, const Card& b) {
                return a > b;
            }
        );
    }

    template<HandRank R>
    bool check() const {
        if constexpr (R == HandRank::RoyalFlush) return is_royal_flush();
        else if constexpr (R == HandRank::StraightFlush) return is_straight_flush();
        else if constexpr (R == HandRank::FourOfKind) return is_four_of_kind();
        else if constexpr (R == HandRank::FullHouse) return is_full_house();
        else if constexpr (R == HandRank::Flush) return is_flush();
        else if constexpr (R == HandRank::Straight) return is_straight();
        else if constexpr (R == HandRank::ThreeOfKind) return is_three_of_kind();
        else if constexpr (R == HandRank::TwoPair) return is_two_pair();
        else if constexpr (R == HandRank::OnePair) return is_pair();
        else return false;  // TopCard
    }

     // 카드 족보
    std::array<int, 13> count_ranks() const {
        std::array<int, 13> counts{};
        for (auto& card : cards_) {
            counts[static_cast<int>(card.rank) - 2]++;
        }
        return counts;
    }

    bool is_pair() const {
        auto counts = count_ranks();
        return std::any_of(counts.begin(), counts.end(), 
            [](int c) { return c >= 2; }
        );
    }
    
    bool is_three_of_kind() const {
        auto counts = count_ranks();
        return std::any_of(counts.begin(), counts.end(), 
            [](int c) { return c >= 3; }
        );
    }

    bool is_four_of_kind() const {
        auto counts = count_ranks();
        return std::any_of(counts.begin(), counts.end(), 
            [](int c) { return c >= 4; }
        );
    }

    bool is_two_pair() const {
        auto counts = count_ranks();
        return std::count(counts.begin(), counts.end(), 2) >= 2;
    }

    bool is_full_house() const {
        auto counts = count_ranks();
        return std::count(counts.begin(), counts.end(), 2) &&
               std::count(counts.begin(), counts.end(), 3);
    }

    bool is_flush() const {
        Suit first_suit = cards_[0].suit;
        return std::all_of(cards_.begin(), cards_.end(),
            [first_suit](const Card& card) {
                return first_suit == card.suit;
            } 
        );
    }

    bool is_straight() const {
        bool normal = true;
        for (size_t i=1; i<N; ++i) {
            if (static_cast<int>(cards_[i-1].rank) -
                static_cast<int>(cards_[i].rank) != 1)
            {
                normal = false;
                break;
            }
        }
        if (normal) return true;

        if (cards_[0].rank == Rank::Ace &&
            cards_[1].rank == Rank::Five &&
            cards_[2].rank == Rank::Four &&
            cards_[3].rank == Rank::Three &&
            cards_[4].rank == Rank::Two)
        {
            return true;
        }
        return false;
    }

    bool is_straight_flush() const {
        return is_flush() && is_straight();
    }
    
    bool is_royal_flush() const {
        if (!is_straight_flush()) return false;
        return cards_[0].rank == Rank::Ace;
    }
};


} // namespace poker