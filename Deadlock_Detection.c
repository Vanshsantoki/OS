#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES]; 
int available[MAX_RESOURCES];               
int max_need[MAX_PROCESSES][MAX_RESOURCES];  

bool isDeadlock(int processes, int resources) {
    bool finish[MAX_PROCESSES] = {0}; 
    int work[MAX_RESOURCES];          
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];      
    }

    

    bool progressMade;
    do {
        progressMade = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j]; 
                    }
                    finish[i] = 1;  
                    progressMade = true;
                    break;  
                }
            }
        }
    } while (progressMade);

    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            return true; 
        }
    }

    return false; 
}

void takeInput(int processes, int resources) {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources needed by each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max_need[i][j]);
        }
    }

    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the requested resources for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }
}

int main() {
    int processes, resources;

    takeInput(processes, resources);

    if (isDeadlock(processes, resources)) {
        printf("Deadlock detected!\n");
    } 
    
    else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
