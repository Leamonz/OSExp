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

void read_Jobdata(const char *path);                            //读取数据文件；
bool AddJobsToBackUp(std::vector<Job> &Jobs,
                     int &count, int cur_time);                 //根据当前时间查看是否有已到达的作业，将到达队列都放入后备队列
void initialize_jobs();                                         //初始化所有作业信息;
void CalcRRInBackUpQ();                                         //计算后备队列中作业的响应比

void HRRFScheduleJob(std::vector<Job> Jobs);                    //高响应比优先算法
void HPFScheduleJob(std::vector<Job> Jobs);                     //优先权高者优先算法
void RRScheduleJob(std::vector<Job> Jobs, int TIME_PIECE);      //时间片轮转算法

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
