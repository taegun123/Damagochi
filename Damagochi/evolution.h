#pragma once
#include "monster.h"
using namespace std;

// monster 클래스를 공개 상속 받습니다.
class stage2_monster : public monster {
public:
    // 생성자: 기본 클래스 monster의 생성자를 호출하고 진화 정보를 설정합니다.
    stage2_monster(string tamagochi) : monster(tamagochi) {
        this->name = tamagochi + " V2"; // 이름에 V2를 붙입니다.
        this->level = 2;
        this->exp = 0; // 진화 후 경험치 초기화

        // 진화 보너스: 기본 수치를 높게 설정합니다.
        this->hungry = 50;
        this->cleaner = 50;
        this->funny = 50;

        cout << name << "(으)로 진화 완료! 새로운 상태를 확인하세요." << endl;
    }

    // 이 클래스만의 새로운 기능이나 오버라이드된 함수를 추가할 수 있습니다.

    // checkEvolution() 오버라이드: 더 이상의 진화는 없다고 가정
    bool checkEvolution() override {
        return false;
    }
};