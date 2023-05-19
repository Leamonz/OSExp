//
// Created by HP on 2023/4/13.
//

#ifndef OSEXP2_UTILS_H
#define OSEXP2_UTILS_H

#include "Job.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

void read_Jobdata(const char *path);                            //��ȡ�����ļ���
bool AddJobsToBackUp(std::vector<Job> &Jobs,
                     int &count, int cur_time);                 //���ݵ�ǰʱ��鿴�Ƿ����ѵ������ҵ����������ж�����󱸶���
void initialize_jobs();                                         //��ʼ��������ҵ��Ϣ;
void CalcRRInBackUpQ();                                         //����󱸶�������ҵ����Ӧ��

void HRRFScheduleJob(std::vector<Job> Jobs);                    //����Ӧ�������㷨
void HPFScheduleJob(std::vector<Job> Jobs);                     //����Ȩ���������㷨
void RRScheduleJob(std::vector<Job> Jobs, int TIME_PIECE);      //ʱ��Ƭ��ת�㷨

class CompareViaReachTime {
public:
    bool operator()(Job &j1, Job &j2);
};

class CompareViaResponseRatio {
public:
    bool operator()(Job &j1, Job &j2);
};

class CompareViaPriority {
public:
    bool operator()(Job &j1, Job &j2);
};

#endif //OSEXP2_UTILS_H
