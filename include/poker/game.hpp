#pragma once
#include "deck.hpp"
#include "player.hpp"
#include "action.hpp"
#include <vector>
#include <functional>
#include <iostream>

namespace poker {

class Game {
public:
    using DecisionCallback = std::function<Decision(const Hand<5>&, size_t pot, size_t to_call)>;
    
    struct Seat {
        Player<5>* player;
        DecisionCallback decide;
        bool folded{false};
        size_t round_bet{0};
    };

    explicit Game(size_t small_blind = 10) 
        : small_blind_(small_blind) 
    {}
    
    // 플레이어 추가 (AI 또는 사람)
    template<typename Strategy>
    void add_player(Player<5>* player, Strategy& strategy) {
        seats_.push_back(Seat{
            player,
            [&strategy](const Hand<5>& h, size_t p, size_t c) {
                return strategy.decide(h, p, c);
            },
            false,
            0
        });
    }
    
    // 라운드 시작
    void start_round() {
        // 리셋
        deck_.reset();
        deck_.shuffle();
        pot_ = 0;
        current_bet_ = 0;
        
        for (auto& seat : seats_) {
            seat.folded = false;
            seat.round_bet = 0;
        }
        
        // 블라인드
        post_blinds();
        
        // 카드 배분
        deal_cards();
        
        // 베팅
        betting_round();
        
        // 쇼다운
        showdown();
    }
    
    size_t pot() const { return pot_; }
    size_t player_count() const { return seats_.size(); }

private:
    std::vector<Seat> seats_;
    Deck deck_;
    size_t pot_{0};
    size_t current_bet_{0};
    size_t small_blind_;
    size_t dealer_pos_{0};
    
    void post_blinds() {
        size_t sb_pos = (dealer_pos_ + 1) % seats_.size();
        size_t bb_pos = (dealer_pos_ + 2) % seats_.size();
        
        // 스몰 블라인드
        size_t sb = small_blind_;
        seats_[sb_pos].player->bet(sb);
        seats_[sb_pos].round_bet = sb;
        pot_ += sb;
        
        // 빅 블라인드
        size_t bb = small_blind_ * 2;
        seats_[bb_pos].player->bet(bb);
        seats_[bb_pos].round_bet = bb;
        pot_ += bb;
        current_bet_ = bb;
        
        std::cout << "Blinds posted: SB=" << sb << ", BB=" << bb << "\n";
    }
    
    void deal_cards() {
        for (auto& seat : seats_) {
            seat.player->receive_hand(deck_.deal<5>());
        }
        std::cout << "Cards dealt to " << seats_.size() << " players\n";
    }
    
    void betting_round() {
        size_t start_pos = (dealer_pos_ + 3) % seats_.size();
        size_t actions_without_raise = 0;
        size_t active_players = seats_.size();
        
        size_t pos = start_pos;
        
        while (actions_without_raise < active_players) {
            auto& seat = seats_[pos];
            
            if (!seat.folded && seat.player->has_hand()) {
                size_t to_call = current_bet_ - seat.round_bet;
                
                Decision decision = seat.decide(
                    seat.player->hand(), 
                    pot_, 
                    to_call
                );
                
                process_decision(seat, decision, to_call);
                
                if (decision.action == Action::Raise || decision.action == Action::Bet) {
                    actions_without_raise = 1;
                } else {
                    actions_without_raise++;
                }
                
                if (decision.action == Action::Fold) {
                    active_players--;
                }
            }
            
            pos = (pos + 1) % seats_.size();
            
            // 한 명만 남으면 종료
            if (active_players <= 1) break;
        }
    }
    
    void process_decision(Seat& seat, const Decision& decision, size_t to_call) {
        switch (decision.action) {
            case Action::Fold:
                seat.folded = true;
                seat.player->fold();
                std::cout << "Player folds\n";
                break;
                
            case Action::Check:
                std::cout << "Player checks\n";
                break;
                
            case Action::Call:
                seat.player->bet(to_call);
                seat.round_bet += to_call;
                pot_ += to_call;
                std::cout << "Player calls " << to_call << "\n";
                break;
                
            case Action::Bet:
            case Action::Raise: {
                size_t total = to_call + decision.amount;
                seat.player->bet(total);
                seat.round_bet += total;
                pot_ += total;
                current_bet_ = seat.round_bet;
                std::cout << "Player raises to " << current_bet_ << "\n";
                break;
            }
                
            case Action::AllIn: {
                size_t all = seat.player->chips();
                seat.player->bet(all);
                seat.round_bet += all;
                pot_ += all;
                if (seat.round_bet > current_bet_) {
                    current_bet_ = seat.round_bet;
                }
                std::cout << "Player goes all-in: " << all << "\n";
                break;
            }
        }
    }
    
    void showdown() {
        std::cout << "\n=== Showdown ===\n";
        std::cout << "Pot: " << pot_ << "\n";
        
        Seat* winner = nullptr;
        
        for (auto& seat : seats_) {
            if (!seat.folded && seat.player->has_hand()) {
                std::cout << "Player hand: " << static_cast<int>(seat.player->hand().evaluate()) << "\n";
                
                if (!winner || seat.player->hand() > winner->player->hand()) {
                    winner = &seat;
                }
            }
        }
        
        if (winner) {
            std::cout << "Winner takes pot: " << pot_ << "\n";
            // 칩 지급은 Player에 add_chips 메서드 필요
        }
        
        // 딜러 버튼 이동
        dealer_pos_ = (dealer_pos_ + 1) % seats_.size();
    }
};

} // namespace poker
