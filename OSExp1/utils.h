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
// 资源种类
const int numResources = 5;
// 最大容纳进程数量
const int MAX_PROCESSES = 10;

class PCB;
// 系统中每种资源的数量
vector<int> Available(numResources);
// 枚举变量，表示进程状态，有：就绪、运行、阻塞三种状态
enum ProcessStatus {
    Ready,
    Running,
    Block,
};
// 进程控制块
class PCB {
private:
    string PID;                 // 标识信息：进程ID
    ProcessStatus status{};     // 进程状态
    int runTime{};              // 进程所需运行时间
    vector<int> Need;           // 每种资源进程所需量
public:
    PCB() = default;
    // 创建PCB
    void create_PCB(string pid, ProcessStatus s, int time, vector<int> res);
    // GetXXX函数 --- 获取进程的信息
    string GetPID() const { return this->PID; }

    ProcessStatus GetStatus() const { return this->status; }

    int GetRunTime() const { return this->runTime; }

    vector<int> &GetNeed() { return this->Need; }
    // SetXXX函数 --- 设置进程信息(只需要对状态进行修改)
    void SetStatus(ProcessStatus s) { this->status = s; };
    // 释放资源
    void Release();
    // 进程运行
    bool Run(int time);
};

/**
 *
 * @param pid 进程id
 * @param s 进程状态
 * @param time 进程运行时间
 * @param res 进程所需资源量
 */
void PCB::create_PCB(string pid, ProcessStatus s, int time, vector<int> res) {
    this->PID = std::move(pid);
    this->status = s;
    this->runTime = time;
    this->Need = std::move(res);
    cout << "创建进程" << PID << "\t所需运行时间: " << runTime << endl;
    cout << "所需资源: ";
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
 * @param time 运行时间
 * @return bool值，表示进程是否运行完毕
 */
bool PCB::Run(int time) {
    for (int i = 0; i < time; i++) {
        Sleep(250);
        this->runTime--;
        cout << "进程" << this->PID << "运行中，剩余运行时间" << this->runTime << endl;
        if (this->runTime == 0) {
            cout << "进程" << this->PID << "运行完毕" << endl;
            Release();
            return true;
        }
    }
    Release();
    return false;
}

#endif //OSEXP_UTILS_H
