#include <iostream>
#include <vector>
#include "utils.h"
#include <ctime>

using namespace std;
// �������У��ֱ��ʾ�������С��������С����ж���
// ÿ��ֻ��һ���������У�����û���������ж���
list<PCB> lReady;
list<PCB> lBlock;
list<PCB> lVacant(MAX_PROCESSES, PCB());
// ʱ��Ƭ��С
const int TIME_PIECE = 10;

// ���������Ϣ
void input() {
    vector<int> temp(numResources);
    string id;
    int time;
    PCB tempPCB;
    cout << "�����봴��������Ϣ" << endl;
    cout << "PID: ";
    cin >> id;
    cout << "����ʱ��: ";
    cin >> time;
    cout << "������Դ��: ";
    for (int i = 0; i < numResources; i++) {
        cin >> temp[i];
    }
    tempPCB = lVacant.front();
    lVacant.pop_front();
    tempPCB.create_PCB(id, Ready, time, temp);
    lReady.push_back(tempPCB);
    cout << "��������" << tempPCB.GetPID() << ", �Ѽ����������" << endl;
}

// ϵͳ��ʼ������ʼ��ϵͳ��Դ+��ʼ������
void init() {
    // ��ʼ��ϵͳ��Դ
    srand((unsigned int) time(nullptr));
    cout << "ϵͳ��Դ��: ";
    for (int &val: Available) {
        // ��ʼ��Ϊ5~20�������
        val = (int) (rand()) % 16 + 5;
        cout << val << ' ';
    }
    putchar('\n');
    int n = 0;
    char op;
    do {
        input();
        n++;
        if (n >= MAX_PROCESSES) {
            cout << "�������Դﵽ���" << endl;
            break;
        }
        cout << "�Ƿ�����������̣�(Y/N): ";
        cin >> op;
    } while (toupper(op) == 'Y');
}

/**
 *
 * @param runningPCB Ҫ������Դ�Ľ���
 * @return boolֵ����ʾ�Ƿ����������Դ
 */
bool Allocate(PCB &runningPCB) {
    vector<int> Need = runningPCB.GetNeed();
    for (int i = 0; i < Available.size(); i++) {
        if (Available[i] < Need[i]) return false;
    }
    // ������Դ
    for (int i = 0; i < Available.size(); i++) {
        Available[i] -= Need[i];
    }
    return true;
}

// �����㷨 ʱ��Ƭ��ת
void Dispatch() {
    PCB runningPCB;
    while (true) {
        if (!lReady.empty()) {
            runningPCB = lReady.front();
            lReady.pop_front();
            runningPCB.SetStatus(Running);
        } else {
            cout << "��������Ϊ��" << endl;
            break;
        }
        if (!Allocate(runningPCB)) {
            cout << "��Դ���㣬��������" << endl;
            runningPCB.SetStatus(Block);
            lBlock.push_back(runningPCB);
            continue;
        }
        bool flag = runningPCB.Run(TIME_PIECE);
        if (!flag) {
            cout << "����" << runningPCB.GetPID() << "δִ�����,�����������" << endl;
            runningPCB.SetStatus(Ready);
            lReady.push_back(runningPCB);
        } else {
            cout << "����" << runningPCB.GetPID() << "�������, �ͷ���Դ" << endl;
            lVacant.push_back(runningPCB);
            // ������������
            if (!lBlock.empty()) {
                PCB tempPCB = lBlock.front();
                lBlock.pop_front();
                tempPCB.SetStatus(Ready);
            }
        }
    }
}

int main() {
    init();
    Dispatch();
    return 0;
}
