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
//const int N = 5;    // 哲学家数量
//HANDLE mutex = CreateMutex(nullptr, false, "mutex");    // 哲学家互斥就餐，避免死锁
//HANDLE chopsticks[5];   // 信号量，表示五支筷子
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
//    WaitForSingleObject(mutex, INFINITE);   // 哲学家之间互斥就餐，一次只有一名哲学家就餐
//    cout << "Philosopher " << x << " sends the require for chopsticks " << x << " and " << (x + 1) % N << endl;
//    // 申请拿取左右两边的筷子
//    WaitForSingleObject(chopsticks[x], INFINITE);
//    WaitForSingleObject(chopsticks[(x + 1) % 5], INFINITE);
//    cout << "Philosopher " << x << " is eating." << endl;
//    sleep(3);
//    // 哲学家就餐完毕，释放两边的筷子
//    ReleaseSemaphore(chopsticks[x], 1, nullptr);
//    ReleaseSemaphore(chopsticks[(x + 1) % 5], 1, nullptr);
//    cout << "Philosopher " << x << " finishes eating." << endl;
//    ReleaseMutex(mutex);
//}
//
//int main() {
//    DWORD threadID;
//    HANDLE hThreads[N];
//    // 筷子信号量初始化
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
