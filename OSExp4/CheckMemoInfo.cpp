////
//// Created by HP on 2023/5/18.
////
//
//#include <cstdio>
//#include <windows.h>
//
//int main() {
//    MEMORYSTATUSEX MemInfo;
//    MemInfo.dwLength = sizeof(MemInfo);
//    char para[3000] = "", tempstr[100];
//
//    GlobalMemoryStatusEx(&MemInfo);
//    sprintf(para, "当前存储空间使用情况如下\n");
//    sprintf(tempstr, "物理内存总数: %zu(BYTES)\n", MemInfo.ullTotalPhys);
//    strcat(para, tempstr);
//    sprintf(tempstr, "可用物理内存: %zu(BYTES)\n", MemInfo.ullAvailPhys);
//    strcat(para, tempstr);
//    sprintf(tempstr, "页面文件总数: %zu(KBYTES)\n", MemInfo.ullTotalPageFile / 1024);
//    strcat(para, tempstr);
//    sprintf(tempstr, "可用页面文件数: %zu(KBYTES)\n", MemInfo.ullAvailPageFile / 1024);
//    strcat(para, tempstr);
//    sprintf(tempstr, "虚存空间总数: %zu(BYTES)\n", MemInfo.ullTotalVirtual);
//    strcat(para, tempstr);
//    sprintf(tempstr, "可用虚存空间数: %zu(BYTES)\n", MemInfo.ullAvailVirtual);
//    strcat(para, tempstr);
//    sprintf(tempstr, "物理存储使用负荷: %lu%%\n", MemInfo.dwMemoryLoad);
//    strcat(para, tempstr);
//
//    printf("%s", para);
//    return 0;
//}
