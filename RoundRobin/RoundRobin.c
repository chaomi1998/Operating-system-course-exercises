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
void operation(PCBList* process);

int main()
{
    PCBList process = NULL;
    init(&process);
    view(&process);

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

    for (int i = 1; i <= process_count; i++) {
        printf("请输入进程P%d需要运行的时间：", i);
        int time = 0;
        scanf("%d", &time);
        newProcess = (PCBNode*) malloc(sizeof(PCBNode));
        newProcess->pid = 1;
        newProcess->rr = 0;
        newProcess->sta = 'w';
        newProcess->time = time;
        newProcess->next = NULL;

        if (*process == NULL) {
            *process = newProcess;
        }
        else {
            PCBNode* seek = *process;

            while (seek->next != NULL) {
                seek = seek->next;
            }

            seek->next = newProcess;
        }
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
        printline(2);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%c\t|\n", seek->pid, seek->rr, seek->time, seek->sta);
        seek = seek->next;
    }

    printline(1);
}

void operation(PCBList* process) {

}