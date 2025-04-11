#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id;
    int burst;
    int period;
    int deadline;
    int remaining;
    int weight;
    int next_arrival;
    int next_deadline;
} Task;

// Function to calculate GCD
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to calculate LCM of an array of integers
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_lcm_of_deadlines(Task tasks[], int n) {
    int result = tasks[0].deadline;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].deadline);
    }
    return result;
}

void rate_monotonic(Task tasks[], int n, int hyper_period) {
    printf("\nRate-Monotonic Scheduling:\n");
    for (int t = 0; t < hyper_period; t++) {
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining = tasks[i].burst;
                tasks[i].next_arrival += tasks[i].period;
                tasks[i].next_deadline = t + tasks[i].period;
            }
            if (tasks[i].remaining > 0 &&
                (current == -1 || tasks[i].period < tasks[current].period)) {
                current = i;
            }
        }
        if (current != -1) {
            printf("Time %d: P%d\n", t, tasks[current].id);
            tasks[current].remaining--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

void earliest_deadline_first(Task tasks[], int n, int hyper_period) {
    printf("\nEarliest-Deadline First Scheduling:\n");
    for (int t = 0; t < hyper_period; t++) {
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining = tasks[i].burst;
                tasks[i].next_arrival += tasks[i].period;
                tasks[i].next_deadline = t + tasks[i].deadline;
            }
            if (tasks[i].remaining > 0 &&
                (current == -1 || tasks[i].next_deadline < tasks[current].next_deadline)) {
                current = i;
            }
        }
        if (current != -1) {
            printf("Time %d: P%d\n", t, tasks[current].id);
            tasks[current].remaining--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

void proportional_scheduling(Task tasks[], int n, int total_time) {
    printf("\nProportional Scheduling (Weighted Round Robin Approx.):\n");
    int time = 0;
    while (time < total_time) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < tasks[i].weight && time < total_time; j++) {
                printf("Time %d: P%d\n", time, tasks[i].id);
                time++;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX];

    printf("Enter number of tasks (max %d): ", MAX);
    scanf("%d", &n);
    if (n > MAX) n = MAX;

    printf("Enter Burst times (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].burst);
    }

    printf("Enter Periods (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].period);
    }

    printf("Enter Deadlines (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].deadline);
    }

    printf("Enter Weights (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].weight);
    }

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        tasks[i].remaining = 0;
        tasks[i].next_arrival = 0;
        tasks[i].next_deadline = 0;
    }

    int hyper_period = calculate_lcm_of_deadlines(tasks, n);
    printf("\nCalculated total simulation time (LCM of deadlines): %d\n", hyper_period);

    rate_monotonic(tasks, n, hyper_period);

    for (int i = 0; i < n; i++) {
        tasks[i].remaining = 0;
        tasks[i].next_arrival = 0;
        tasks[i].next_deadline = 0;
    }

    earliest_deadline_first(tasks, n, hyper_period);

    proportional_scheduling(tasks, n, hyper_period);

    return 0;
}