#include <stdio.h>

#define MAX 10

typedef struct {
    int id;       
    int arrival;   
    int burst;     
    int remaining; 
    int completion;
    int start;     
    int waiting;   
    int turnaround; 
    int response;   
} Process;

void roundRobinScheduling(Process proc[], int n, int quantum) {
    int time = 0;
    int remaining_processes = n;
    int i, done;

    while (remaining_processes > 0) {
        done = 1;
        for (i = 0; i < n; i++) {
            if (proc[i].remaining > 0) {
                done = 0;

                if (proc[i].start == -1 && proc[i].arrival <= time) {
                    proc[i].start = time;
                    proc[i].response = time - proc[i].arrival;
                }

                if (proc[i].remaining > quantum) {
                    proc[i].remaining -= quantum;
                    time += quantum;
                } else {
                    time += proc[i].remaining;
                    proc[i].completion = time;
                    proc[i].remaining = 0;
                    proc[i].turnaround = proc[i].completion - proc[i].arrival;
                    proc[i].waiting = proc[i].turnaround - proc[i].burst;
                    remaining_processes--;
                }
            }
        }

        if (done) break;
    }
}

void printProcesses(Process proc[], int n) {
    printf("\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time | Completion Time | Response Time\n");
    for (int i = 0; i < n; i++) {
        printf("%9d | %12d | %10d | %12d | %16d | %15d | %13d\n",
               proc[i].id, proc[i].arrival, proc[i].burst, proc[i].waiting,
               proc[i].turnaround, proc[i].completion, proc[i].response);
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
        proc[i].remaining = proc[i].burst;
        proc[i].start = -1; 
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobinScheduling(proc, n, quantum);

    printProcesses(proc, n);

    return 0;
}