//1) Create a simple stack data structure that is capable of holding up to 50000 integers. (Use a simple array based implementation that contains a buffer array of size 50000 allocated on heap and a position variable to keep track of the location of the top of the stack in the buffer.) Implement the push and pop functions for this stack. Also implement a function to print all the elements of the stack.
//
//2) Create main program that creates and initialises one stack called st. Create two threads t1 and t2 where t1 pushes numbers 1 to 10000 in st and t2 pushes numbers -1 to -10000 in st. Make sure that you join both the threads so that they run completely. How many total elements should have been pushed to the stack? How many elements actually have been pushed to the stack? If you are seeing a discrepancy explain what is causing it? If you were pushing smaller number of elements (say t1 pushes 1 to 100 and t2 pushes -1 to -100) do you still see the discrepancy? Explain.
//
//3) The discrepancy you see above is caused because of concurrency issues. How can this problem be resolved using locks? Implement the lock based solution and check that the discrepancy disappears.





#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define STACK_SIZE 50000

// Structure representing a stack
typedef struct {
    int buffer[STACK_SIZE];
    int top;
    pthread_mutex_t lock; // Mutex for thread safety
} Stack;

// Function to initialize the stack
void init_stack(Stack *stack) {
    stack->top = -1;
    pthread_mutex_init(&(stack->lock), NULL);
}

// Function to push an element onto the stack
void push(Stack *stack, int element) {
    pthread_mutex_lock(&(stack->lock)); // Acquire lock before accessing shared resource
    if (stack->top == STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        pthread_mutex_unlock(&(stack->lock)); // Release lock before returning
        return;
    }
    stack->buffer[++stack->top] = element;
    pthread_mutex_unlock(&(stack->lock)); // Release lock after accessing shared resource
}

// Function to pop an element from the stack
int pop(Stack *stack) {
    pthread_mutex_lock(&(stack->lock)); // Acquire lock before accessing shared resource
    if (stack->top == -1) {
        printf("Stack underflow!\n");
        pthread_mutex_unlock(&(stack->lock)); // Release lock before returning
        return -1;
    }
    int element = stack->buffer[stack->top--];
    pthread_mutex_unlock(&(stack->lock)); // Release lock after accessing shared resource
    return element;
}

// Function to print all elements of the stack
void print_stack(Stack *stack) {
	int i;
    printf("Stack elements: ");
    for (i = stack->top; i >= 0; i--) {
        printf("%d ", stack->buffer[i]);
    }
    printf("\n");
}

// Function for t1 to push numbers 1 to 10000 in the stack
void *thread1_function(void *arg) {
    Stack *stack = (Stack *)arg;
    for (int i = 1; i <= 10000; i++) {
        push(stack, i);
    }
    pthread_exit(NULL);
}

// Function for t2 to push numbers -1 to -10000 in the stack
void *thread2_function(void *arg) {
    Stack *stack = (Stack *)arg;
    for (int i = -1; i >= -10000; i--) {
        push(stack, i);
    }
    pthread_exit(NULL);
}

int main() {
    Stack st;
    init_stack(&st);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1_function, (void *)&st);
    pthread_create(&t2, NULL, thread2_function, (void *)&st);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    print_stack(&st);

    return 0;
}

