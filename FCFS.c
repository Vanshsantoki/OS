#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int compareArrivalTime(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;
    return processA->arrival_time - processB->arrival_time;
}

void calculateTimes(struct Process processes[], int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i].waiting_time;

        current_time = processes[i].completion_time;
    }
}

void printTable(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time, processes[i].response_time);
    }
}

void calculateAverages(struct Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waiting_time;
        totalResponseTime += processes[i].response_time;
        totalTurnaroundTime += processes[i].turnaround_time;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgResponseTime = (double)totalResponseTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    qsort(processes, n, sizeof(struct Process), compareArrivalTime);

    calculateTimes(processes, n);

    printTable(processes, n);

    calculateAverages(processes, n);

    return 0;
}
