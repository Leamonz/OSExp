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
    WaitForSingleObject(on_bridge, INFINITE);   // 确认桥中间足够容纳至少1个人
    WaitForSingleObject(nmutex, INFINITE);      // 确认桥北面没有其他人
    cout << "North Pedestrian Thread " << thread_info->tid << " is crossing the north bridge." << endl;
    ReleaseMutex(nmutex);   // 行人通过桥的北面

    cout << "North Pedestrian Thread " << thread_info->tid << " is on the bridge." << endl;
    sleep(thread_info->duration);   // 行人处于桥的中间

    WaitForSingleObject(smutex, INFINITE);      // 确认桥南面没有其他人
    cout << "North Pedestrian Thread " << thread_info->tid << " is crossing the south bridge." << endl;
    ReleaseMutex(smutex);   // 行人通过桥的南面
    cout << "North Pedestrian Thread " << thread_info->tid << " crossed the bridge." << endl;
    ReleaseSemaphore(on_bridge, 1, nullptr);    // 行人过桥，桥可容纳人数增加1
}

void SouthThread(ThreadInfo *thread_info) {
    sleep(thread_info->delay);
    // 南行人过桥线程与北行人类似，只不过交换了过桥的南北面的次序
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
