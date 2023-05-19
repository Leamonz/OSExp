//#include <iostream>
//#include <windows.h>
//#include "utils.h"
//
//using namespace std;
//
//extern ThreadInfo threadInfo[];
//extern int nThreads;
//
//HANDLE rmutex = CreateMutex(nullptr, false, "reader_mutex");
//HANDLE wmutex = CreateMutex(nullptr, false, "writer_mutex");
//HANDLE fmutex = CreateMutex(nullptr, false, "file_mutex");
//HANDLE queue = CreateMutex(nullptr, false, "queue");
//int readerCount = 0;
//int writerCount = 0;
//CRITICAL_SECTION RW_MUTEX;
//
//
//void ReaderThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//    WaitForSingleObject(queue, INFINITE);   // ȷ�϶�����û�������߳�
//    cout << "Reader thread " << thread_info->tid << " sends the reading require." << endl;
//    WaitForSingleObject(rmutex, INFINITE);  // ����֮�以������ļ�
//    if (readerCount == 0) {
//        WaitForSingleObject(fmutex, INFINITE);  // �����ǰû�ж��ߣ���Ҫ�ȴ�д���ͷų��ļ��ķ���Ȩ
//    }
//    readerCount++;  // ��¼��������
//    ReleaseMutex(rmutex);
//    ReleaseMutex(queue);
//
//    EnterCriticalSection(&RW_MUTEX);
//    cout << "Reader thread " << thread_info->tid << " begins to read file." << endl;
//    sleep(thread_info->duration);   // ���߿�ʼ���ļ�
//    cout << "Reader thread " << thread_info->tid << " finishes reading file." << endl;
//    LeaveCriticalSection(&RW_MUTEX);
//
//    WaitForSingleObject(rmutex, INFINITE);
//    readerCount--;  // ���߶����ļ������¶�������
//    if (readerCount == 0) {
//        ReleaseMutex(fmutex);   // �����߶������ļ��ˣ�Ҫ�ͷ��ļ��ķ���Ȩ
//    }
//    ReleaseMutex(rmutex);
//}
//
//void WriterThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//    cout << "Writer thread " << thread_info->tid << " sends the writing require." << endl;
//    WaitForSingleObject(wmutex, INFINITE);  // д��֮�以������ļ�
//    if (writerCount == 0) {
//        WaitForSingleObject(queue, INFINITE);   // �����ǰû��д�ߣ���Ҫ�ȴ������ж����߳̽�����Ȼ��ռ�ݶ���
//    }
//    writerCount++;  // ��¼д������
//    ReleaseMutex(wmutex);
//
//    WaitForSingleObject(fmutex, INFINITE);  // ��ͬд�߻���д�ļ�����Ȼ���ݿ��ܲ�����ͻ
//    EnterCriticalSection(&RW_MUTEX);
//    cout << "Writer thread " << thread_info->tid << " begins to write to the file." << endl;
//    sleep(thread_info->duration);   // д�߿�ʼд�ļ�
//    cout << "Writer thread " << thread_info->tid << " finishes writing to the file." << endl;
//    LeaveCriticalSection(&RW_MUTEX);
//    ReleaseMutex(fmutex);
//
//    WaitForSingleObject(wmutex, INFINITE);
//    writerCount--;  // д��д���ļ�������д������
//    if (writerCount == 0) {
//        ReleaseMutex(queue);    // ������д��д���ļ����ͷŶ���
//    }
//    ReleaseMutex(wmutex);
//}
//
//int main() {
//    ReadThreadInfo("./RWProblem.txt");
//    InitializeCriticalSection(&RW_MUTEX);
//
//    HANDLE hThreads[nThreads];
//    DWORD threadID;
//    for (int i = 0; i < nThreads; i++) {
//        if (toupper(threadInfo[i].type) == 'R') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) ReaderThread,
//                                       &threadInfo[i], 0, &threadID);
//        } else if (toupper(threadInfo[i].type) == 'W') {
//            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) WriterThread,
//                                       &threadInfo[i], 0, &threadID);
//        }
//    }
//    WaitForMultipleObjects(nThreads, hThreads, true, -1);
//    cout << "All readers and writers have finished operating." << endl;
//    return 0;
//}
