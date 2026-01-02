#include <poker/card.hpp>
#include <poker/concepts.hpp>
#include <poker/hand.hpp>
#include <poker/deck.hpp>
#include <poker/player.hpp>
#include <poker/game.hpp>
#include <poker/ai/conservative.hpp>
#include <poker/ai/aggressive.hpp>
#include <poker/ai/smart.hpp>
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
    
    // Hand Comparison Test
    std::cout << "\n=== Comparison Test ===\n";
    
    Hand<5> pair_kings{
        Card{Rank::King, Suit::Spades},
        Card{Rank::King, Suit::Hearts},
        Card{Rank::Ace, Suit::Diamonds},
        Card{Rank::Seven, Suit::Clubs},
        Card{Rank::Two, Suit::Spades}
    };
    
    Hand<5> pair_queens{
        Card{Rank::Queen, Suit::Spades},
        Card{Rank::Queen, Suit::Hearts},
        Card{Rank::Ace, Suit::Clubs},
        Card{Rank::King, Suit::Diamonds},
        Card{Rank::Jack, Suit::Spades}
    };
    
    std::cout << "Pair Kings: ";
    print_hand(pair_kings);
    std::cout << "Pair Queens: ";
    print_hand(pair_queens);
    
    if (pair_kings > pair_queens) {
        std::cout << "Result: Pair Kings wins!\n";
    } else if (pair_kings < pair_queens) {
        std::cout << "Result: Pair Queens wins!\n";
    } else {
        std::cout << "Result: Tie!\n";
    }
    
    // Player Test
    std::cout << "\n=== Player Test ===\n";
    
    Player<5> player1("Alice", 1000);
    Player<5> player2("Bob", 1000);
    
    Deck deck2;
    deck2.shuffle();
    
    player1.receive_hand(deck2.deal<5>());
    player2.receive_hand(deck2.deal<5>());
    
    std::cout << "Alice chips: " << player1.chips() << "\n";
    std::cout << "Alice has hand: " << (player1.has_hand() ? "yes" : "no") << "\n";
    
    player1.bet(100);
    std::cout << "Alice bets 100, chips now: " << player1.chips() << "\n";
    
    player2.fold();
    std::cout << "Bob folds, has hand: " << (player2.has_hand() ? "yes" : "no") << "\n";
    
    // AI Test
    std::cout << "\n=== AI Test ===\n";
    
    Deck deck3;
    deck3.shuffle();
    auto test_hand = deck3.deal<5>();
    
    std::cout << "Test hand: ";
    print_hand(test_hand);
    
    ConservativeAI conservative;
    AggressiveAI aggressive;
    SmartAI smart;
    
    auto decision1 = conservative.decide(test_hand, 100, 20);
    auto decision2 = aggressive.decide(test_hand, 100, 20);
    auto decision3 = smart.decide(test_hand, 100, 20);
    
    auto action_str = [](Action a) {
        switch (a) {
            case Action::Fold:  return "Fold";
            case Action::Check: return "Check";
            case Action::Call:  return "Call";
            case Action::Bet:   return "Bet";
            case Action::Raise: return "Raise";
            case Action::AllIn: return "AllIn";
            default:            return "Unknown";
        }
    };
    
    std::cout << "Conservative: " << action_str(decision1.action) << " (" << decision1.amount << ")\n";
    std::cout << "Aggressive:   " << action_str(decision2.action) << " (" << decision2.amount << ")\n";
    std::cout << "Smart:        " << action_str(decision3.action) << " (" << decision3.amount << ")\n";
    
    // === GAME TEST ===
    std::cout << "\n========================================\n";
    std::cout << "=== POKER GAME: AI vs AI vs AI ===\n";
    std::cout << "========================================\n\n";
    
    Player<5> alice("Alice", 1000);
    Player<5> bob("Bob", 1000);
    Player<5> charlie("Charlie", 1000);
    
    ConservativeAI conservative_ai;
    AggressiveAI aggressive_ai;
    SmartAI smart_ai;
    
    Game game(10);  // 스몰블라인드 10
    game.add_player(&alice, conservative_ai);
    game.add_player(&bob, aggressive_ai);
    game.add_player(&charlie, smart_ai);
    
    std::cout << "Players:\n";
    std::cout << "  Alice (Conservative): " << alice.chips() << " chips\n";
    std::cout << "  Bob (Aggressive):     " << bob.chips() << " chips\n";
    std::cout << "  Charlie (Smart):      " << charlie.chips() << " chips\n\n";
    
    // 3 라운드 진행
    for (int round = 1; round <= 3; ++round) {
        std::cout << "--- Round " << round << " ---\n";
        game.start_round();
        std::cout << "\nChips after round " << round << ":\n";
        std::cout << "  Alice:   " << alice.chips() << "\n";
        std::cout << "  Bob:     " << bob.chips() << "\n";
        std::cout << "  Charlie: " << charlie.chips() << "\n\n";
    }
    
    std::cout << "========================================\n";
    std::cout << "=== GAME OVER ===\n";
    std::cout << "========================================\n";
    
    return 0;
}
