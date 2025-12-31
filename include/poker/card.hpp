#pragma once

#include <cstdint>
#include <compare>

namespace poker {

enum class Rank : std::uint8_t {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

enum class Suit : std::uint8_t {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

struct Card {
    Rank rank{};
    Suit suit{};

    auto operator<=>(const Card& other) const {
        return rank <=> other.rank;
    }

    bool operator==(const Card& other) const {
        return rank == other.rank;
    }
};

} // namespace poker