#include <stdio.h>

void findCompletionTimeNonPreemptive(int n, int bt[], int at[], int ct[], int priority[]) {
    int completed = 0, time = 0;
    int is_completed[n];

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed < n) {
        int min_priority = -1;
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && at[i] <= time) {
                if (min_priority == -1 || priority[i] < priority[min_priority]) {
                    min_priority = i;
                }
            }
        }

        if (min_priority != -1) {
            time += bt[min_priority];  
            ct[min_priority] = time; 
            is_completed[min_priority] = 1; 
            completed++;
        } else {
            time++;  
        }
    }
}

void findTurnaroundTime(int n, int bt[], int at[], int ct[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }
}

void findWaitingTime(int n, int bt[], int at[], int ct[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }
}

void findResponseTime(int n, int at[], int wt[], int rt[]) {
    for (int i = 0; i < n; i++) {
        rt[i] = wt[i];
    }
}

void findAvgTime(int n, int wt[], int tat[], int rt[]) {
    int total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
    printf("Average response time: %.2f\n", (float)total_rt / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], at[n], priority[n], ct[n], tat[n], wt[n], rt[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
        processes[i] = i + 1; 
    }

    findCompletionTimeNonPreemptive(n, bt, at, ct, priority);
    findTurnaroundTime(n, bt, at, ct, tat);
    findWaitingTime(n, bt, at, ct, wt, tat);
    findResponseTime(n, at, wt, rt);
    findAvgTime(n, wt, tat, rt);

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
            processes[i], at[i], bt[i], priority[i], ct[i], wt[i], tat[i], rt[i]);
    }

    return 0;

}
