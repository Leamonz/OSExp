//
// Created by HP on 2023/4/14.
//

#include "Job.h"
#include "utils.h"

Job::Job(int id, int r_time, int n_time, int p) {
    jid = id;
    reach_time = r_time;
    need_time = n_time;
    priority = p;
}

void Job::ShowInfo() const {
    std::cout << "执行完的作业是：" << jid << "号作业，等待时间为 "
              << wait_time << " 周转时间为 " << tr_time << " 带权周转时间为 "
              << std::fixed << std::setprecision(2) << wtr_time << std::endl;
}

bool Job::Run(int Time) {
    if (Time == 0) {
        // 没有时间片，作业执行需要的时间
        for (int i = 0; i < need_time; i++) {
            run_time++;
            CURRENT_TIME++;
        }
        CalcTurnaroundTime(CURRENT_TIME);
        CalcWeightedTurnaroundTime();
        CalcWaitTime();
        ShowInfo();
        return true;
    } else {
        // 给定时间片，执行完时间片
        for (int i = 0; i < Time; i++) {
            run_time++;
            CURRENT_TIME++;
            // 如果提前完成，就提前结束时间片
            if (run_time == need_time) {
                std::cout << jid << " 号作业执行了 " << i + 1 << std::endl;
                CalcTurnaroundTime(CURRENT_TIME);
                CalcWeightedTurnaroundTime();
                CalcWaitTime();
                ShowInfo();
                return true;
            }
        }
        std::cout << jid << " 号作业执行了 " << Time << std::endl;
    }
    return false;
}