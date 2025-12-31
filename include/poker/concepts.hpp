#pragma once

#include "card.hpp"
#include <concepts>

namespace poker {

template<typename T>
concept CardLike = requires(const T& t) {
    { t.rank } -> std::convertible_to<Rank>;
    { t.suit } -> std::convertible_to<Suit>;
};

}