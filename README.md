# 🃏 Modern C++ Poker

**5-Card Draw Poker AI Battle - C++20 Template Metaprogramming Mastery**

C++20 템플릿 기법을 마스터하기 위해 만든 **AI vs AI 포커 게임**입니다.  
Variadic Templates, Fold Expressions, Concepts, CRTP 등 모던 C++ 핵심 기법이 적용되어 있습니다.

---

## 🎯 프로젝트 목표

**실용적인 게임**을 만들면서 **C++ 템플릿 고급 기법**을 익히는 것이 목표입니다.

---

## 🔥 사용된 템플릿 기법들

| 기법 | 적용 위치 | 설명 |
|-----|----------|------|
| **Variadic Templates** | `Hand<N>` 생성자 | 가변 개수 인자 처리 |
| **Perfect Forwarding** | `Hand(Args&&... args)` | 불필요한 복사 제거 |
| **Fold Expressions** | `evaluate()` | `(check(cards) && ...)` 패턴 |
| **if constexpr** | 핸드 평가 | 컴파일 타임 분기 |
| **Concepts** | `CardLike` | 타입 제약 명시 |
| **std::index_sequence** | `deal<N>()` | 배열 → 가변 인자 변환 |
| **CRTP** | `Strategy<Derived, N>` | 정적 다형성 |
| **operator<=>** | `Hand`, `HandValue` | Three-way comparison |
| **constexpr** | `make_standard_deck()` | 컴파일 타임 덱 생성 |

---

## 📂 프로젝트 구조

```
modern-cpp-poker/
├── include/poker/
│   ├── card.hpp          # Card, Rank, Suit (operator<=>)
│   ├── concepts.hpp      # CardLike concept
│   ├── hand.hpp          # Hand<N> - 평가, 비교
│   ├── deck.hpp          # Deck - constexpr 덱, deal<N>()
│   ├── player.hpp        # Player<N> - 베팅, 폴드
│   ├── action.hpp        # Action enum, Decision struct
│   ├── strategy.hpp      # CRTP Strategy 베이스
│   ├── game.hpp          # Game 클래스 - 게임 진행
│   └── ai/
│       ├── conservative.hpp  # 보수적 AI
│       ├── aggressive.hpp    # 공격적 AI
│       └── smart.hpp         # EV 기반 스마트 AI
├── src/
│   └── main.cpp          # AI vs AI 게임 실행
├── CMakeLists.txt
└── README.md
```

---

## 🎮 게임 실행 예시

```cpp
#include "poker/game.hpp"
#include "poker/ai/conservative.hpp"
#include "poker/ai/aggressive.hpp"
#include "poker/ai/smart.hpp"

int main() {
    poker::Game game(10, 20);  // Small blind 10, Big blind 20

    game.add_player<poker::ConservativeAI>("Alice", 1000);
    game.add_player<poker::AggressiveAI>("Bob", 1000);
    game.add_player<poker::SmartAI>("Charlie", 1000);

    for (int round = 1; round <= 3; ++round) {
        game.start_round();
    }
}
```

**출력:**
```
=== POKER GAME: AI vs AI vs AI ===
--- Round 1 ---
[Blinds] Alice posts small blind 10
[Blinds] Bob posts big blind 20
[Deal] Cards dealt to 3 players
[Action] Charlie calls 20
[Action] Alice calls 10
...
[Showdown] Winner: Bob with HandRank 2
```

---

## 🧠 AI 전략

| 전략 | 특징 |
|-----|------|
| **ConservativeAI** | 좋은 패(Pair 이상)만 베팅, 블러핑 없음 |
| **AggressiveAI** | 적극적 레이즈, 50% 확률 블러핑 |
| **SmartAI** | 핸드 강도 계산, EV 기반 판단, 15% 블러핑 |

---

## 🚀 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
cmake --build .

# Windows
.\Debug\poker_game.exe

# Linux/macOS
./poker_game
```

**요구사항:** C++20 지원 컴파일러 (GCC 10+, Clang 13+, MSVC 2019+)

---

## 📖 학습 포인트

### 1. Variadic Templates + Perfect Forwarding
```cpp
template<typename... Args>
    requires (sizeof...(Args) == N) && (CardLike<std::decay_t<Args>> && ...)
explicit Hand(Args&&... args)
    : cards_{Card{std::forward<Args>(args)}...}
```

### 2. Fold Expressions
```cpp
bool is_flush() const {
    Suit first = cards_[0].suit;
    return ((cards_[1].suit == first) && (cards_[2].suit == first) && ...);
}
```

### 3. std::index_sequence 패턴
```cpp
template<size_t N>
Hand<N> deal() {
    return deal_impl<N>(std::make_index_sequence<N>{});
}

template<size_t N, size_t... Is>
Hand<N> deal_impl(std::index_sequence<Is...>) {
    return Hand<N>{buffer_[top_ - N + Is]...};
}
```

### 4. CRTP (Curiously Recurring Template Pattern)
```cpp
template<typename Derived, size_t N = 5>
class Strategy {
public:
    Decision decide(const Hand<N>& hand, size_t call_amount) {
        return static_cast<Derived*>(this)->decide_impl(hand, call_amount);
    }
};

class SmartAI : public Strategy<SmartAI> {
    Decision decide_impl(const Hand<5>& hand, size_t call_amount) { ... }
};
```

---

## 📜 License

MIT License

---

**Made with 🔥 by NoirStar - Template Metaprogramming Enthusiast**
