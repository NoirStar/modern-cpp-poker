# 🃏 Modern C++ Poker

**5-Card Draw Poker AI Battle - C++20 Template Metaprogramming Mastery**

완전한 템플릿 메타프로그래밍 학습을 위한 포커 게임 프로젝트입니다.  
모든 핵심 기능이 최신 C++20 템플릿 기법으로 구현되어 있습니다.

---

## 🎯 프로젝트 목표

이 프로젝트는 **실용적인 게임**을 만들면서 동시에 **C++ 템플릿의 모든 고급 기법**을 마스터하기 위해 설계되었습니다.

---

## 🔥 사용된 템플릿 기법들

| 기법 | 어디에 사용 | 난이도 |
|-----|-----------|--------|
| **Variadic Templates** | `Hand<Cards...>`, AI 전략 체이닝 | ⭐⭐ |
| **Fold Expressions** | 핸드 평가, 카드 비교 | ⭐⭐⭐ |
| **Pack Expansion** | 카드 조합 생성 | ⭐⭐ |
| **Concepts** | `Card`, `HandEvaluator`, `AIStrategy` | ⭐⭐⭐ |
| **CRTP** | AI 전략 베이스 클래스 | ⭐⭐⭐ |
| **Type Traits** | 컴파일타임 핸드 검증 | ⭐⭐⭐ |
| **constexpr/consteval** | 컴파일타임 카드 로직 | ⭐⭐⭐⭐ |
| **Template Specialization** | 각 핸드 랭크별 평가 | ⭐⭐⭐ |
| **SFINAE** | 조건부 메서드 활성화 | ⭐⭐⭐⭐ |
| **if constexpr** | 타입별 분기 처리 | ⭐⭐ |
| **Deduction Guides** | 자동 타입 추론 | ⭐⭐ |
| **std::invoke** | 다양한 callable 처리 | ⭐⭐ |

---

## 📂 프로젝트 구조

```
modern-cpp-poker/
├── include/poker/
│   ├── card.hpp              # 카드 타입 (Rank, Suit)
│   ├── hand.hpp              # 핸드 표현 및 평가
│   ├── hand_evaluator.hpp    # 컴파일타임 핸드 랭킹
│   ├── deck.hpp              # 덱 관리
│   ├── player.hpp            # 플레이어 추상화
│   ├── game_state.hpp        # 게임 상태 머신
│   └── ai/
│       ├── strategy.hpp      # AI 전략 베이스
│       ├── conservative.hpp  # 보수적 전략
│       ├── aggressive.hpp    # 공격적 전략
│       └── smart.hpp         # 확률 기반 전략
├── src/
│   └── main.cpp              # 게임 실행
├── CMakeLists.txt
└── README.md
```

---

## 🎮 게임 플레이

```cpp
// AI 전략을 템플릿 파라미터로!
Game<ConservativeAI, AggressiveAI, SmartAI> game;

game.start();
game.play_rounds(100);
game.show_stats();
```

---

## 🧠 AI 전략

| 전략 | 특징 | 템플릿 기법 |
|-----|------|-----------|
| **Conservative** | 좋은 패만 베팅 | CRTP, 조건부 컴파일 |
| **Aggressive** | 블러핑 많이 | 확률 계산, fold expression |
| **Smart** | 상황 판단 | 컴파일타임 의사결정 트리 |

---

## 🚀 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
cmake --build .
./poker_game
```

**요구사항:** C++20 지원 컴파일러 (GCC 10+, Clang 13+, MSVC 2019+)

---

## 📖 학습 로드맵

1. **카드 시스템** → `card.hpp` 분석
   - enum class, constexpr 함수
   
2. **핸드 평가** → `hand_evaluator.hpp` 분석
   - 템플릿 특수화, fold expressions

3. **AI 전략** → `ai/*.hpp` 분석
   - CRTP, concepts, type traits

4. **게임 로직** → `game_state.hpp` 분석
   - 상태 머신, variadic templates

---

## 🎓 배울 수 있는 것

- ✅ 실전 템플릿 메타프로그래밍
- ✅ 컴파일타임 최적화 기법
- ✅ 타입 안전 설계 패턴
- ✅ 모던 C++ 관용구
- ✅ 제네릭 프로그래밍

---

## 📊 성능

- **컴파일 타임 핸드 검증** → 런타임 오버헤드 제로
- **인라이닝 최적화** → 함수 호출 비용 없음
- **타입 기반 디스패치** → 가상 함수 오버헤드 제거

---

## 📜 라이센스

MIT License

---

**Made with 🔥 by NoirStar - Template Metaprogramming Enthusiast**
