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
//    WaitForSingleObject(queue, INFINITE);   // 确认队列中没有其他线程
//    cout << "Reader thread " << thread_info->tid << " sends the reading require." << endl;
//    WaitForSingleObject(rmutex, INFINITE);  // 读者之间互斥访问文件
//    if (readerCount == 0) {
//        WaitForSingleObject(fmutex, INFINITE);  // 如果此前没有读者，还要等待写者释放出文件的访问权
//    }
//    readerCount++;  // 记录读者数量
//    ReleaseMutex(rmutex);
//    ReleaseMutex(queue);
//
//    EnterCriticalSection(&RW_MUTEX);
//    cout << "Reader thread " << thread_info->tid << " begins to read file." << endl;
//    sleep(thread_info->duration);   // 读者开始读文件
//    cout << "Reader thread " << thread_info->tid << " finishes reading file." << endl;
//    LeaveCriticalSection(&RW_MUTEX);
//
//    WaitForSingleObject(rmutex, INFINITE);
//    readerCount--;  // 读者读完文件，更新读者数量
//    if (readerCount == 0) {
//        ReleaseMutex(fmutex);   // 当读者都读完文件了，要释放文件的访问权
//    }
//    ReleaseMutex(rmutex);
//}
//
//void WriterThread(ThreadInfo *thread_info) {
//    sleep(thread_info->delay);
//    cout << "Writer thread " << thread_info->tid << " sends the writing require." << endl;
//    WaitForSingleObject(wmutex, INFINITE);  // 写者之间互斥访问文件
//    if (writerCount == 0) {
//        WaitForSingleObject(queue, INFINITE);   // 如果此前没有写者，则要等待队列中读者线程结束，然后占据队列
//    }
//    writerCount++;  // 记录写者数量
//    ReleaseMutex(wmutex);
//
//    WaitForSingleObject(fmutex, INFINITE);  // 不同写者互斥写文件，不然数据可能产生冲突
//    EnterCriticalSection(&RW_MUTEX);
//    cout << "Writer thread " << thread_info->tid << " begins to write to the file." << endl;
//    sleep(thread_info->duration);   // 写者开始写文件
//    cout << "Writer thread " << thread_info->tid << " finishes writing to the file." << endl;
//    LeaveCriticalSection(&RW_MUTEX);
//    ReleaseMutex(fmutex);
//
//    WaitForSingleObject(wmutex, INFINITE);
//    writerCount--;  // 写者写完文件，更新写者数量
//    if (writerCount == 0) {
//        ReleaseMutex(queue);    // 当所有写者写完文件，释放队列
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
