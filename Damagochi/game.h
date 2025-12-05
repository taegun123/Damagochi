#pragma once
#include <iostream>
#include <cstdlib>
#include <windows.h> // 콘솔 색상 및 Sleep 함수를 위해
#include <limits>    // 입력 버퍼 처리를 위해
#include <ctime>     // srand
using namespace std;

class Game {
private:
    // 콘솔 색상 설정 유틸리티 (Windows 전용)
    void setConsoleColor(int color);

    // 1번 게임: 행운의 주사위 게임
    bool diceGame();

    // 2번 게임: 랜덤 사칙연산 게임
    bool mathQuiz();

public:
    Game();
    // 사용자가 1 또는 2를 선택하여 미니 게임을 시작하고 결과를 반환합니다.
    bool startMiniGame();
};