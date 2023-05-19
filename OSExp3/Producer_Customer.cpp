////
//// Created by HP on 2023/4/29.
////
//
//#include <iostream>
//#include <windows.h>
//#include "utils.h"
//
//using namespace std;
//extern ThreadInfo threadInfo[];
//extern int nThreads;
//
//const int MAXN = 20;    // 缓冲区中最多保留的产品数量
//HANDLE full = CreateSemaphore(nullptr, 0, MAXN, "buffer_full");     // 表示缓冲区是否填满的信号量
//HANDLE empty = CreateSemaphore(nullptr, MAXN, MAXN, "buffer_empty");// 表示缓冲区是否为空的信号量
//HANDLE mutex = CreateMutex(nullptr, false, "mutex");    // 访问缓冲区的互斥变量
//CRITICAL_SECTION PC_MUTEX;      // 临界资源
//int buffer[MAXN];       // 缓冲区
//int in = 0, out = 0;    // 生产者和消费者在访问缓冲区时使用的索引
//int productID = 1;      // 生产产品的id
//
//void ProducerThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//
//    cout << "Producer Thread " << thread_info->tid << " sends the produce require." << endl;
//    WaitForSingleObject(empty, INFINITE); // 等待缓冲区为空才能进行生产
//    WaitForSingleObject(mutex, INFINITE); // 等待其他进程访问完缓冲区
//
//    EnterCriticalSection(&PC_MUTEX); // 进入临界区
//    cout << "Producer Thread " << thread_info->tid << " begins to produce." << endl;
//    sleep(thread_info->duration);
//    buffer[in % MAXN] = productID;  // 生产者生产一件产品
//    cout << "Producer Thread " << thread_info->tid << " produced product " << productID << "." << endl;
//    productID++;
//    in = (in + 1) % MAXN;   // 调整索引往后指一位
//    LeaveCriticalSection(&PC_MUTEX); // 离开临界区
//
//    ReleaseMutex(mutex);    // 释放互斥量mutex
//    ReleaseSemaphore(full, 1, nullptr); //full := full + 1表示新增一件产品
//}
//
//void CustomerThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//
//    cout << "Customer Thread " << thread_info->tid << " sends the consume require." << endl;
//    WaitForSingleObject(full, INFINITE); // 等待缓冲区有产品才能消费
//    WaitForSingleObject(mutex, INFINITE);// 等待其他线程访问完缓冲区
//
//    EnterCriticalSection(&PC_MUTEX); // 进入临界区
//    cout << "Customer Thread " << thread_info->tid << " begins to consume product." << endl;
//    sleep(thread_info->duration);
//    int getProd = buffer[out % MAXN];   // 消费者购买一件产品
//    cout << "Customer Thread " << thread_info->tid << " consumed product " << getProd << "." << endl;
//    out = (out + 1) % MAXN;
//    LeaveCriticalSection(&PC_MUTEX);    // 离开临界区
//
//    ReleaseMutex(mutex);    // 释放互斥量mutex
//    ReleaseSemaphore(empty, 1, nullptr); // empty := empty - 1表示购买一件产品
//}
//
//int main() {
//    ReadThreadInfo("./PCProblem.txt");  // 读取线程信息
//    InitializeCriticalSection(&PC_MUTEX);   // 初始化临界资源
//    DWORD threadID; // 定义线程ID
//    HANDLE hThreads[nThreads]; // 定义一个数组保存所有线程的句柄
//    for (int i = 0; i < nThreads; i++) {
//        // 根据线程的不同类型创建线程，不同类型的线程调用不同的函数
//        if (toupper(threadInfo[i].type) == 'P') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) ProducerThread,
//                                       &threadInfo[i], 0, &threadID);
//        } else if (toupper(threadInfo[i].type) == 'C') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) CustomerThread,
//                                       &threadInfo[i], 0, &threadID);
//        }
//    }
//    // 等待所有线程执行完毕
//    WaitForMultipleObjects(nThreads, hThreads, true, -1);
//    cout << "All producers and customers have finished operating" << endl;
//    return 0;
//}