#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <stdio.h>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int a = 0;
    while (a == 0) {

        string name;
        int playerHP = 100;
        int dragonHP = 400;
        int coins = 0;
        bool hasChain = false;
        map<string, int> inventory;

        cout << "ĳ���� �̸��� �Է��ϼ���: ";
        cin.ignore();
        getline(cin, name);

        while (playerHP > 0 && dragonHP > 0) {
            cout << "\n==========\n";
            cout << name << " HP: " << playerHP << " | �巡�� HP: " << dragonHP << " | ����: " << coins << "\n";
            cout << "1. ����\n2. ����\n3. ����\n4. �κ��丮\n�����ϼ���: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int playerDamage = rand() % 6 + 5; // 5~10
                if (hasChain) playerDamage += 3;
                int dragonDamage = rand() % 5 + 1; // 1~5

                dragonHP -= playerDamage;
                playerHP -= dragonDamage;
                coins += 10;

                cout << name << "�� ����! �巡�￡�� " << playerDamage << "�� ���ظ� �������ϴ�.\n";
                cout << "�巡���� �ݰ�! " << name << "��(��) " << dragonDamage << "�� ���ظ� �Ծ����ϴ�.\n";
            }
            else if (choice == 2) {
                cout << name << "��(��) �����ƽ��ϴ�. ���� ������ �Ѿ�ϴ�.\n";
            }
            else if (choice == 3) {
                cout << "\n--- ���� ---\n";
                cout << "1. ��罽 (���ݷ� +3, 30����)\n";
                cout << "2. ���� (20% Ȯ�� �巡�� ���, 50����)\n";
                cout << "3. ��� (50% ������ �巡��HP -20 & �� HP +20, ���н� �巡��HP +30 & �� HP -30, 10����)\n";
                cout << "������ �׸��� �����ϼ��� (0. ������): ";
                int shopChoice;
                cin >> shopChoice;

                if (shopChoice == 1 && coins >= 30) {
                    hasChain = true;
                    coins -= 30;
                    cout << "��罽�� �����߽��ϴ�! ���ݷ��� �����մϴ�.\n";
                }
                else if (shopChoice == 2 && coins >= 50) {
                    inventory["����"]++;
                    coins -= 50;
                    cout << "������ �����߽��ϴ�. �κ��丮���� ����� �� �ֽ��ϴ�.\n";
                }
                else if (shopChoice == 3 && coins >= 10) {
                    inventory["���"]++;
                    coins -= 10;
                    cout << "��� �������� �����߽��ϴ�. �κ��丮���� ����� �� �ֽ��ϴ�.\n";
                }
                else if (shopChoice == 0) {
                    cout << "�������� �����ϴ�.\n";
                }
                else {
                    cout << "������ �����ϰų� �߸��� �����Դϴ�.\n";
                }

            }
            else if (choice == 4) {
                cout << "\n--- �κ��丮 ---\n";
                cout << "1. ���� (" << inventory["����"] << "��)\n";
                cout << "2. ��� (" << inventory["���"] << "��)\n";
                cout << "0. ������\n";
                cout << "����� �������� �����ϼ���: ";
                int invChoice;
                cin >> invChoice;

                if (invChoice == 1) {
                    if (inventory["����"] > 0) {
                        inventory["����"]--;
                        int chance = rand() % 100;
                        if (chance < 20) {
                            cout << "������ ���! �巡���� �����߽��ϴ�. ���!\n";
                            dragonHP = 0;
                        }
                        else {
                            cout << "������ ��������� ȿ���� �������ϴ�.\n";
                        }
                        cout << name << " HP: " << playerHP << " | �巡�� HP: " << dragonHP << endl;
                    }
                    else {
                        cout << "������ �����ϴ�.\n";
                    }
                }
                else if (invChoice == 2) {
                    if (inventory["���"] > 0) {
                        inventory["���"]--;
                        int chance = rand() % 100;
                        if (chance < 50) {
                            cout << "��� ����! �巡�� HP -20, " << name << " HP +20\n";
                            dragonHP -= 20;
                            playerHP += 20;
                            if (playerHP > 100) playerHP = 100;
                        }
                        else {
                            cout << "��� ����! �巡�� HP +30, " << name << " HP -30\n";
                            dragonHP += 30;
                            if (dragonHP > 400) dragonHP = 400;
                            playerHP -= 30;
                        }
                        cout << name << " HP: " << playerHP << " | �巡�� HP: " << dragonHP << endl;
                    }
                    else {
                        cout << "��� �������� �����ϴ�.\n";
                    }
                }
                else if (invChoice == 0) {
                    cout << "�κ��丮���� �����ϴ�.\n";
                }
                else {
                    cout << "�߸��� �����Դϴ�.\n";
                }

            }
            else {
                cout << "�߸��� �����Դϴ�.\n";
            }
        }

        cout << "\n==========\n";
        if (playerHP <= 0 && dragonHP <= 0) {
            cout << "�巡��� " << name << " �� �� ���������ϴ�! ���º��Դϴ�.\n";
            printf("�ٽ� �ҷ�?");
            scanf_s(" %d", &a);
        }
        else if (playerHP <= 0) {
            cout << name << "��(��) ���������ϴ�. ���� ����!\n";
            printf("�ٽ� �ҷ�?");
            scanf_s(" %d", &a);
        }
        else {
            cout << "�巡���� �����ƽ��ϴ�! �¸�!\n";
            printf("�ٽ� �ҷ�?");
            scanf_s(" %d", &a);
        }

    }
    return 0;
}
//����