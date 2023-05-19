#include <iostream>
#include "utils.h"

using namespace std;
extern vector<Job> AllJobs;

void menu() {
    cout << "==========" << endl;
    cout << "��ѡ��ʹ�õĵ����㷨" << endl;
    cout << "(1) ����Ӧ�������㷨" << endl;
    cout << "(2) ����Ȩ���������㷨" << endl;
    cout << "(3) ʱ��Ƭ��ת�㷨" << endl;
    cout << "(4) �˳�" << endl;
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
                cout << "������ʱ��Ƭ��";
                cin >> TIME_PIECE;
                RRScheduleJob(AllJobs, TIME_PIECE);
                break;
            case 4:
                cout << "�˳���" << endl;
                break;
            default:
                cout << "��ѡ����ȷ��ѡ��" << endl;
                break;
        }
    } while (select != 4);
    return 0;
}
