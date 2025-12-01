#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "monster.h"
using namespace std;

monster::monster(string tamagochi) { //기본 상태 수치
	name = tamagochi;
	hungry = 20;
	cleaner = 20;
	funny = 20;
	exp = 0;
	level = 1;

	cout << name << " (이)가 태어났습니다! " << endl;
}

void monster::gainExp(int amount) {
	exp += amount;
	cout << name << "이(가) 경험치 +" << amount << "를 획득했습니다! (총 EXP: " << exp << ")" << endl;
}

void monster::feed() { //배고픔 선택시 배고픔 상승

	cout << name << "이 밥을 먹었습니다. [배고픔 10 상승]" << endl; 
	hungry += 10;
	if (hungry >= 100) {
		hungry = 100;
	}

	//랜덤 청결도 감소
	const int persentage = 50; 
	int decreaseClean = rand() % 100; 
	if(decreaseClean < persentage) {
		cleaner -= 5;
		cout << "[알림] " << name << "이(가) 밥을 먹다가 더러워졌습니다! [청결도 5 감소]" << endl;
	}

	//화면 출력 확인
	cout << "\n(메인 메뉴로 돌아가려면 Enter 키를 누르세요...)";
	system("pause");
}

void monster::clean() { //건강 상승

	cout << name << "깨끗하게 씻었습니다. [건강 10상승]" << endl;
	cleaner += 10;
	if(cleaner >=100){
		cleaner = 100;
	}

	cout << "\n(메인 메뉴로 돌아가려면 Enter 키를 누르세요...)";
	system("pause");
}

void monster::play() { //재미 상승
	cout << name << "신나게 놉니다! 지루함이 줄었습니다. [재미 15상승]" << endl;
	funny += 15;
	hungry -= 5; //놀이 후 배고픔 증가

	const int persentage = 50;
	int decreaseClean = rand() % 100;
	if (decreaseClean < persentage) {
		cleaner -= 5;
		cout << "[알림] " << name << "이(가) 뛰어다니다가 넘어졌습니다! [건강 5 감소]" << endl;
	}

	int expGained = rand() % 11 + 10;
	gainExp(expGained);

	if (funny >= 100) {
		funny = 100;
	}

	cout << "\n(메인 메뉴로 돌아가려면 Enter 키를 누르세요...)";
	system("pause");
}

void monster::status(){ //모든 상태 표시
	cout << "---[" << name << "] 현재 상태 ---" << endl;
	cout << "  건강  : " << cleaner << "/100" << endl; //건강 0 죽음 -> 
	cout << "  배고픔: " << hungry << "/100" << endl; // 배고픔 0죽음
	cout << "  재미: " << funny << "/100" << endl; //재미 0죽음
	cout << "  경험치: " << exp << "/100[경험치 100일시 진화]" << " " <<  "레벨 : " << level << endl;
}

void monster::DecreaseStatus() {

	const int MIN_DECREASE = 3;
	const int MAX_DECREASE = 7;
	int decreaseAmount = rand() % (MAX_DECREASE - MIN_DECREASE + 1) + MIN_DECREASE;

	int eventChoice = rand() % 3;
	switch (eventChoice) {
	case 0: // 첫 번째: 배고픔 수치 감소
		hungry -= decreaseAmount;
		cout << "[알림] " << name << "이(가) 배가 고파졌습니다! [배고픔 " << decreaseAmount << " 감소]" << endl;
		break;

	case 1: // 두 번째: 재미 수치 감소
		funny -= decreaseAmount;
		cout << "[알림] " << name << "이(가) 지루해졌습니다! [재미 " << decreaseAmount << " 감소]" << endl;
		break;

	case 2: // 세 번째: 청결도 수치 감소
		cleaner -= decreaseAmount;
		cout << "[알림] " << name << "이(가) 더러워졌습니다! [건강 " << decreaseAmount << " 감소]" << endl;
		break;
	}


	if (hungry < 0) hungry = 0;
	if (cleaner < 0) cleaner = 0;
	if (funny < 0) funny = 0;
}

bool monster::IsDead() {
	if (hungry <= 0 || cleaner <= 0 || funny <= 0) {
		return true;
	}
	return false;
}