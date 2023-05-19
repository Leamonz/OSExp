//
// Created by HP on 2023/5/4.
//

#include <iostream>
#include <windows.h>
#include "utils.h"

using namespace std;
extern ThreadInfo threadInfo[10];
extern int nThreads;

HANDLE nmutex = CreateMutex(nullptr, false, "north bridge");
HANDLE smutex = CreateMutex(nullptr, false, "south bridge");
HANDLE on_bridge = CreateSemaphore(nullptr, 2, 2, "persons on bridge");

void NorthThread(ThreadInfo *thread_info) {
    sleep(thread_info->delay);

    cout << "North Pedestrian Thread " << thread_info->tid << " sends the require to cross the bridge." << endl;
    WaitForSingleObject(on_bridge, INFINITE);   // ȷ�����м��㹻��������1����
    WaitForSingleObject(nmutex, INFINITE);      // ȷ���ű���û��������
    cout << "North Pedestrian Thread " << thread_info->tid << " is crossing the north bridge." << endl;
    ReleaseMutex(nmutex);   // ����ͨ���ŵı���

    cout << "North Pedestrian Thread " << thread_info->tid << " is on the bridge." << endl;
    sleep(thread_info->duration);   // ���˴����ŵ��м�

    WaitForSingleObject(smutex, INFINITE);      // ȷ��������û��������
    cout << "North Pedestrian Thread " << thread_info->tid << " is crossing the south bridge." << endl;
    ReleaseMutex(smutex);   // ����ͨ���ŵ�����
    cout << "North Pedestrian Thread " << thread_info->tid << " crossed the bridge." << endl;
    ReleaseSemaphore(on_bridge, 1, nullptr);    // ���˹��ţ��ſ�������������1
}

void SouthThread(ThreadInfo *thread_info) {
    sleep(thread_info->delay);
    // �����˹����߳��뱱�������ƣ�ֻ���������˹��ŵ��ϱ���Ĵ���
    cout << "South Pedestrian Thread " << thread_info->tid << " sends the require to cross the bridge." << endl;
    WaitForSingleObject(on_bridge, INFINITE);
    WaitForSingleObject(smutex, INFINITE);
    cout << "South Pedestrian Thread " << thread_info->tid << " is crossing the south bridge." << endl;
    ReleaseMutex(smutex);

    cout << "South Pedestrian Thread " << thread_info->tid << " is on the bridge." << endl;
    sleep(thread_info->duration);

    WaitForSingleObject(nmutex, INFINITE);
    cout << "South Pedestrian Thread " << thread_info->tid << " is crossing the north bridge." << endl;
    ReleaseMutex(nmutex);
    cout << "South Pedestrian Thread " << thread_info->tid << " crossed the bridge." << endl;
    ReleaseSemaphore(on_bridge, 1, nullptr);
}

int main() {
    ReadThreadInfo("Bridge.txt");
    DWORD threadID;
    HANDLE hThreads[nThreads];

    for (int i = 0; i < nThreads; i++) {
        if (toupper(threadInfo[i].type) == 'N') {
            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) NorthThread,
                                       &threadInfo[i], 0, &threadID);
        } else if (toupper(threadInfo[i].type) == 'S') {
            hThreads[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) SouthThread,
                                       &threadInfo[i], 0, &threadID);
        }
    }

    WaitForMultipleObjects(nThreads, hThreads, true, -1);
    cout << "All pedestrians have passed the bridge." << endl;
    return 0;
}
