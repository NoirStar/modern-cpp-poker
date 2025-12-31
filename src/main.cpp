#include <poker/card.hpp>
#include <poker/concepts.hpp>
#include <poker/hand.hpp>
#include <poker/deck.hpp>
#include <iostream>

const char* to_string(poker::HandRank rank) {
    switch (rank) {
        case poker::HandRank::RoyalFlush:    return "Royal Flush";
        case poker::HandRank::StraightFlush: return "Straight Flush";
        case poker::HandRank::FourOfKind:    return "Four of a Kind";
        case poker::HandRank::FullHouse:     return "Full House";
        case poker::HandRank::Flush:         return "Flush";
        case poker::HandRank::Straight:      return "Straight";
        case poker::HandRank::ThreeOfKind:   return "Three of a Kind";
        case poker::HandRank::TwoPair:       return "Two Pair";
        case poker::HandRank::OnePair:       return "One Pair";
        case poker::HandRank::TopCard:       return "Top Card";
        default:                             return "Unknown";
    }
}

const char* to_string(poker::Rank rank) {
    switch (rank) {
        case poker::Rank::Two:   return "2";
        case poker::Rank::Three: return "3";
        case poker::Rank::Four:  return "4";
        case poker::Rank::Five:  return "5";
        case poker::Rank::Six:   return "6";
        case poker::Rank::Seven: return "7";
        case poker::Rank::Eight: return "8";
        case poker::Rank::Nine:  return "9";
        case poker::Rank::Ten:   return "10";
        case poker::Rank::Jack:  return "J";
        case poker::Rank::Queen: return "Q";
        case poker::Rank::King:  return "K";
        case poker::Rank::Ace:   return "A";
        default:                 return "?";
    }
}

const char* to_string(poker::Suit suit) {
    switch (suit) {
        case poker::Suit::Clubs:    return "C";
        case poker::Suit::Diamonds: return "D";
        case poker::Suit::Hearts:   return "H";
        case poker::Suit::Spades:   return "S";
        default:                    return "?";
    }
}

void print_hand(const poker::Hand<5>& hand) {
    std::cout << "[ ";
    for (size_t i = 0; i < 5; ++i) {
        std::cout << to_string(hand[i].rank) << to_string(hand[i].suit) << " ";
    }
    std::cout << "] -> " << to_string(hand.evaluate()) << "\n";
}

int main() {
    using namespace poker;
    
    // Royal Flush
    Hand<5> royal_flush{
        Card{Rank::Ace, Suit::Spades},
        Card{Rank::King, Suit::Spades},
        Card{Rank::Queen, Suit::Spades},
        Card{Rank::Jack, Suit::Spades},
        Card{Rank::Ten, Suit::Spades}
    };
    
    // Flush
    Hand<5> flush{
        Card{Rank::Ace, Suit::Spades},
        Card{Rank::King, Suit::Spades},
        Card{Rank::Nine, Suit::Spades},
        Card{Rank::Five, Suit::Spades},
        Card{Rank::Two, Suit::Spades}
    };
    
    // Two Pair
    Hand<5> two_pair{
        Card{Rank::Ace, Suit::Spades},
        Card{Rank::Ace, Suit::Hearts},
        Card{Rank::King, Suit::Spades},
        Card{Rank::King, Suit::Hearts},
        Card{Rank::Two, Suit::Clubs}
    };
    
    // Top Card
    Hand<5> top_card{
        Card{Rank::Ace, Suit::Spades},
        Card{Rank::King, Suit::Hearts},
        Card{Rank::Nine, Suit::Diamonds},
        Card{Rank::Five, Suit::Clubs},
        Card{Rank::Two, Suit::Spades}
    };
    
    std::cout << "Royal Flush: " << to_string(royal_flush.evaluate()) << "\n";
    std::cout << "Flush:       " << to_string(flush.evaluate()) << "\n";
    std::cout << "Two Pair:    " << to_string(two_pair.evaluate()) << "\n";
    std::cout << "Top Card:    " << to_string(top_card.evaluate()) << "\n";
    
    // Deck Test
    std::cout << "\n=== Deck Test ===\n";
    Deck deck;
    deck.shuffle();
    
    std::cout << "Remaining: " << deck.remaining() << "\n";
    
    auto hand1 = deck.deal<5>();
    std::cout << "Hand 1: ";
    print_hand(hand1);
    std::cout << "Remaining: " << deck.remaining() << "\n";
    
    auto hand2 = deck.deal<5>();
    std::cout << "Hand 2: ";
    print_hand(hand2);
    std::cout << "Remaining: " << deck.remaining() << "\n";
    
    return 0;
}
