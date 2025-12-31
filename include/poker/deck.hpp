#pragma once

#include "card.hpp"
#include <random>
#include <algorithm>
#include <array>

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

private:
    std::array<Card, 52> cards_{detail::STANDARD_DECK};
    size_t top_index_{0};
    std::mt19937 rng_{std::random_device{}()};
};

} // namespace poker

