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
//const int MAXN = 20;    // ����������ౣ���Ĳ�Ʒ����
//HANDLE full = CreateSemaphore(nullptr, 0, MAXN, "buffer_full");     // ��ʾ�������Ƿ��������ź���
//HANDLE empty = CreateSemaphore(nullptr, MAXN, MAXN, "buffer_empty");// ��ʾ�������Ƿ�Ϊ�յ��ź���
//HANDLE mutex = CreateMutex(nullptr, false, "mutex");    // ���ʻ������Ļ������
//CRITICAL_SECTION PC_MUTEX;      // �ٽ���Դ
//int buffer[MAXN];       // ������
//int in = 0, out = 0;    // �����ߺ��������ڷ��ʻ�����ʱʹ�õ�����
//int productID = 1;      // ������Ʒ��id
//
//void ProducerThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//
//    cout << "Producer Thread " << thread_info->tid << " sends the produce require." << endl;
//    WaitForSingleObject(empty, INFINITE); // �ȴ�������Ϊ�ղ��ܽ�������
//    WaitForSingleObject(mutex, INFINITE); // �ȴ��������̷����껺����
//
//    EnterCriticalSection(&PC_MUTEX); // �����ٽ���
//    cout << "Producer Thread " << thread_info->tid << " begins to produce." << endl;
//    sleep(thread_info->duration);
//    buffer[in % MAXN] = productID;  // ����������һ����Ʒ
//    cout << "Producer Thread " << thread_info->tid << " produced product " << productID << "." << endl;
//    productID++;
//    in = (in + 1) % MAXN;   // ������������ָһλ
//    LeaveCriticalSection(&PC_MUTEX); // �뿪�ٽ���
//
//    ReleaseMutex(mutex);    // �ͷŻ�����mutex
//    ReleaseSemaphore(full, 1, nullptr); //full := full + 1��ʾ����һ����Ʒ
//}
//
//void CustomerThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//
//    cout << "Customer Thread " << thread_info->tid << " sends the consume require." << endl;
//    WaitForSingleObject(full, INFINITE); // �ȴ��������в�Ʒ��������
//    WaitForSingleObject(mutex, INFINITE);// �ȴ������̷߳����껺����
//
//    EnterCriticalSection(&PC_MUTEX); // �����ٽ���
//    cout << "Customer Thread " << thread_info->tid << " begins to consume product." << endl;
//    sleep(thread_info->duration);
//    int getProd = buffer[out % MAXN];   // �����߹���һ����Ʒ
//    cout << "Customer Thread " << thread_info->tid << " consumed product " << getProd << "." << endl;
//    out = (out + 1) % MAXN;
//    LeaveCriticalSection(&PC_MUTEX);    // �뿪�ٽ���
//
//    ReleaseMutex(mutex);    // �ͷŻ�����mutex
//    ReleaseSemaphore(empty, 1, nullptr); // empty := empty - 1��ʾ����һ����Ʒ
//}
//
//int main() {
//    ReadThreadInfo("./PCProblem.txt");  // ��ȡ�߳���Ϣ
//    InitializeCriticalSection(&PC_MUTEX);   // ��ʼ���ٽ���Դ
//    DWORD threadID; // �����߳�ID
//    HANDLE hThreads[nThreads]; // ����һ�����鱣�������̵߳ľ��
//    for (int i = 0; i < nThreads; i++) {
//        // �����̵߳Ĳ�ͬ���ʹ����̣߳���ͬ���͵��̵߳��ò�ͬ�ĺ���
//        if (toupper(threadInfo[i].type) == 'P') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) ProducerThread,
//                                       &threadInfo[i], 0, &threadID);
//        } else if (toupper(threadInfo[i].type) == 'C') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) CustomerThread,
//                                       &threadInfo[i], 0, &threadID);
//        }
//    }
//    // �ȴ������߳�ִ�����
//    WaitForMultipleObjects(nThreads, hThreads, true, -1);
//    cout << "All producers and customers have finished operating" << endl;
//    return 0;
//}