#include <iostream>
#include "game.h"
using namespace std;

void game::gameResult() {
	if (gameResult == 1) {
		cout << "게임에 성공했습니다!" << endl;
	}
	else {
		cout << "게임에 실패했습니다!" << endl;
	}
}

void game::start(){
	cout << "게임을 시작합니다!" << endl;
	cin >> choice;

	switch (choice){
	case 0:
		gameResult = 0;
		cout << "게임에 실패했습니다!" << endl;
		break;
	case 1:
		gameResult = 1;
		cout << "게임에 성공했습니다!" << endl;
		break;
	}


}
