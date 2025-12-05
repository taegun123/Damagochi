#include "game.h"
#include <sstream>
#include <algorithm> // swap 함수 사용을 위해 명시적으로 포함
#include <limits>    // numeric_limits 사용을 위해 유지 (다른 용도로 필요)
#include <windows.h>
using namespace std;

// Windows 콘솔 색상 코드 (기존과 동일)
const int FG_WHITE = 7;
const int FG_RED = 12;
const int FG_GREEN = 10;

// 콘솔 색상 설정 함수 (기존과 동일)
void Game::setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Game::Game() {}

// 1번 게임: 행운의 주사위 게임 (로직 변경 없음)
bool Game::diceGame() {
    system("cls");
    cout << "===  행운의 주사위 게임 ===\n";
    cout << "주사위를 굴려 4 이상이 나오면 성공입니다!\n";
    system("pause");

    int diceRoll = (rand() % 6) + 1;

    cout << "주사위를 굴립니다...";
    Sleep(1000);
    cout << " 결과는 " << diceRoll << "입니다!\n";

    if (diceRoll >= 4) {
        setConsoleColor(FG_GREEN);
        cout << " 성공! 몬스터가 놀이에 성공했습니다. \n";
        setConsoleColor(FG_WHITE);
        return true;
    }
    else {
        setConsoleColor(FG_RED);
        cout << " 실패! 몬스터가 아쉽게 목표를 달성하지 못했습니다.\n";
        setConsoleColor(FG_WHITE);
        return false;
    }
}

// 2번 게임: 랜덤 사칙연산 게임 (입력 처리 부분 수정)
bool Game::mathQuiz() {
    system("cls");
    cout << "===   랜덤 사칙연산 게임 ===\n";
    cout << "제시된 문제를 맞혀주세요!\n";

    int num1 = rand() % 20 + 5;
    int num2 = rand() % 5 + 1;
    int operation = rand() % 2;

    int answer;
    int correctResult;
    char opChar;

    if (operation == 0) {
        opChar = '+';
        correctResult = num1 + num2;
    }
    else {
        opChar = '-';
        if (num1 < num2) swap(num1, num2);
        correctResult = num1 - num2;
    }

    cout << "\n문제: " << num1 << " " << opChar << " " << num2 << " = ?" << endl;; 
    cout << "정답 : ";

    // 사용자 입력 처리 (10000으로 대체)
    if (!(cin >> answer)) {
        cin.clear();
        cin.ignore(10000, '\n'); // ✅ max() 호출 대신 10000 사용
        cout << "\n 입력 오류로 인해 실패했습니다.\n";
        return false;
    }
    cin.ignore(10000, '\n'); // ✅ max() 호출 대신 10000 사용

    // 정답 확인
    if (answer == correctResult) {
        setConsoleColor(FG_GREEN);
        cout << " 정답입니다! 몬스터가 즐거워합니다. \n";
        setConsoleColor(FG_WHITE);
        return true;
    }
    else {
        setConsoleColor(FG_RED);
        cout << " 오답입니다. 정답은 " << correctResult << "였습니다.\n";
        setConsoleColor(FG_WHITE);
        return false;
    }
}

// 메인 게임 선택 및 실행 (입력 처리 부분 수정)
bool Game::startMiniGame() {
    int choice = 0;

    cout << "\n--- 미니 게임 선택 ---" << endl;
    cout << "1.  행운의 주사위 게임 \n";
    cout << "2.  랜덤 사칙연산 게임 \n";
    cout << "----------------------" << endl;

    // 사용자 입력 처리
    do {
        cout << "선택 (1 또는 2): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            choice = 0;
            continue;
        }
        cin.ignore(10000, '\n'); 
    } while (choice < 1 || choice > 2);

    switch (choice) {
    case 1:
        return diceGame();
    case 2:
        return mathQuiz();
    default:
        return false;
    }
}