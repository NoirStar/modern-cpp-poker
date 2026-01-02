#pragma once

#include "hand.hpp"
#include <optional>

namespace poker {

template<size_t N>
class Player {
public:
    explicit Player(std::string&& name, size_t chips) 
        : name_(std::move(name)), chips_(chips)
    {}

    void receive_hand(Hand<N>&& hand) {
        hand_ = std::move(hand);
    }

    void fold() {
        hand_.reset();
    }
    void bet(size_t amount) {
        if (amount > chips_) {
            throw std::out_of_range("Not enough chips");
        }
        chips_ -= amount;
        current_bet_ += amount;
    }
    
    bool has_hand() const {
        return hand_.has_value();
    }

    const Hand<N>& hand() const {
        return hand_.value();  // 없으면 예외
    }

    size_t chips() const {
        return chips_;
    }
    
    void add_chips(size_t amount) {
        chips_ += amount;
    }
    
    const std::string& name() const {
        return name_;
    }
    
private:
    std::string name_;
    size_t chips_{};
    std::optional<Hand<N>> hand_;
    size_t current_bet_{};
};

} // namespace poker