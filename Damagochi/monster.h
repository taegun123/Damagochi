#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum Mood {
	HAPPY,  // 기쁨 (상태 양호)
	NORMAL, // 보통 (상태 중간)
	SAD     // 슬픔 (상태 나쁨/위험)
};

class monster {
public:
	string name;
	int hungry; //배고픔 수치 
	int funny; //흥미도 수치 
	int cleaner; //청결도 수치
	int exp;
	int level;
	monster(string tamagochi);

	void feed(); //먹이주기
	void clean(); //씻겨주기
	void play(); //게임하기
	void status();

	Mood currentMood;
	void UpdateMood();

	//시간 경과에 따라 상태 수치를 감소시킵니다.

	void DecreaseStatus();

	// 몬스터의 생사 여부를 확인합니다.
	bool IsDead();

	void gainExp(int amount);
	virtual bool checkEvolution() { return false; } // 가상 함수로 진화 확인 (기본은 false)

	virtual ~monster() {}
};
