#include <stdio.h>
#include <stdbool.h>

#define MAX_THREADS 100
#define MAX_RESOURCES 100

int available[MAX_RESOURCES];
int maximum[MAX_THREADS][MAX_RESOURCES];
int allocation[MAX_THREADS][MAX_RESOURCES];
int need[MAX_THREADS][MAX_RESOURCES];
int work[MAX_RESOURCES];
bool finish[MAX_THREADS];

int n_threads, n_resources;
int i, j;





bool is_safe_state() {
    // Initialize work and finish arrays
    
    for (i = 0; i < n_resources; i++) {
        work[i] = available[i];
    }
    for (i = 0; i < n_threads; i++) {
        finish[i] = false;
    }

    // Find an i such that both finish[i] == false and need_i <= work
    int completed_threads = 0;
    while (completed_threads < n_threads) {
        bool found = false;
        for (i = 0; i < n_threads; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                for (j = 0; j < n_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    // Allocate resources
                    for (j = 0; j < n_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    completed_threads++;
                    found = true;
                }
            }
        }
        // If no such i exists, the system is in an unsafe state
        if (!found) {
            return false;
        }
    }
    // If all threads finish, the system is in a safe state
    return true;
}

bool request_resources(int thread_num, int request[]) {
    // Check if request is within need and available resources
    for (i = 0; i < n_resources; i++) {
        if (request[i] > need[thread_num][i] || request[i] > available[i]) {
            return false;
        }
    }
    
    // Attempt to allocate resources
    for (i = 0; i < n_resources; i++) {
        available[i] -= request[i];
        allocation[thread_num][i] += request[i];
        need[thread_num][i] -= request[i];
    }

    // Check if the system is in a safe state after allocation
    if (is_safe_state()) {
        return true;
    } else {
        // If allocation leads to an unsafe state, revert changes
        for (i = 0; i < n_resources; i++) {
            available[i] += request[i];
            allocation[thread_num][i] -= request[i];
            need[thread_num][i] += request[i];
        }
        return false;
    }
}

bool is_deadlocked() {
    // A system is deadlocked if it is not in a safe state
    return !is_safe_state();
}


//int element = stack->buffer[stack->top--];
//    pthread_mutex_unlock(&(stack->lock)); // Release lock after accessing shared resource
//    return element;

int main() {
    //printf("Enter number of threads: ");
    //scanf("%d", &n_threads);

    printf("Enter number of resources: ");
    scanf("%d", &n_resources);

    printf("Enter total number of resources of each type: ");
    for (i = 0; i < n_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum needed resources of each type for each thread:\n");
    for (i = 0; i < n_threads; i++) {
        printf("Thread %d: ", i);
        for (j = 0; j < n_resources; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    printf("Enter current allocation of resources for each thread:\n");
    for (i = 0; i < n_threads; i++) {
        printf("Thread %d: ", i);
        for (j = 0; j < n_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }

    if (is_safe_state()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    int request_thread;
    printf("Enter the thread number requesting resources: ");
    scanf("%d", &request_thread);

    int request[MAX_RESOURCES];
    printf("Enter the requested resources for thread %d: ", request_thread);
    for (i = 0; i < n_resources; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(request_thread, request)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied. Granting the request would lead to an unsafe state.\n");
    }

    if (is_deadlocked()) {
        printf("System is in a deadlocked state.\n");
    } else {
        printf("System is not in a deadlocked state.\n");
    }

    return 0;
}

