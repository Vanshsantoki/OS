#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int response_time;
    int start_time;
    bool is_completed;
};

void sortProcessesByArrivalTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Non-preemptive SJF (Shortest Job First) scheduling
void calculateNonPreemptiveSJF(struct Process proc[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int shortest_burst_index = -1;
        int shortest_burst = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (!proc[i].is_completed && proc[i].arrival_time <= current_time && proc[i].burst_time < shortest_burst) {
                shortest_burst = proc[i].burst_time;
                shortest_burst_index = i;
            }
        }

        if (shortest_burst_index == -1) {
            current_time++;
        } else {
            proc[shortest_burst_index].response_time = current_time - proc[shortest_burst_index].arrival_time;
            proc[shortest_burst_index].completion_time = current_time + proc[shortest_burst_index].burst_time;
            proc[shortest_burst_index].turnaround_time = proc[shortest_burst_index].completion_time - proc[shortest_burst_index].arrival_time;
            proc[shortest_burst_index].waiting_time = proc[shortest_burst_index].turnaround_time - proc[shortest_burst_index].burst_time;
            proc[shortest_burst_index].is_completed = true;

            current_time = proc[shortest_burst_index].completion_time;
            completed_processes++;
        }
    }
}

// Preemptive Shortest Job First (SJF)
void calculatePreemptiveSJF(struct Process proc[], int n) {
    int current_time = 0;
    int completed = 0;
    struct Process *current_process = NULL;

    while (completed < n) {
        int shortest_burst_time = __INT_MAX__;
        current_process = NULL;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_burst_time > 0) {
                if (proc[i].remaining_burst_time < shortest_burst_time) {
                    shortest_burst_time = proc[i].remaining_burst_time;
                    current_process = &proc[i];
                }
            }
        }

        if (current_process != NULL) {
            if (current_process->remaining_burst_time == current_process->burst_time) {
                current_process->start_time = current_time;
                current_process->response_time = current_time - current_process->arrival_time;
            }

            current_process->remaining_burst_time--;
            current_time++;

            if (current_process->remaining_burst_time == 0) {
                current_process->completion_time = current_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void printResults(struct Process proc[], int n) {
    printf("PID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].burst_time, proc[i].arrival_time,
               proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time, proc[i].response_time);
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0, avg_response_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += proc[i].waiting_time;
        avg_turnaround_time += proc[i].turnaround_time;
        avg_response_time += proc[i].response_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    avg_response_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *proc = (struct Process *)malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_burst_time = proc[i].burst_time;
        proc[i].is_completed = false;
    }

    sortProcessesByArrivalTime(proc, n);

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Non-preemptive SJF\n");
    printf("2. Preemptive SJF\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            calculateNonPreemptiveSJF(proc, n);
            break;
        case 2:
            calculatePreemptiveSJF(proc, n);
            break;
        default:
            printf("Invalid choice\n");
            free(proc);
            return -1;
    }

    printResults(proc, n);

    free(proc);
    return 0;
}