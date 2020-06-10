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
 * 表分割
 */
void printline(int type);

/*
 * 表显示
 */
void view(PCBList *process);

/*
 * 执行 
 */
void operation(PCBList* process, const int timeSlice);

/*
 * 获得时间片长度 
 */
const int getTimeSlice();

int main()
{
    PCBList process = (PCBNode*) malloc(sizeof(PCBNode));
    process->next = NULL;
    init(&process);
    const int timeSlice = getTimeSlice();

    if (timeSlice == 0) {
        return;
    }

    view(&process);
    operation(&process, timeSlice);
}

void init(PCBList *process)
{
    PCBNode* newProcess = NULL;
    
    printf("请输入进程数量(最大值%d)：", MAX_PROCESS);
    int process_count = 0;
    scanf("%d", &process_count);

    if (process_count > MAX_PROCESS) {
        return;
    }
    PCBNode* seek = *process;
    for (int i = 1; i <= process_count; i++) {
        printf("请输入进程P%d需要运行的时间：", i);
        int time = 0;
        scanf("%d", &time);

        if (time <= 0) {
            return;
        }
       
        newProcess = (PCBNode*) malloc(sizeof(PCBNode));
        newProcess->pid = i;
        newProcess->rr = 0;
        newProcess->sta = 'w';
        newProcess->time = time;
        newProcess->next = NULL;

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

    printline(1);
    printf("|\tpid\t|\trr\t|\ttime\t|\tSTA\t|\n");
    
    while (seek->next != NULL) {
        seek = seek->next;
        printline(2);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%c\t|\n", seek->pid, seek->rr, seek->time, seek->sta);
    }

    printline(1);
}

void operation(PCBList* process, const int timeSlice) {

    while ((*process)->next != NULL) {

        for (PCBList lhs = *process, rhs = (*process)->next; rhs != NULL;) {
            rhs->sta = 'f';
            if (rhs->time - rhs->rr - timeSlice > 0) {
                rhs->rr += timeSlice;
            }
            else {
                rhs->rr = rhs->time;
            }

            printf("进程 p%d 运行中......\n", rhs->pid);
            view(process);

            if (rhs->rr == rhs->time) {
                PCBList tmp = rhs;
                rhs = rhs->next;
                lhs->next = rhs;
            }
            else {
                rhs->sta = 'w';
                lhs = lhs->next;
                rhs = rhs->next;
            }
        }

    }
}

const int getTimeSlice() {
    int timeSlice = 0;
    printf("请输入时间片长度（正整数）：");
    scanf("%d", &timeSlice);

    if (timeSlice <= 0) {
        return 0;
    }
    else {
        return timeSlice;
    }
}