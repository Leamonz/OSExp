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
//// 主存中的页面数量
//int pageNum = 0;
//vector<pageInfo> currentPages(3);
//// 访问页面的次序
//vector<int> PAGES = {3, 4, 2, 6, 4,
//                     3, 7, 4, 3, 6,
//                     3, 4, 8, 4, 6};
//int HIT = 0;
//
//void LRU() {
//    for (int &p: PAGES) {
//        cout << "当前访问页面: P" << p << endl;
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
//                    flag = 1; // 主存中找到该页面，访问次数加1
//                    HIT++;
//                    cout << "命中！" << endl;
//                    break;
//                }
//            }
//            // 当前主存中没有找到该页面
//            if (!flag) {
//                if (pageNum < 3) {
//                    currentPages[pageNum].pageNo = p;
//                    currentPages[pageNum].visit = 1;
//                    currentPages[pageNum].stay = 0;
//                    pageNum++;
//                } else {
//                    // 找到最近最少访问的页面，将其替换
//                    int pos = 0, nVisit = currentPages[0].visit, nStay = currentPages[0].stay;
//                    for (int i = 1; i < pageNum; i++) {
//                        if ((currentPages[i].stay > nStay) ||
//                            (currentPages[i].stay == nStay && currentPages[i].visit < nVisit)) {
//                            nVisit = currentPages[i].visit;
//                            nStay = currentPages[i].stay;
//                            pos = i;
//                        }
//                    }
//                    cout << "替换页面P" << currentPages[pos].pageNo << "为P" << p << endl;
//                    currentPages[pos].pageNo = p;
//                    currentPages[pos].visit = 1;
//                    currentPages[pos].stay = 0;
//                }
//            }
//        }
//        cout << "=====当前主存页面信息=====" << endl;
//        cout << "页号\t访问次数\t停留时间" << endl;
//        // 每个页面存留时间加1
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
//    int n = PAGES.size(); // 访问总数
//    int MISS = n - HIT;
//    cout << "缺页次数: " << MISS << endl;
//    cout << "命中率: " << fixed << setprecision(4) << 1.0 * HIT / n << endl;
//    return 0;
//}