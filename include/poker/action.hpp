#pragma once
#include <cstddef>

namespace poker {

enum class Action {
    Fold,       // 다이
    Check,      // 체크
    Call,       // 콜
    Bet,        // 삥 (첫 베팅)
    Raise,      // 따당/레이즈
    AllIn       // 올인
};

struct Decision {
    Action action;
    size_t amount{0};  // Bet, Raise, AllIn일 때 금액
};

} // namespace poker