# OSExp

SCU 操作系统实验课实验 共4个实验

## [实验一、Linux编程基础](https://github.com/Leamonz/OSExp/tree/master/OSExp1)
1. Linux基本命令
2. shell编程
3. 单处理机系统的进程调度模拟

## [实验二、作业调度实验](https://github.com/Leamonz/OSExp/tree/master/OSExp2)
需要实现三种作业调度算法
- 高响应比者优先(HRRF)
- 高优先权者优先(HPF)
- 时间片轮转法(RR)

## [实验三、互斥与同步实验](https://github.com/Leamonz/OSExp/tree/master/OSExp3)
实现了三种经典的同步互斥问题，以及一个附加的同步互斥问题
- [生产者-消费者问题](https://github.com/Leamonz/OSExp/blob/master/OSExp3/Producer_Customer.cpp)
- [读者-写者问题](https://github.com/Leamonz/OSExp/blob/master/OSExp3/Reader_Writer.cpp)
- [哲学家就餐问题](https://github.com/Leamonz/OSExp/blob/master/OSExp3/Philosopher.cpp)
  哲学家就餐问题需要避免死锁产生，此处我选择的避免死锁的方法是一次只允许一名哲学家就餐
- [过桥问题](https://github.com/Leamonz/OSExp/blob/master/OSExp3/Bridge.cpp)
  
## [实验四、内存管理实验](https://github.com/Leamonz/OSExp/tree/master/OSExp4)
1. 观察[virtumem.cpp](https://github.com/Leamonz/OSExp/blob/master/OSExp4/virtumem.cpp)的运行结果并分析
2. 观察[memoryAlloc.cpp](https://github.com/Leamonz/OSExp/blob/master/OSExp4/memoryAlloc.cpp)的运行结果并分析
3. 模拟实现[LRU](https://github.com/Leamonz/OSExp/blob/master/OSExp4/LRU.cpp)算法
4. 写一个小程序查看本机内存状况 --- [CheckMemInfo.cpp](https://github.com/Leamonz/OSExp/blob/master/OSExp4/CheckMemInfo.cpp)
5. 编写分页存储管理程序
  - [Manager.cpp](https://github.com/Leamonz/OSExp/blob/master/OSExp4/Manager.cpp) + [Manager.h](https://github.com/Leamonz/OSExp/blob/master/OSExp4/Manger.h): 实现分页存储管理的类
  - [main.cpp](https://github.com/Leamonz/OSExp/blob/master/OSExp4/main.cpp): 程序运行入口
