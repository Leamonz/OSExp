//
// Created by HP on 2023/5/18.
//

#ifndef OSEXP4_MANAGER_H
#define OSEXP4_MANAGER_H
const int MAXBlks = 100;
const int MAXProcs = 100;
// ���򷵻�״̬
enum FuncStatus {
    Fail = 0,   // ʧ��
    Success = 1 // �ɹ�
};
// �ڴ��״̬
enum MemStatus {
    Vacant = 0, // ����
    Busy = 1    // æµ
};

struct Process {
    int pid;    // ���̺�
    int pageNum;// �����ڴ����
    int *blocks;// ��¼ռ�õ��ڴ��

    Process(int, int);

    ~Process();
};

class Manager {
private:
    int total;  // �ڴ��ܿ���
    int used;   // �ڴ���ʹ�ÿ���
    int processNum; // ��������
    int usedBlocks[MAXBlks];    // ��¼��ʹ�õ��ڴ��
    MemStatus tag[MAXBlks];     // ���λ����¼ÿ���ڴ���Ƿ����
    Process *processes[MAXProcs];   // ��¼���н���

public:
    Manager() = default;
    // �����ʼ��
    void init();
    // �˵�
    static void menu();
    // ��������
    FuncStatus AllocProc(int, int);
    // ��������
    FuncStatus KillProc(int);
    // �ͷŽ���ռ���ڴ��
    void Release(Process *);
    // ��ӡ�ڴ���Ϣ
    void Display();
    // ���й������
    void Run();

};

#endif //OSEXP4_MANAGER_H
