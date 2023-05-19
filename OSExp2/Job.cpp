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
    std::cout << "ִ�������ҵ�ǣ�" << jid << "����ҵ���ȴ�ʱ��Ϊ "
              << wait_time << " ��תʱ��Ϊ " << tr_time << " ��Ȩ��תʱ��Ϊ "
              << std::fixed << std::setprecision(2) << wtr_time << std::endl;
}

bool Job::Run(int Time) {
    if (Time == 0) {
        // û��ʱ��Ƭ����ҵִ����Ҫ��ʱ��
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
        // ����ʱ��Ƭ��ִ����ʱ��Ƭ
        for (int i = 0; i < Time; i++) {
            run_time++;
            CURRENT_TIME++;
            // �����ǰ��ɣ�����ǰ����ʱ��Ƭ
            if (run_time == need_time) {
                std::cout << jid << " ����ҵִ���� " << i + 1 << std::endl;
                CalcTurnaroundTime(CURRENT_TIME);
                CalcWeightedTurnaroundTime();
                CalcWaitTime();
                ShowInfo();
                return true;
            }
        }
        std::cout << jid << " ����ҵִ���� " << Time << std::endl;
    }
    return false;
}