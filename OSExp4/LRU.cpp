////
//// Created by HP on 2023/5/14.
////
//
//#include <iostream>
//#include <iomanip>
//#include <vector>
//
//using namespace std;
//
//typedef struct {
//    int pageNo{0};
//    int visit{0};
//    int stay{0};
//} pageInfo;
//// �����е�ҳ������
//int pageNum = 0;
//vector<pageInfo> currentPages(3);
//// ����ҳ��Ĵ���
//vector<int> PAGES = {3, 4, 2, 6, 4,
//                     3, 7, 4, 3, 6,
//                     3, 4, 8, 4, 6};
//int HIT = 0;
//
//void LRU() {
//    for (int &p: PAGES) {
//        cout << "��ǰ����ҳ��: P" << p << endl;
//        int flag = 0;
//        if (pageNum == 0) {
//            currentPages[pageNum].pageNo = p;
//            currentPages[pageNum].visit = 1;
//            currentPages[pageNum].stay = 0;
//            pageNum++;
//        } else {
//            for (int i = 0; i < pageNum; i++) {
//                if (currentPages[i].pageNo == p) {
//                    currentPages[i].visit++;
//                    currentPages[i].stay = 0;
//                    flag = 1; // �������ҵ���ҳ�棬���ʴ�����1
//                    HIT++;
//                    cout << "���У�" << endl;
//                    break;
//                }
//            }
//            // ��ǰ������û���ҵ���ҳ��
//            if (!flag) {
//                if (pageNum < 3) {
//                    currentPages[pageNum].pageNo = p;
//                    currentPages[pageNum].visit = 1;
//                    currentPages[pageNum].stay = 0;
//                    pageNum++;
//                } else {
//                    // �ҵ�������ٷ��ʵ�ҳ�棬�����滻
//                    int pos = 0, nVisit = currentPages[0].visit, nStay = currentPages[0].stay;
//                    for (int i = 1; i < pageNum; i++) {
//                        if ((currentPages[i].stay > nStay) ||
//                            (currentPages[i].stay == nStay && currentPages[i].visit < nVisit)) {
//                            nVisit = currentPages[i].visit;
//                            nStay = currentPages[i].stay;
//                            pos = i;
//                        }
//                    }
//                    cout << "�滻ҳ��P" << currentPages[pos].pageNo << "ΪP" << p << endl;
//                    currentPages[pos].pageNo = p;
//                    currentPages[pos].visit = 1;
//                    currentPages[pos].stay = 0;
//                }
//            }
//        }
//        cout << "=====��ǰ����ҳ����Ϣ=====" << endl;
//        cout << "ҳ��\t���ʴ���\tͣ��ʱ��" << endl;
//        // ÿ��ҳ�����ʱ���1
//        for (int i = 0; i < pageNum; i++) {
//            currentPages[i].stay++;
//            cout << setiosflags(ios::left) << setw(4) << currentPages[i].pageNo
//                 << setw(4) << currentPages[i].visit
//                 << setw(4) << currentPages[i].stay << endl;
//        }
////        puts("\n\n");
//    }
//}
//
//int main() {
//    LRU();
//    int n = PAGES.size(); // ��������
//    int MISS = n - HIT;
//    cout << "ȱҳ����: " << MISS << endl;
//    cout << "������: " << fixed << setprecision(4) << 1.0 * HIT / n << endl;
//    return 0;
//}