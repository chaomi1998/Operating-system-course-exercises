// RoundRobin.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define MAX_PROCESS 6

typedef struct PCB
{
    int pid;
    int rr;
    int time;
    char sta;
    struct PCB* next;
}*PCBList, PCBNode;

/*
 * 初始化
 */
void init(PCBList *process);

/*
 * 显示表分割线
 */
void printline(int type);

/*
 * 显示表
 */
void view(PCBList *process);

/*
 * 执行 
 */
void operation(PCBList* process, const int timeSlice);

// 获得进程数量
int getProcessCount();

// 获得正整数
int getPositiveInteger();

int main()
{
    // 建立进程表头（链表）
    PCBList process = (PCBNode*) malloc(sizeof(PCBNode));
    process->next = NULL;
    if (process == NULL) {
        printf("系统错误!按任意键退出");
        getchar();
        exit(-1);
    }

    // 初始化信息
    init(&process);

    // 获取时间片长度
    printf("请输入时间片长度（正整数）：");
    int timeSlice = getPositiveInteger();

    // 显示初始信息
    view(&process);

    // 开始调度
    operation(&process, timeSlice);
}

void init(PCBList *process)
{
    PCBNode* newProcess = NULL;
    
    printf("请输入进程数量(最大值%d)：", MAX_PROCESS);
    int process_count = getProcessCount();
 
    // 访问索引
    PCBNode* seek = *process;

    // 获得所有进程的运行时间
    for (int i = 1; i <= process_count; i++) {
        printf("请输入进程P%d需要运行的时间：", i);
        int time = getPositiveInteger();
       
        // 初始化进程信息
        newProcess = (PCBNode*) malloc(sizeof(PCBNode));

        if (newProcess == NULL) {
            printf("系统错误!按任意键退出");
            getchar();
            exit(-1);
        }

        newProcess->pid = i;
        newProcess->rr = 0;
        newProcess->sta = 'w';
        newProcess->time = time;
        newProcess->next = NULL;

        // 将新初始化的进程放进表尾
        seek->next = newProcess;
        seek = seek->next;
    }
}

void printline(int type)
{
    if (type == 1) {
        printf("+---------------|---------------|---------------|---------------+\n");
    }
    else if (type == 2) {
        printf("|---------------|---------------|---------------|---------------|\n");
    }
}

void view(PCBList *process)
{
    PCBNode* seek = *process;

    // 打印表头
    printline(1);
    printf("|\tpid\t|\trr\t|\ttime\t|\tSTA\t|\n");
    
    // 依次打印表内容
    while (seek->next != NULL) {
        seek = seek->next;
        printline(2);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%c\t|\n", seek->pid, seek->rr, seek->time, seek->sta);
    }

    printline(1);
}

void operation(PCBList* process, const int timeSlice) {

    // 只有进程表中所有进程都执行完后才会退出
    while ((*process)->next != NULL) {

        for (PCBList lhs = *process, rhs = (*process)->next; rhs != NULL;) {
            // 将进程置为运行态
            rhs->sta = 'f';
            printf("进程 p%d 运行中......\n", rhs->pid);

            // 将进程的已执行时间加上时间片 如果超出进程的运行时间则只运行需要的时间
            if (rhs->rr + timeSlice < rhs->time) {
                rhs->rr += timeSlice;
            }
            else {
                rhs->rr = rhs->time;
            }

            // 显示当前状态
            view(process);

            // 如果进程已经执行完则从进程表中移除 之后轮转下一个进程
            if (rhs->rr == rhs->time) {
                PCBList tmp = rhs;
                rhs = rhs->next;
                lhs->next = rhs;
                free(tmp);
            }
            else {
                rhs->sta = 'w';
                lhs = lhs->next;
                rhs = rhs->next;
            }
        }

    }
}

int getProcessCount() {
    
    int process_count = 0;

    while (1) {
        scanf("%d", &process_count);

        if (process_count > MAX_PROCESS || process_count <= 0) {
            printf("数量错误！请重新输入：");
            continue;
        }
        else {
            return process_count;
        }
    }
    
}


int getPositiveInteger() {
    int num = 0;
    while (1) {
        scanf("%d", &num);

        if (num <= 0) {
            printf("输入数字必须为正整数，你的输入为 %d 请重新输入：", num);
            continue;
        }
        else {
            return num;
        }
    }
}