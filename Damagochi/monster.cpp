#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "monster.h"
#include "game.h"
using namespace std;

const string HAPPY_ART = R"(
■■■■■■■■
■□□□□□□■
■□★□□★□■
■□□□□□□■
■□■□□■□■
■□□■■□□■
  ■□□□□■
    ■■■■
)";

const string NORMAL_ART = R"(
■■■■■■■■
■□□□□□□■
■□●□□●□■
■□□□□□□■
■□□□□□□■
■□□■■□□■
  ■□□□□■
    ■■■■
)";

const string SAD_ART = R"(
■■■■■■■■
■□□□□□□■
■□〓□□〓□■
■□□□□□□■
■□□■■□□■
■□■□□■□■
  ■□□□□■
    ■■■■
)";

void monster::UpdateMood() {
	// 세 가지 수치 중 하나라도 30 이하이면 슬픔 상태 (SAD)
	if (hungry <= 30 || funny <= 30 || cleaner <= 30) {
		currentMood = SAD;
	}
	// 세 가지 수치 모두 80 이상이면 기쁨 상태 (HAPPY)
	else if (hungry >= 80 && funny >= 80 && cleaner >= 80) {
		currentMood = HAPPY;
	}
	// 그 외의 경우 (중간 상태)는 보통 상태 (NORMAL)
	else {
		currentMood = NORMAL;
	}
}

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
	if (exp >= 100) {
		exp = 100;
	}

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
		cleaner -= 10;
		cout << "[!랜덤이벤트!] " << name << "이(가) 밥을 먹다가 더러워졌습니다! [건강 10 감소]" << endl;
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

	const int persentage = 2;
	int decreaseClean = rand() % 100;
	if (decreaseClean <= persentage) {
		cleaner -= 100;
		cout << "[!랜덤이벤트!] " << name << "이(가) 씻다가 넘어져 머리를 부딪혔습니다![사망]" << endl;
	}

	cout << "\n(메인 메뉴로 돌아가려면 Enter 키를 누르세요...)";
	system("pause");
}

void monster::play() { //재미 상승
	system("cls");
	cout << name << "이(가) 미니 게임을 시작합니다!" << endl;

	Game miniGame;
	bool gameResult = miniGame.startMiniGame();

	if (gameResult) {
		cout << "\n게임에 성공하여 재미가 상승했습니다! [재미 15 상승]" << endl;
		funny += 15;
		int expGained = rand() % 10 + 1;
		gainExp(expGained);
	}
	else {
		cout << "\n게임에 실패하여 재미에 변화가 없습니다." << endl;
	}

	const int persentage = 50;
	int decreaseClean = rand() % 100;
	if (decreaseClean < persentage) {
		cleaner -= 15;
		cout << "[!랜덤이벤트!] " << name << "이(가) 뛰어다니다가 넘어졌습니다! [건강 15 감소]" << endl;
	}

	if (funny >= 100) {
		funny = 100;
	}

	cout << "\n(메인 메뉴로 돌아가려면 Enter 키를 누르세요...)";
	system("pause");
}

void monster::status(){ //모든 상태 표시
	UpdateMood(); // ⬅️ 상태 출력 전 감정 업데이트

	// ⬅️ 감정 상태에 따른 아스키 아트 출력
	if (currentMood == HAPPY) {
		cout << HAPPY_ART << endl;
	}
	else if (currentMood == NORMAL) {
		cout << NORMAL_ART << endl;
	}
	else {
		cout << SAD_ART << endl;
	}
	cout << "-------------------------" << endl;
	cout << "  주의 사항 : 상태가 0일시 사망  " << endl;
	cout << "---[" << name << "] 현재 상태 ---" << endl;
	cout << "  건강  : " << cleaner << "/100" << endl; //건강 0 죽음 -> 
	cout << "  배고픔: " << hungry << "/100" << endl; // 배고픔 0죽음
	cout << "  재미: " << funny << "/100" << endl; //재미 0죽음
	cout << "  경험치: " << exp << "/100[경험치 100일시 진화]" << " " <<  "레벨 : " << level << endl;
}

void monster::DecreaseStatus() {

	int decreaseAmount = rand() % 10 + 5;
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

