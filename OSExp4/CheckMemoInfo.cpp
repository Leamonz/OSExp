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
//    sprintf(para, "��ǰ�洢�ռ�ʹ���������\n");
//    sprintf(tempstr, "�����ڴ�����: %zu(BYTES)\n", MemInfo.ullTotalPhys);
//    strcat(para, tempstr);
//    sprintf(tempstr, "���������ڴ�: %zu(BYTES)\n", MemInfo.ullAvailPhys);
//    strcat(para, tempstr);
//    sprintf(tempstr, "ҳ���ļ�����: %zu(KBYTES)\n", MemInfo.ullTotalPageFile / 1024);
//    strcat(para, tempstr);
//    sprintf(tempstr, "����ҳ���ļ���: %zu(KBYTES)\n", MemInfo.ullAvailPageFile / 1024);
//    strcat(para, tempstr);
//    sprintf(tempstr, "���ռ�����: %zu(BYTES)\n", MemInfo.ullTotalVirtual);
//    strcat(para, tempstr);
//    sprintf(tempstr, "�������ռ���: %zu(BYTES)\n", MemInfo.ullAvailVirtual);
//    strcat(para, tempstr);
//    sprintf(tempstr, "����洢ʹ�ø���: %lu%%\n", MemInfo.dwMemoryLoad);
//    strcat(para, tempstr);
//
//    printf("%s", para);
//    return 0;
//}
