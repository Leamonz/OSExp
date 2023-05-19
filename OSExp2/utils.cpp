//
// Created by HP on 2023/4/13.
//
#include "utils.h"

std::vector<Job> AllJobs;       // 保存读取的作业信息
std::vector<Job> BackUpQ;       // 后备队列
int CURRENT_TIME = 0;           // 记录当前运行时间
int N_Jobs = 0;                 // 记录总作业数

bool CompareViaReachTime::operator()(Job &j1, Job &j2) {
    // 根据到达时间先后排序
    return j1.GetReachTime() < j2.GetReachTime();
}

bool CompareViaResponseRatio::operator()(Job &j1, Job &j2) {
    // 响应比越大越先执行
    return j1.GetResponseRatio() > j2.GetResponseRatio();
}

bool CompareViaPriority::operator()(Job &j1, Job &j2) {
    // 优先权数字越小，优先级越高
    return j1.GetPriority() < j2.GetPriority();
}

void Print(int id, int r_time, int n_time, int p) {
    std::cout << std::setw(6) << std::setiosflags(std::ios::left) << id << std::setw(6)
              << std::setiosflags(std::ios::left) << r_time << std::setw(6) << std::setiosflags(std::ios::left)
              << n_time << std::setw(6) << std::setiosflags(std::ios::left) << p << std::endl;
}

void read_Jobdata(const char *path) {
    std::ifstream inFile;
    inFile.open(path);
    if (inFile.fail()) {
        std::cout << "文件打开失败" << std::endl;
    }
    std::string temp;
    std::getline(inFile, temp);
    std::cout << temp << std::endl;
    int id, r_time, n_time, p;
    inFile >> id >> r_time >> n_time >> p;
    AllJobs.emplace_back(id, r_time, n_time, p);
    N_Jobs++;
    Print(id, r_time, n_time, p);
    while (!inFile.eof()) {
        inFile >> id >> r_time >> n_time >> p;
        AllJobs.emplace_back(id, r_time, n_time, p);
        N_Jobs++;
        Print(id, r_time, n_time, p);
    }
}

bool AddJobsToBackUp(std::vector<Job> &Jobs, int &count, int cur_time) {
    bool flag = false;
    for (int i = count; i < Jobs.size(); i++) {
        // 如果当前运行时间大于等于进程到达时间，则将该进程调入后备队列
        if (cur_time >= Jobs[i].GetReachTime()) {
            BackUpQ.push_back(Jobs[i]);
            Jobs[i].SetReached(true);
            count++;
            flag = true;
        }
    }
    // 返回一个bool值表示是否有进程调入后备队列
    return flag;
}

void CalcRRInBackUpQ() {
    for (auto &job: BackUpQ) {
        job.CalcResponseRatio(CURRENT_TIME);
    }
}

void HRRFScheduleJob(std::vector<Job> Jobs) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "高响应比优先服务：" << std::endl;
    std::sort(Jobs.begin(), Jobs.end(), CompareViaReachTime());
    int count = 0, completed = 0;
    Job runningJob;
    while (true) {
        while (!BackUpQ.empty()) {
            // 计算后备队列中所有作业的响应比
            CalcRRInBackUpQ();
            // 将后备队列的作业按照响应比由大到小进行排序
            sort(BackUpQ.begin(), BackUpQ.end(), CompareViaResponseRatio());
            // 取出响应比最高的作业
            runningJob = *(BackUpQ.begin());
            BackUpQ.erase(BackUpQ.begin());
            runningJob.Run();
            runningJob.SetVisited(true);
            // 计算指标：平均等待时间、平均周转时间、平均带权周转时间
            AvgWaitTime += runningJob.GetWaitTime();
            AvgTurnAroundTime += runningJob.GetTRTime();
            AvgWeightedTurnAroundTime += runningJob.GetWTRTime();
            completed++;
        }
        if (AddJobsToBackUp(Jobs, count, CURRENT_TIME)) continue;
        CURRENT_TIME++;
        if (completed == N_Jobs) break;
    }
    AvgWaitTime /= N_Jobs;
    AvgTurnAroundTime /= N_Jobs;
    AvgWeightedTurnAroundTime /= N_Jobs;
    std::cout << "平均等待时间：" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "平均周转时间：" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "平均带权周转时间：" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // 重启处理机
    CURRENT_TIME = 0;
}

void HPFScheduleJob(std::vector<Job> Jobs) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "优先权高者优先服务(非抢占式)：" << std::endl;
    std::sort(Jobs.begin(), Jobs.end(), CompareViaReachTime());
    int count = 0, completed = 0;
    Job runningJob;
    while (true) {
        while (!BackUpQ.empty()) {
            std::sort(BackUpQ.begin(), BackUpQ.end(), CompareViaPriority());
            runningJob = *(BackUpQ.begin());
            BackUpQ.erase(BackUpQ.begin());
            runningJob.Run();
            runningJob.SetVisited(true);
            // 计算指标：平均等待时间、平均周转时间、平均带权周转时间
            AvgWaitTime += runningJob.GetWaitTime();
            AvgTurnAroundTime += runningJob.GetTRTime();
            AvgWeightedTurnAroundTime += runningJob.GetWTRTime();
            completed++;
        }
        if (AddJobsToBackUp(Jobs, count, CURRENT_TIME)) continue;
        CURRENT_TIME++;
        if (completed == N_Jobs) break;
    }
    AvgWaitTime /= N_Jobs;
    AvgTurnAroundTime /= N_Jobs;
    AvgWeightedTurnAroundTime /= N_Jobs;
    std::cout << "平均等待时间：" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "平均周转时间：" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "平均带权周转时间：" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // 重启处理机
    CURRENT_TIME = 0;
}

void RRScheduleJob(std::vector<Job> Jobs, int TIME_PIECE) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "时间片轮转服务：" << std::endl;
    std::cout << "时间片为：" << TIME_PIECE << std::endl;
    std::sort(Jobs.begin(), Jobs.end(), CompareViaReachTime());
    int count = 0, completed = 0;
    Job runningJob;
    while (true) {
        while (!BackUpQ.empty()) {
            bool flag = false;
            runningJob = *(BackUpQ.begin());
            BackUpQ.erase(BackUpQ.begin());
            flag = runningJob.Run(TIME_PIECE);
            // 判断当前进程是否执行完毕，如果每执行完就放入后备队列等待下一次调用
            if (flag) {
                runningJob.SetVisited(true);
                // 计算指标：平均等待时间、平均周转时间、平均带权周转时间
                AvgWaitTime += runningJob.GetWaitTime();
                AvgTurnAroundTime += runningJob.GetTRTime();
                AvgWeightedTurnAroundTime += runningJob.GetWTRTime();
                completed++;
            } else {
                AddJobsToBackUp(Jobs, count, CURRENT_TIME);
                BackUpQ.push_back(runningJob);
            }
        }
        if (AddJobsToBackUp(Jobs, count, CURRENT_TIME)) continue;
        CURRENT_TIME++;
        if (completed == N_Jobs) break;
    }
    AvgWaitTime /= N_Jobs;
    AvgTurnAroundTime /= N_Jobs;
    AvgWeightedTurnAroundTime /= N_Jobs;
    std::cout << "平均等待时间：" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "平均周转时间：" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "平均带权周转时间：" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // 重启处理机
    CURRENT_TIME = 0;
}