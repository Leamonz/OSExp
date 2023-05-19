//
// Created by HP on 2023/4/14.
//

#ifndef OSEXP2_JOB_H
#define OSEXP2_JOB_H

extern int CURRENT_TIME;

class Job {
private:
    int jid{};             //��ҵ��
    int reach_time{};         //��ҵ�ִ�ʱ��
    int need_time{};          //��ҵ��ִ��ʱ��
    int priority{};            //��ҵ����Ȩ
    float response_ratio{};   //��Ӧ��
    int start_time{};        //��ҵ��ʼʱ��
    int wait_time{};          //�ȴ�ʱ��
    int tr_time{};            //��תʱ��
    double wtr_time{};        //��Ȩ��תʱ��
    int run_time{};           //��ҵ�ۼ���ִ��ʱ��
    bool visited{};            //��ҵ�Ƿ񱻷��ʹ�
    bool reached{};            //��ҵ�Ƿ��ѵִ�

public:
    Job() = default;

    Job(int id, int r_time, int n_time, int p);// ���캯��
    // ����Set�������������ö��������
    void SetStartTime(int t) { start_time = t; }

    void SetVisited(bool is_visited) { visited = is_visited; }

    void SetReached(bool is_reached) { reached = is_reached; }
    // ����Calc���������ڼ���ָ�꣺��תʱ�䣬��Ȩ��תʱ�䣬�ȴ�ʱ�䣬��Ӧ��
    void CalcTurnaroundTime(int cur_time) { tr_time = cur_time - reach_time; }

    void CalcWeightedTurnaroundTime() { wtr_time = 1.0 * tr_time / (need_time); }

    void CalcWaitTime() { wait_time = tr_time - need_time; }

    void CalcResponseRatio(int cur_time) {
        wait_time = cur_time - reach_time;
        response_ratio = 1.0 + 1.0 * wait_time / need_time;
    }
    // ����Get���������ڻ�ȡ���������
    float GetResponseRatio() const { return response_ratio; }

    int GetPriority() const { return priority; }

    int GetID() const { return jid; }

    int GetReachTime() const { return reach_time; }

    int GetWaitTime() const { return wait_time; }

    int GetTRTime() const { return tr_time; }

    double GetWTRTime() const { return wtr_time; }
    // ����ִ����Ϻ��ӡ����ִ����Ϣ
    void ShowInfo() const;
    // �������к���������һ������ֵ��ʾ�Ƿ�ִ�����
    bool Run(int Time = 0);
};


#endif //OSEXP2_JOB_H
