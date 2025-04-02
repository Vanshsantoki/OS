#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESSES 10
typedef struct {
    int pid;
    int priority;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;
typedef struct {
    Process processes[MAX_PROCESSES];
    int front, rear;
} Queue;
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}
int isEmpty(Queue *q) {
    return q->front == -1;
}
void enqueue(Queue *q, Process p) {
    if (q->rear == MAX_PROCESSES - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->processes[q->rear] = p;
}
Process dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        Process empty = {-1, -1, -1, -1, -1, -1};
        return empty;
    }
    Process p = q->processes[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return p;
}
void multiLevelQueueScheduling(Process processes[], int n) {
    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);
    int current_time = 0;
    int total_waiting = 0, total_turnaround = 0;
    int completed = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (processes[j].arrival_time > processes[j+1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 0) {
            enqueue(&systemQueue, processes[i]);
        } else {
            enqueue(&userQueue, processes[i]);
        }
    }
    printf("\nGantt Chart:\n");
    printf("Time\tProcess\tPriority\n");
    printf("------------------------\n");
    while (!isEmpty(&systemQueue)) {
        Process current = dequeue(&systemQueue);
        if (current_time < current.arrival_time) {
            current_time = current.arrival_time;
        }
        printf("%d-%d\tP%d\tSystem\n", current_time, current_time + current.burst_time, current.pid);
        current.waiting_time = current_time - current.arrival_time;
        current.turnaround_time = current.waiting_time + current.burst_time;
        total_waiting += current.waiting_time;
        total_turnaround += current.turnaround_time;
        current_time += current.burst_time;
        completed++;
    }
    while (!isEmpty(&userQueue)) {
        Process current = dequeue(&userQueue);
        if (current_time < current.arrival_time) {
            current_time = current.arrival_time;
        }
        printf("%d-%d\tP%d\tUser\n", current_time, current_time + current.burst_time, current.pid);
        current.waiting_time = current_time - current.arrival_time;
        current.turnaround_time = current.waiting_time + current.burst_time;
        total_waiting += current.waiting_time;
        total_turnaround += current.turnaround_time;
        current_time += current.burst_time;
        completed++;
    }
    float avg_waiting = (float)total_waiting / n;
    float avg_turnaround = (float)total_turnaround / n;
    printf("\nProcess\tPriority\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].priority == 0 ? "System" : "User",
               processes[i].burst_time,
               processes[i].arrival_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
}
int main() {
    int n;
    Process processes[MAX_PROCESSES];
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d:\n", i+1);
        processes[i].pid = i+1;
        printf("Priority (0 for System, 1 for User): ");
        scanf("%d", &processes[i].priority);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
    }
    multiLevelQueueScheduling(processes, n);
    return 0;
}
