//
// Created by HP on 2023/4/13.
//
#include "utils.h"

std::vector<Job> AllJobs;       // �����ȡ����ҵ��Ϣ
std::vector<Job> BackUpQ;       // �󱸶���
int CURRENT_TIME = 0;           // ��¼��ǰ����ʱ��
int N_Jobs = 0;                 // ��¼����ҵ��

bool CompareViaReachTime::operator()(Job &j1, Job &j2) {
    // ���ݵ���ʱ���Ⱥ�����
    return j1.GetReachTime() < j2.GetReachTime();
}

bool CompareViaResponseRatio::operator()(Job &j1, Job &j2) {
    // ��Ӧ��Խ��Խ��ִ��
    return j1.GetResponseRatio() > j2.GetResponseRatio();
}

bool CompareViaPriority::operator()(Job &j1, Job &j2) {
    // ����Ȩ����ԽС�����ȼ�Խ��
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
        std::cout << "�ļ���ʧ��" << std::endl;
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
        // �����ǰ����ʱ����ڵ��ڽ��̵���ʱ�䣬�򽫸ý��̵���󱸶���
        if (cur_time >= Jobs[i].GetReachTime()) {
            BackUpQ.push_back(Jobs[i]);
            Jobs[i].SetReached(true);
            count++;
            flag = true;
        }
    }
    // ����һ��boolֵ��ʾ�Ƿ��н��̵���󱸶���
    return flag;
}

void CalcRRInBackUpQ() {
    for (auto &job: BackUpQ) {
        job.CalcResponseRatio(CURRENT_TIME);
    }
}

void HRRFScheduleJob(std::vector<Job> Jobs) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "����Ӧ�����ȷ���" << std::endl;
    std::sort(Jobs.begin(), Jobs.end(), CompareViaReachTime());
    int count = 0, completed = 0;
    Job runningJob;
    while (true) {
        while (!BackUpQ.empty()) {
            // ����󱸶�����������ҵ����Ӧ��
            CalcRRInBackUpQ();
            // ���󱸶��е���ҵ������Ӧ���ɴ�С��������
            sort(BackUpQ.begin(), BackUpQ.end(), CompareViaResponseRatio());
            // ȡ����Ӧ����ߵ���ҵ
            runningJob = *(BackUpQ.begin());
            BackUpQ.erase(BackUpQ.begin());
            runningJob.Run();
            runningJob.SetVisited(true);
            // ����ָ�꣺ƽ���ȴ�ʱ�䡢ƽ����תʱ�䡢ƽ����Ȩ��תʱ��
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
    std::cout << "ƽ���ȴ�ʱ�䣺" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "ƽ����תʱ�䣺" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "ƽ����Ȩ��תʱ�䣺" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // ���������
    CURRENT_TIME = 0;
}

void HPFScheduleJob(std::vector<Job> Jobs) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "����Ȩ�������ȷ���(����ռʽ)��" << std::endl;
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
            // ����ָ�꣺ƽ���ȴ�ʱ�䡢ƽ����תʱ�䡢ƽ����Ȩ��תʱ��
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
    std::cout << "ƽ���ȴ�ʱ�䣺" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "ƽ����תʱ�䣺" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "ƽ����Ȩ��תʱ�䣺" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // ���������
    CURRENT_TIME = 0;
}

void RRScheduleJob(std::vector<Job> Jobs, int TIME_PIECE) {
    double AvgWaitTime = 0, AvgTurnAroundTime = 0, AvgWeightedTurnAroundTime = 0;
    std::cout << "ʱ��Ƭ��ת����" << std::endl;
    std::cout << "ʱ��ƬΪ��" << TIME_PIECE << std::endl;
    std::sort(Jobs.begin(), Jobs.end(), CompareViaReachTime());
    int count = 0, completed = 0;
    Job runningJob;
    while (true) {
        while (!BackUpQ.empty()) {
            bool flag = false;
            runningJob = *(BackUpQ.begin());
            BackUpQ.erase(BackUpQ.begin());
            flag = runningJob.Run(TIME_PIECE);
            // �жϵ�ǰ�����Ƿ�ִ����ϣ����ÿִ����ͷ���󱸶��еȴ���һ�ε���
            if (flag) {
                runningJob.SetVisited(true);
                // ����ָ�꣺ƽ���ȴ�ʱ�䡢ƽ����תʱ�䡢ƽ����Ȩ��תʱ��
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
    std::cout << "ƽ���ȴ�ʱ�䣺" << std::fixed << std::setprecision(2) << AvgWaitTime << std::endl;
    std::cout << "ƽ����תʱ�䣺" << std::fixed << std::setprecision(2) << AvgTurnAroundTime << std::endl;
    std::cout << "ƽ����Ȩ��תʱ�䣺" << std::fixed << std::setprecision(2) << AvgWeightedTurnAroundTime << std::endl;
    // ���������
    CURRENT_TIME = 0;
}