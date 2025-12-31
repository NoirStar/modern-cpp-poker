#include <poker/card.hpp>
#include <poker/concepts.hpp>
#include <poker/hand.hpp>
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
    
    return 0;
}
