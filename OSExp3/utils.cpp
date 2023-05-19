//
// Created by HP on 2023/4/29.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include "utils.h"

using namespace std;
ThreadInfo threadInfo[10];
int nThreads = 0;

void ReadThreadInfo(const char *path) {
    ifstream inFile;
    inFile.open(path);
    if (inFile.fail()) {
        cout << "Failed to open file " << path << endl;
        return;
    }
    cout << "ID " << " 类型 " << " 延迟时间 " << " 持续时间 " << endl;
    inFile >> threadInfo[nThreads].tid >> threadInfo[nThreads].type
           >> threadInfo[nThreads].delay >> threadInfo[nThreads].duration;
    cout << setiosflags(ios::left) << setw(4) << threadInfo[nThreads].tid << setw(4) << threadInfo[nThreads].type
         << setw(4) << threadInfo[nThreads].delay << setw(4) << threadInfo[nThreads].duration << endl;
    nThreads++;
    while (!inFile.eof()) {
        inFile >> threadInfo[nThreads].tid >> threadInfo[nThreads].type
               >> threadInfo[nThreads].delay >> threadInfo[nThreads].duration;
        cout << setiosflags(ios::left) << setw(4) << threadInfo[nThreads].tid << setw(4) << threadInfo[nThreads].type
             << setw(4) << threadInfo[nThreads].delay << setw(4) << threadInfo[nThreads].duration << endl;
        nThreads++;
    }
}
