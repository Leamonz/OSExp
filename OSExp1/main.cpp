#include <iostream>
#include <vector>
#include "utils.h"
#include <ctime>

using namespace std;
// 三个队列，分别表示就绪队列、阻塞队列、空闲队列
// 每次只有一个进程运行，所以没有设置运行队列
list<PCB> lReady;
list<PCB> lBlock;
list<PCB> lVacant(MAX_PROCESSES, PCB());
// 时间片大小
const int TIME_PIECE = 10;

// 输入进程信息
void input() {
    vector<int> temp(numResources);
    string id;
    int time;
    PCB tempPCB;
    cout << "请输入创建进程信息" << endl;
    cout << "PID: ";
    cin >> id;
    cout << "运行时间: ";
    cin >> time;
    cout << "所需资源量: ";
    for (int i = 0; i < numResources; i++) {
        cin >> temp[i];
    }
    tempPCB = lVacant.front();
    lVacant.pop_front();
    tempPCB.create_PCB(id, Ready, time, temp);
    lReady.push_back(tempPCB);
    cout << "创建进程" << tempPCB.GetPID() << ", 已加入就绪队列" << endl;
}

// 系统初始化：初始化系统资源+初始化进程
void init() {
    // 初始化系统资源
    srand((unsigned int) time(nullptr));
    cout << "系统资源量: ";
    for (int &val: Available) {
        // 初始化为5~20的随机数
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
            cout << "进程数以达到最大" << endl;
            break;
        }
        cout << "是否继续创建进程？(Y/N): ";
        cin >> op;
    } while (toupper(op) == 'Y');
}

/**
 *
 * @param runningPCB 要分配资源的进程
 * @return bool值，表示是否允许分配资源
 */
bool Allocate(PCB &runningPCB) {
    vector<int> Need = runningPCB.GetNeed();
    for (int i = 0; i < Available.size(); i++) {
        if (Available[i] < Need[i]) return false;
    }
    // 分配资源
    for (int i = 0; i < Available.size(); i++) {
        Available[i] -= Need[i];
    }
    return true;
}

// 调度算法 时间片轮转
void Dispatch() {
    PCB runningPCB;
    while (true) {
        if (!lReady.empty()) {
            runningPCB = lReady.front();
            lReady.pop_front();
            runningPCB.SetStatus(Running);
        } else {
            cout << "就绪队列为空" << endl;
            break;
        }
        if (!Allocate(runningPCB)) {
            cout << "资源不足，进程阻塞" << endl;
            runningPCB.SetStatus(Block);
            lBlock.push_back(runningPCB);
            continue;
        }
        bool flag = runningPCB.Run(TIME_PIECE);
        if (!flag) {
            cout << "进程" << runningPCB.GetPID() << "未执行完毕,挂入就绪队列" << endl;
            runningPCB.SetStatus(Ready);
            lReady.push_back(runningPCB);
        } else {
            cout << "进程" << runningPCB.GetPID() << "运行完毕, 释放资源" << endl;
            lVacant.push_back(runningPCB);
            // 唤醒阻塞队列
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
