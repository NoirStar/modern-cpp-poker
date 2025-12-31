#pragma once

#include "card.hpp"
#include "hand.hpp"
#include <random>
#include <algorithm>
#include <array>
#include <stdexcept>

namespace poker {

namespace detail {
    constexpr std::array<Card, 52> make_standard_deck() {
        std::array<Card, 52> deck{};
        size_t i{};
        for (int s{}; s < 4; ++s) {
            for (int r = 2; r <= 14; ++r) {
                deck[i++] = Card{
                    static_cast<Rank>(r),
                    static_cast<Suit>(s)
                };
            }
        }
        return deck;
    }
    
    inline constexpr auto STANDARD_DECK = make_standard_deck();
}

class Deck {
public:
    Deck() = default;
    ~Deck() = default;

    Deck(const Deck&) = delete;
    Deck& operator=(const Deck&) = delete;

    void shuffle() {
        std::shuffle(cards_.begin(), cards_.end(), rng_);
    }

    size_t remaining() const {
        return 52 - top_index_;
    }

    void reset() {
        cards_ = detail::STANDARD_DECK;
        top_index_ = 0;
    }

    /*
    deal<5>() 호출
        ↓
    make_index_sequence<5>{}  →  index_sequence<0,1,2,3,4> 생성
        ↓
    deal_impl<5>(index_sequence<0,1,2,3,4>) 호출
        ↓
    Hand<5>(cards_[0], cards_[1], cards_[2], cards_[3], cards_[4]) 반환
    */
    template<size_t N>
    Hand<N> deal() {
        if (top_index_ + N > 52) {
            throw std::out_of_range("Not enough cards in deck");
        }
        // 번호표 만들어서 전달
        auto hand = deal_impl<N>(std::make_index_sequence<N>{});
        top_index_ += N;
        return hand;
    }

    template<size_t N, size_t... I>
    Hand<N> deal_impl(std::index_sequence<I...>) {
        // 번호표(I...) 로 카드 꺼내서 Hand 생성
        return Hand<N>(cards_[top_index_ + I]...);
    }

private:
    std::array<Card, 52> cards_{detail::STANDARD_DECK};
    size_t top_index_{0};
    std::mt19937 rng_{std::random_device{}()};
};

} // namespace poker

