////
//// Created by HP on 2023/4/29.
////
//
//#include <iostream>
//#include <windows.h>
//#include <string>
//#include "utils.h"
//
//using namespace std;
//
//const int N = 5;    // ��ѧ������
//HANDLE mutex = CreateMutex(nullptr, false, "mutex");    // ��ѧ�һ���Ͳͣ���������
//HANDLE chopsticks[5];   // �ź�������ʾ��֧����
//
////CRITICAL_SECTION P_MUTEX;
////int chopsticks[5] = {0, 0, 0, 0, 0};
////void PhilosopherThread(int x) {
////
////    WaitForSingleObject(mutex, INFINITE);
////    cout << "Philosopher " << x << " sends the require for chopsticks " << x << " and " << (x + 1) % N << endl;
////
////    while (chopsticks[x] == 1);
////    chopsticks[x] = 1;
////    while (chopsticks[(x + 1) % N] == 1);
////    chopsticks[(x + 1) % N] = 1;
////    cout << "Philosopher " << x << " is eating." << endl;
////    sleep(3);
////    chopsticks[x] = 0;
////    chopsticks[(x + 1) % N] = 0;
////    cout << "Philosopher " << x << " finishes eating." << endl;
////    ReleaseMutex(mutex);
////}
//
//void PhilosopherThread(int x) {
//    WaitForSingleObject(mutex, INFINITE);   // ��ѧ��֮�以��Ͳͣ�һ��ֻ��һ����ѧ�ҾͲ�
//    cout << "Philosopher " << x << " sends the require for chopsticks " << x << " and " << (x + 1) % N << endl;
//    // ������ȡ�������ߵĿ���
//    WaitForSingleObject(chopsticks[x], INFINITE);
//    WaitForSingleObject(chopsticks[(x + 1) % 5], INFINITE);
//    cout << "Philosopher " << x << " is eating." << endl;
//    sleep(3);
//    // ��ѧ�ҾͲ���ϣ��ͷ����ߵĿ���
//    ReleaseSemaphore(chopsticks[x], 1, nullptr);
//    ReleaseSemaphore(chopsticks[(x + 1) % 5], 1, nullptr);
//    cout << "Philosopher " << x << " finishes eating." << endl;
//    ReleaseMutex(mutex);
//}
//
//int main() {
//    DWORD threadID;
//    HANDLE hThreads[N];
//    // �����ź�����ʼ��
//    string SEED = "chopsticks_";
//    int len = SEED.size();
//    for (int i = 0; i < 5; i++) {
//        SEED[len - 1] = '0' + i;
//        chopsticks[i] = CreateSemaphore(nullptr, 1, 1, SEED.c_str());
//    }
//
//    for (int i = 0; i < N; i++) {
//        hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) PhilosopherThread,
//                                   (LPVOID) (i + 1), 0, &threadID);
//    }
//    WaitForMultipleObjects(N, hThreads, true, -1);
//    cout << "All philosophers have finished eating." << endl;
//    return 0;
//}
