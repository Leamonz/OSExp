#include <iostream>
#include "utils.h"

using namespace std;
extern vector<Job> AllJobs;

void menu() {
    cout << "==========" << endl;
    cout << "请选择使用的调度算法" << endl;
    cout << "(1) 高响应比优先算法" << endl;
    cout << "(2) 优先权高者优先算法" << endl;
    cout << "(3) 时间片轮转算法" << endl;
    cout << "(4) 退出" << endl;
    cout << "==========" << endl;
}

int main() {
    read_Jobdata("./jobs.txt");
    int select = 0, TIME_PIECE;
    do {
        menu();
        cin >> select;
        cin.get();
        switch (select) {
            case 1:
                HRRFScheduleJob(AllJobs);
                break;
            case 2:
                HPFScheduleJob(AllJobs);
                break;
            case 3:
                cout << "请输入时间片：";
                cin >> TIME_PIECE;
                RRScheduleJob(AllJobs, TIME_PIECE);
                break;
            case 4:
                cout << "退出！" << endl;
                break;
            default:
                cout << "请选择正确的选项" << endl;
                break;
        }
    } while (select != 4);
    return 0;
}
