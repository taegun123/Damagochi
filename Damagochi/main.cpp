#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <chrono>
#include "monster.h"
#include "timer.h"
#include "evolution.h"
using namespace std;

const long long DECREASE_INTERVAL_MS = 5000;
const int EVOLUTION_EXP_THRESHOLD = 100;

void GameLoop(monster* pet);

int main() {
    char choice;

    cout << "===========================================" << endl;
    cout << R"(
                                                                                                  
#######                                       ##         
#  #  #                                        #      #  
#  #  #                                        #         
   #     ##   # ## ##    ##    ####  ##   ###  ###   ##  
   #    #  #   #  #  #  #  #  #  #  #  # #  #  #  #   #  
   #     ###   #  #  #   ###  #  #  #  # #     #  #   #  
   #    #  #   #  #  #  #  #   ##   #  # #  #  #  #   #  
  ###   ##### ### ## ## #####  ####  ##   ##   ## ## ### 
                              #   #                      
                               ###                       

)" << endl;
    cout << "===========================================" << endl;

    cout << "프로그램을 시작하시겠습니까? (Y/N): ";

    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'y' || choice == 'Y') {
        cout << " 펫의 이름을 지어주세요: ";
        string petName;
        getline(cin, petName);

        monster* myPet = new monster(petName);
        GameLoop(myPet);
		
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "프로그램을 종료합니다. 다음에 만나요!" << endl;
    }
    else {
        cout << "잘못된 입력입니다. 프로그램을 종료합니다." << endl;
    }

    cout << "[프로그램 종료]" << endl;

    return 0;

}

void GameLoop(monster* pet) {
    int menuChoice = 0;
    Timer statusTimer;

    while (true) {

        if (pet->exp >= EVOLUTION_EXP_THRESHOLD && pet->level == 1) {

            cout << "\n🌟🌟🌟 축하합니다! " << pet->name << "이(가) 진화합니다! 🌟🌟🌟" << endl;
            system("pause");

            string newName = pet->name; // 기존 이름 유지
            delete pet; // 기존 객체 메모리 해제

            // 새로운 진화형 객체를 동적 할당하고 포인터 교체 (다형성)
            pet = new stage2_monster(newName);

            statusTimer.Reset(); // 진화 후 타이머 리셋
            continue; // 루프를 다시 시작하여 화면 갱신
        }

        system("cls");

        if (pet->IsDead()) {
            cout << "\n===================================" << endl;
            cout << pet->name << " (이)가 돌봐주지 않아 사망했습니다..." << endl;
            cout << "              GAME OVER              " << endl;
            cout << "===================================" << endl;
            break;
        }

        if (pet->level == 2 && pet->cleaner == 100 && pet->funny == 100 && pet->hungry == 100) {
            system("cls");

            cout << "\n===================================" << endl;
            cout << "축하합니다! " << pet->name << "이(가) 완전히 성장하여 독립을 위해 떠나였습니다! 🎉🎉🎉" << endl;
            cout << "===================================" << endl;

            break;
        }

        long long elapsed = statusTimer.GetElapsedMilliseconds();
        if (elapsed >= DECREASE_INTERVAL_MS) {
            pet->DecreaseStatus(); // 상태 수치 감소
            statusTimer.Reset();  // 타이머 재설정
        }

        pet->status();

        cout << "\n--- 행동 메뉴 ---" << endl;
        cout << "1. 밥 주기 " << endl;
        cout << "2. 놀아주기 " << endl;
        cout << "3. 씻겨주기" << endl;
        cout << "4. 종료 (Exit)" << endl;
        cout << "-----------------" << endl;
        cout << "메뉴를 선택하세요: ";

        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            pet->feed();
            break;
        case 2:
            pet->play();
            break;
        case 3:
            pet->clean();
            break;
        case 4:
            cout << "게임을 종료합니다." << endl;
            delete pet; // 동적 할당된 메모리 해제
            return;

            cout << "\n(계속하려면 Enter 키를 누르세요...)";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

}

