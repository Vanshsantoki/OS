#include <stdio.h>
#include <string.h>

int n;

struct Process {
    int pid;                 
    char name[20];          
    int arrivalTime;           
    int completionTime;        
    int executionTime;         
};

void search(struct Process processes[], int id) {
    for (int i = 0; i < n; i++) {
        if (processes[i].pid == id) {
            printf("Process id: %d\n", processes[i].pid);
            printf("Process name: %s\n", processes[i].name);
            printf("Process arrival time: %d\n", processes[i].arrivalTime);
            printf("Process execution time: %d\n", processes[i].executionTime);
            printf("Process completion time: %dms\n\n", processes[i].completionTime);
            return;
        }
    }
    printf("Process with the given process id not found\n");
}

void add(struct Process processes[]) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        processes[i].pid = i + 1;

        printf("Enter process name: ");
        scanf("%s", processes[i].name);

        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter execution time: ");
        scanf("%d", &processes[i].executionTime);

        
        processes[i].completionTime = processes[i].executionTime - processes[i].arrivalTime; 
        processes[i].completionTime = processes[i].completionTime*60*100
    }
}

void display(struct Process processes[]) {
    for (int i = 0; i < n; i++) {
        printf("Process id: %d\n", processes[i].pid);
        printf("Process name: %s\n", processes[i].name);
        printf("Process arrival time: %d\n", processes[i].arrivalTime);
        printf("Process execution time: %d\n", processes[i].executionTime);
        printf("Process completion time: %dms\n\n", processes[i].completionTime);
    }
}

int main() {
    int p_id;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    add(processes);

    printf("\nProcess Details:\n");
    display(processes);

    printf("Enter process_id to search: ");
    scanf("%d", &p_id);
    search(processes, p_id);

    return 0;
}