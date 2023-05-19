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
    // ��ʼ��ϵͳ
    std::default_random_engine re(time(nullptr));
    this->total = MAXBlks;
    this->used = re() % 20; // ��ʼ�� 0~20 ����ʹ���ڴ��
    this->processNum = 0;   // ��ʼ������Ϊ0
    for (int i = 0; i < used; i++) {
        // �����ʼ����ʹ���ڴ��
        int id = re() % 100;
        usedBlocks[i] = id;
        tag[id] = Busy;
    }
    // ��ӡ��ʼ����Ϣ
    Display();
}

void Manager::menu() {
    // ��ӡ�˵�
    printf("=====�����˵�=====\n");
    printf("   1����������\n");
    printf("   2����������\n");
    printf("   3���鿴�ڴ�\n");
    printf("   4���˳�����\n");
    printf("================\n");
}

FuncStatus Manager::AllocProc(int pid, int pageNum) {
    for (int i = 0; i < processNum; i++) {
        if (processes[i]->pid == pid) {
            printf("�Ѿ����ڽ��̺�Ϊ%d�Ľ��̡�\n", pid);
            return Fail;
        }
    }
    int avail = total - used;
    if (avail < pageNum) {
        printf("ʣ���ڴ��%d, �޷���������%d��\n", avail, pageNum);
        return Fail;
    }
    Process *proc = new Process(pid, pageNum);
    proc->blocks = new int[pageNum];
    int n = 0;
    for (int blk = 0; blk < MAXBlks; blk++) {
        // Ϊ�½��̷����ڴ��
        if (tag[blk] == Vacant) {
            tag[blk] = Busy;
            usedBlocks[used] = blk;
            proc->blocks[n] = blk;
            ++n;
            ++used;
            // ������ϣ��˳�
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
            // �ͷŸý���ռ�е��ڴ��
            Release(processes[i]);
            delete processes[i];
            for (int j = i + 1; j < processNum; j++) {
                processes[j - 1] = processes[j];
            }
            processNum--;
            return Success;
        }
    }
    printf("δ�ҵ�����%d��\n", pid);
    return Fail;
}

void Manager::Release(Process *proc) {
    for (int i = 0; i < proc->pageNum; i++) {
        tag[proc->blocks[i]] = Vacant;
    }
}

void Manager::Display() {
    printf("�ڴ�����: %d��\n", total);
    printf("���ÿռ�: %d��\n", used);
    printf("ʣ��ռ�: %d��\n", total - used);
    printf("��������: %d��\n", processNum);
    printf("��ʹ�õ��ڴ��(%d):\n", used);
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
        printf("\n��ǰ�ڴ��޽��̿飡\n");
    } else {
        printf("\n������Ϣ����:\n");
        for (int i = 0; i < processNum; i++) {
            printf("����%dռ���ڴ��: ", processes[i]->pid);
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
        printf("��������Ҫ���еĲ���: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("��������̺ţ�С��100��������ҳ��: ");
                scanf("%d %d", &pid, &pageNum);
                status = AllocProc(pid, pageNum);
                if (status == Success) {
                    printf("�����½��̳ɹ���\n\n");
                } else {
                    printf("�����½���ʧ�ܣ�\n\n");
                }
                break;
            case 2:
                printf("��������̺ţ�С��100��: ");
                scanf("%d", &pid);
                status = KillProc(pid);
                if (status == Success) {
                    printf("��������%d�ɹ���\n\n", pid);
                } else {
                    printf("��������%dʧ�ܣ�\n\n", pid);
                }
                break;
            case 3:
                Display();
                break;
            case 4:
                printf("�˳�����\n\n");
                break;
            default:
                printf("����������������룡\n\n");
                break;
        }
    } while (op != 4);
}

