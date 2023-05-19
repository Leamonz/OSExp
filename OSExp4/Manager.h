//
// Created by HP on 2023/5/18.
//

#ifndef OSEXP4_MANAGER_H
#define OSEXP4_MANAGER_H
const int MAXBlks = 100;
const int MAXProcs = 100;
// 程序返回状态
enum FuncStatus {
    Fail = 0,   // 失败
    Success = 1 // 成功
};
// 内存块状态
enum MemStatus {
    Vacant = 0, // 空闲
    Busy = 1    // 忙碌
};

struct Process {
    int pid;    // 进程号
    int pageNum;// 申请内存块数
    int *blocks;// 记录占用的内存块

    Process(int, int);

    ~Process();
};

class Manager {
private:
    int total;  // 内存总块数
    int used;   // 内存已使用块数
    int processNum; // 进程总数
    int usedBlocks[MAXBlks];    // 记录已使用的内存块
    MemStatus tag[MAXBlks];     // 标记位，记录每个内存块是否空闲
    Process *processes[MAXProcs];   // 记录所有进程

public:
    Manager() = default;
    // 随机初始化
    void init();
    // 菜单
    static void menu();
    // 创建进程
    FuncStatus AllocProc(int, int);
    // 结束进程
    FuncStatus KillProc(int);
    // 释放进程占有内存块
    void Release(Process *);
    // 打印内存信息
    void Display();
    // 运行管理程序
    void Run();

};

#endif //OSEXP4_MANAGER_H
