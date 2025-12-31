cmake_minimum_required(VERSION 3.20)
project(modern-cpp-poker VERSION 1.0.0 LANGUAGES CXX)

# C++20 필수
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 컴파일러 경고 활성화
if(MSVC)
    add_compile_options(/W4 /WX /wd4819)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# 인클루드 디렉토리
include_directories(${CMAKE_SOURCE_DIR}/include)

# 실행 파일
add_executable(poker_game
    src/main.cpp
)

# 컴파일러별 최적화
if(CMAKE_BUILD_TYPE MATCHES Release)
    if(MSVC)
        target_compile_options(poker_game PRIVATE /O2)
    else()
        target_compile_options(poker_game PRIVATE -O3 -march=native)
    endif()
endif()

# 헤더 파일들 (IDE에서 보이게)
target_sources(poker_game PRIVATE
    include/poker/card.hpp
    include/poker/hand.hpp
    include/poker/concepts.hpp
)
