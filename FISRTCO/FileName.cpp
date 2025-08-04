#include <iostream> //C++표준 라이브러리
#include <string> //c++에서 std::string을 사용하려면 꼭 해줘야함
#include <cstdlib> //-->stdlib.h (다양한 유틸리티 제공, 난수 등)
#include <ctime> //time(0)(난수 발생 함수) 이건 srand(time(0))이렇게 사용되며, 출력할때마다 랜덤값나옴, rand()는 매번 같은값
#include <map> //map<string, int> inventory;이렇게 선언해주고 inventory["빤스"]++; 인벤토리에 빤스 한개 추가
#include <stdio.h>
//cstdio=stdio.h 인데 표준 함수가std이름 공간에 있는거임 stdio.h는 global namespace에 있는거고
//그래서 std::printf("")는 cstdio에서만 사용 가능함
//마찬가지로 stdlib.h->cstdlib
using namespace std; //C++에서 아주 중요함 : std:: 생략 가능

int main() {
    srand(static_cast<unsigned int>(time(0)));//static_cast<변환할 타입>(변환할 대상) 여기서는 time()가 time_t타입 즉 명시적이지 않은 타입이 사용되어서 안전하게 명시적으로 변환해주는거임
    //=srand(time(0)); 가능하긴 하는데 안전하고 의도를 명확히 보여주는 습관을 기르는게 좋다
    int a = 0;
    while (a == 0) {

        string name; //네임 변수를 설정해주는거임
        int playerHP = 100;
        int dragonHP = 400;
        int coins = 0;
        bool hasChain = false;//자료형 체인 초기값, 체인 가졌냐?
        map<string, int> inventory;//인벤토리라는 이름을 가진 문자열과 개수를 받음

        cout << "캐릭터 이름을 입력하세요: ";
        cin.ignore();//예를들어 이름[엔터]를 하면 cout는 이름만 받고 \n는 버퍼에 계속 남아있어서 이걸 지워주는 용도
        getline(cin, name);

        while (playerHP > 0 && dragonHP > 0) {
            cout << "\n==========\n";
            cout << name << " HP: " << playerHP << " | 드래곤 HP: " << dragonHP << " | 코인: " << coins << "\n";
            cout << "1. 공격\n2. 도망\n3. 상점\n4. 인벤토리\n선택하세요: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int playerDamage = rand() % 6 + 5; // 5~10
                if (hasChain) playerDamage += 3;
                int dragonDamage = rand() % 5 + 1; // 1~5

                dragonHP -= playerDamage;
                playerHP -= dragonDamage;
                coins += 10;

                cout << name << "의 공격! 드래곤에게 " << playerDamage << "의 피해를 입혔습니다.\n";
                cout << "드래곤의 반격! " << name << "은(는) " << dragonDamage << "의 피해를 입었습니다.\n";
            }
            else if (choice == 2) {
                cout << name << "이(가) 도망쳤습니다. 다음 턴으로 넘어갑니다.\n";
            }
            else if (choice == 3) {
                cout << "\n--- 상점 ---\n";
                cout << "1. 쇠사슬 (공격력 +3, 30코인)\n";
                cout << "2. 빤스 (20% 확률 드래곤 즉사, 50코인)\n";
                cout << "3. 흡수 (50% 성공시 드래곤HP -20 & 내 HP +20, 실패시 드래곤HP +30 & 내 HP -30, 10코인)\n";
                cout << "구매할 항목을 선택하세요 (0. 나가기): ";
                int shopChoice;
                cin >> shopChoice;

                if (shopChoice == 1 && coins >= 30) {
                    hasChain = true;
                    coins -= 30;
                    cout << "쇠사슬을 구매했습니다! 공격력이 증가합니다.\n";
                }
                else if (shopChoice == 2 && coins >= 50) {
                    inventory["빤스"]++;
                    coins -= 50;
                    cout << "빤스를 구매했습니다. 인벤토리에서 사용할 수 있습니다.\n";
                }
                else if (shopChoice == 3 && coins >= 10) {
                    inventory["흡수"]++;
                    coins -= 10;
                    cout << "흡수 아이템을 구매했습니다. 인벤토리에서 사용할 수 있습니다.\n";
                }
                else if (shopChoice == 0) {
                    cout << "상점에서 나갑니다.\n";
                }
                else {
                    cout << "코인이 부족하거나 잘못된 선택입니다.\n";
                }

            }
            else if (choice == 4) {
                cout << "\n--- 인벤토리 ---\n";
                cout << "1. 빤스 (" << inventory["빤스"] << "개)\n";
                cout << "2. 흡수 (" << inventory["흡수"] << "개)\n";
                cout << "0. 나가기\n";
                cout << "사용할 아이템을 선택하세요: ";
                int invChoice;
                cin >> invChoice;

                if (invChoice == 1) {
                    if (inventory["빤스"] > 0) {
                        inventory["빤스"]--;
                        int chance = rand() % 100;
                        if (chance < 20) {
                            cout << "빤스를 사용! 드래곤이 기절했습니다. 즉사!\n";
                            dragonHP = 0;
                        }
                        else {
                            cout << "빤스를 사용했지만 효과가 없었습니다.\n";
                        }
                        cout << name << " HP: " << playerHP << " | 드래곤 HP: " << dragonHP << endl;
                    }
                    else {
                        cout << "빤스가 없습니다.\n";
                    }
                }
                else if (invChoice == 2) {
                    if (inventory["흡수"] > 0) {
                        inventory["흡수"]--;
                        int chance = rand() % 100;
                        if (chance < 50) {
                            cout << "흡수 성공! 드래곤 HP -20, " << name << " HP +20\n";
                            dragonHP -= 20;
                            playerHP += 20;
                            if (playerHP > 100) playerHP = 100;
                        }
                        else {
                            cout << "흡수 실패! 드래곤 HP +30, " << name << " HP -30\n";
                            dragonHP += 30;
                            if (dragonHP > 400) dragonHP = 400;
                            playerHP -= 30;
                        }
                        cout << name << " HP: " << playerHP << " | 드래곤 HP: " << dragonHP << endl;
                    }
                    else {
                        cout << "흡수 아이템이 없습니다.\n";
                    }
                }
                else if (invChoice == 0) {
                    cout << "인벤토리에서 나갑니다.\n";
                }
                else {
                    cout << "잘못된 선택입니다.\n";
                }

            }
            else {
                cout << "잘못된 선택입니다.\n";
            }
        }

        cout << "\n==========\n";
        if (playerHP <= 0 && dragonHP <= 0) {
            cout << "드래곤과 " << name << " 둘 다 쓰러졌습니다! 무승부입니다.\n";
            printf("다시 할래?");
            scanf_s(" %d", &a);
        }
        else if (playerHP <= 0) {
            cout << name << "이(가) 쓰러졌습니다. 게임 오버!\n";
            printf("다시 할래?");
            scanf_s(" %d", &a);
        }
        else {
            cout << "드래곤을 물리쳤습니다! 승리!\n";
            printf("다시 할래?");
            scanf_s(" %d", &a);
        }

    }
    return 0;
}
//std::이건 내가 선언한 string이랑 헷갈리지 말라고 "standard의 ()이야"라고 지정해주는거임 생략 가능함