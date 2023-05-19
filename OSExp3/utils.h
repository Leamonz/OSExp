//
// Created by HP on 2023/4/29.
//

#ifndef OSEXP3_UTILS_H
#define OSEXP3_UTILS_H
#define sleep(_n) Sleep((_n)*1000)

typedef struct {
    int tid;
    char type;
    double delay;
    double duration;
} ThreadInfo;

void ReadThreadInfo(const char *path);

#endif //OSEXP3_UTILS_H
