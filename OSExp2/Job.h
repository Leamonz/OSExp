//
// Created by HP on 2023/4/14.
//

#ifndef OSEXP2_JOB_H
#define OSEXP2_JOB_H

extern int CURRENT_TIME;

class Job {
private:
    int jid{};             //作业号
    int reach_time{};         //作业抵达时间
    int need_time{};          //作业的执行时间
    int priority{};            //作业优先权
    float response_ratio{};   //响应比
    int start_time{};        //作业开始时间
    int wait_time{};          //等待时间
    int tr_time{};            //周转时间
    double wtr_time{};        //带权周转时间
    int run_time{};           //作业累计已执行时间
    bool visited{};            //作业是否被访问过
    bool reached{};            //作业是否已抵达

public:
    Job() = default;

    Job(int id, int r_time, int n_time, int p);// 构造函数
    // 以下Set函数均用于设置对象的属性
    void SetStartTime(int t) { start_time = t; }

    void SetVisited(bool is_visited) { visited = is_visited; }

    void SetReached(bool is_reached) { reached = is_reached; }
    // 以下Calc函数均用于计算指标：周转时间，带权周转时间，等待时间，响应比
    void CalcTurnaroundTime(int cur_time) { tr_time = cur_time - reach_time; }

    void CalcWeightedTurnaroundTime() { wtr_time = 1.0 * tr_time / (need_time); }

    void CalcWaitTime() { wait_time = tr_time - need_time; }

    void CalcResponseRatio(int cur_time) {
        wait_time = cur_time - reach_time;
        response_ratio = 1.0 + 1.0 * wait_time / need_time;
    }
    // 以下Get函数均用于获取对象的属性
    float GetResponseRatio() const { return response_ratio; }

    int GetPriority() const { return priority; }

    int GetID() const { return jid; }

    int GetReachTime() const { return reach_time; }

    int GetWaitTime() const { return wait_time; }

    int GetTRTime() const { return tr_time; }

    double GetWTRTime() const { return wtr_time; }
    // 进程执行完毕后打印进程执行信息
    void ShowInfo() const;
    // 进程运行函数，返回一个布尔值表示是否执行完毕
    bool Run(int Time = 0);
};


#endif //OSEXP2_JOB_H
