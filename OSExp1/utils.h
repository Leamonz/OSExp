//
// Created by HP on 2023/4/6.
//

#ifndef OSEXP_UTILS_H
#define OSEXP_UTILS_H

#include <string>
#include <utility>
#include <vector>
#include <list>
#include <windows.h>

using namespace std;
// ��Դ����
const int numResources = 5;
// ������ɽ�������
const int MAX_PROCESSES = 10;

class PCB;
// ϵͳ��ÿ����Դ������
vector<int> Available(numResources);
// ö�ٱ�������ʾ����״̬���У����������С���������״̬
enum ProcessStatus {
    Ready,
    Running,
    Block,
};
// ���̿��ƿ�
class PCB {
private:
    string PID;                 // ��ʶ��Ϣ������ID
    ProcessStatus status{};     // ����״̬
    int runTime{};              // ������������ʱ��
    vector<int> Need;           // ÿ����Դ����������
public:
    PCB() = default;
    // ����PCB
    void create_PCB(string pid, ProcessStatus s, int time, vector<int> res);
    // GetXXX���� --- ��ȡ���̵���Ϣ
    string GetPID() const { return this->PID; }

    ProcessStatus GetStatus() const { return this->status; }

    int GetRunTime() const { return this->runTime; }

    vector<int> &GetNeed() { return this->Need; }
    // SetXXX���� --- ���ý�����Ϣ(ֻ��Ҫ��״̬�����޸�)
    void SetStatus(ProcessStatus s) { this->status = s; };
    // �ͷ���Դ
    void Release();
    // ��������
    bool Run(int time);
};

/**
 *
 * @param pid ����id
 * @param s ����״̬
 * @param time ��������ʱ��
 * @param res ����������Դ��
 */
void PCB::create_PCB(string pid, ProcessStatus s, int time, vector<int> res) {
    this->PID = std::move(pid);
    this->status = s;
    this->runTime = time;
    this->Need = std::move(res);
    cout << "��������" << PID << "\t��������ʱ��: " << runTime << endl;
    cout << "������Դ: ";
    for (auto val: this->Need) {
        cout << val << " ";
    }
    putchar('\n');
}

void PCB::Release() {
    for (int i = 0; i < Available.size(); i++) {
        Available[i] += this->Need[i];
    }
}

/**
 *
 * @param time ����ʱ��
 * @return boolֵ����ʾ�����Ƿ��������
 */
bool PCB::Run(int time) {
    for (int i = 0; i < time; i++) {
        Sleep(250);
        this->runTime--;
        cout << "����" << this->PID << "�����У�ʣ������ʱ��" << this->runTime << endl;
        if (this->runTime == 0) {
            cout << "����" << this->PID << "�������" << endl;
            Release();
            return true;
        }
    }
    Release();
    return false;
}

#endif //OSEXP_UTILS_H
