//
// Created by HP on 2023/5/18.
//
#include "Manager.h"
#include <random>
#include <cstdio>
#include <algorithm>
#include <ctime>

Process::Process(int id, int num) {
    pid = id;
    pageNum = num;
}

Process::~Process() {
    delete[] blocks;
}

void Manager::init() {
    // 初始化系统
    std::default_random_engine re(time(nullptr));
    this->total = MAXBlks;
    this->used = re() % 20; // 初始化 0~20 块已使用内存块
    this->processNum = 0;   // 初始进程数为0
    for (int i = 0; i < used; i++) {
        // 随机初始化已使用内存块
        int id = re() % 100;
        usedBlocks[i] = id;
        tag[id] = Busy;
    }
    // 打印初始化信息
    Display();
}

void Manager::menu() {
    // 打印菜单
    printf("=====操作菜单=====\n");
    printf("   1、创建进程\n");
    printf("   2、结束进程\n");
    printf("   3、查看内存\n");
    printf("   4、退出程序\n");
    printf("================\n");
}

FuncStatus Manager::AllocProc(int pid, int pageNum) {
    for (int i = 0; i < processNum; i++) {
        if (processes[i]->pid == pid) {
            printf("已经存在进程号为%d的进程。\n", pid);
            return Fail;
        }
    }
    int avail = total - used;
    if (avail < pageNum) {
        printf("剩余内存块%d, 无法满足需求%d。\n", avail, pageNum);
        return Fail;
    }
    Process *proc = new Process(pid, pageNum);
    proc->blocks = new int[pageNum];
    int n = 0;
    for (int blk = 0; blk < MAXBlks; blk++) {
        // 为新进程分配内存块
        if (tag[blk] == Vacant) {
            tag[blk] = Busy;
            usedBlocks[used] = blk;
            proc->blocks[n] = blk;
            ++n;
            ++used;
            // 分配完毕，退出
            if (n == pageNum) break;
        }
    }
    processes[processNum] = proc;
    ++processNum;
    return Success;
}

FuncStatus Manager::KillProc(int pid) {
    for (int i = 0; i < processNum; i++) {
        if (processes[i]->pid == pid) {
            // 释放该进程占有的内存块
            Release(processes[i]);
            delete processes[i];
            for (int j = i + 1; j < processNum; j++) {
                processes[j - 1] = processes[j];
            }
            processNum--;
            return Success;
        }
    }
    printf("未找到进程%d。\n", pid);
    return Fail;
}

void Manager::Release(Process *proc) {
    for (int i = 0; i < proc->pageNum; i++) {
        tag[proc->blocks[i]] = Vacant;
    }
}

void Manager::Display() {
    printf("内存总量: %d块\n", total);
    printf("已用空间: %d块\n", used);
    printf("剩余空间: %d块\n", total - used);
    printf("进程总数: %d个\n", processNum);
    printf("已使用的内存块(%d):\n", used);
    std::sort(usedBlocks, usedBlocks + used);
    int c = 0;
    for (int i = 0; i < used; i++) {
        printf("%02d ", usedBlocks[i]);
        c++;
        if (c == 10) {
            putchar('\n');
            c = 0;
        }
    }
    if (processNum == 0) {
        printf("\n当前内存无进程块！\n");
    } else {
        printf("\n进程信息如下:\n");
        for (int i = 0; i < processNum; i++) {
            printf("进程%d占有内存块: ", processes[i]->pid);
            for (int j = 0; j < processes[i]->pageNum; j++) {
                printf("%02d ", processes[i]->blocks[j]);
            }
            putchar('\n');
        }
    }
    puts("\n\n\n");
}

void Manager::Run() {
    init();
    int op = 0, pid, pageNum;
    FuncStatus status;
    do {
        menu();
        printf("请输入您要进行的操作: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("请输入进程号（小于100）和所需页面: ");
                scanf("%d %d", &pid, &pageNum);
                status = AllocProc(pid, pageNum);
                if (status == Success) {
                    printf("创建新进程成功！\n\n");
                } else {
                    printf("创建新进程失败！\n\n");
                }
                break;
            case 2:
                printf("请输入进程号（小于100）: ");
                scanf("%d", &pid);
                status = KillProc(pid);
                if (status == Success) {
                    printf("结束进程%d成功！\n\n", pid);
                } else {
                    printf("结束进程%d失败！\n\n", pid);
                }
                break;
            case 3:
                Display();
                break;
            case 4:
                printf("退出程序！\n\n");
                break;
            default:
                printf("输入错误，请重新输入！\n\n");
                break;
        }
    } while (op != 4);
}

