/*
 * dsa_demo.c
 * A small, standalone C11 program for demonstrating basic DSA concepts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define CAPACITY 5
#define MAX_ARRAY_SIZE 50
#define INPUT_SIZE 128

typedef struct {
    int values[CAPACITY];
    int top;
} Stack;

typedef struct {
    int values[CAPACITY];
    int front;
    int rear;
    int count;
} CircularQueue;

/* Read one whole line so invalid input cannot leave characters in stdin. */
static int read_int(const char *prompt)
{
    char input[INPUT_SIZE];
    char *end;
    long value;

    for (;;) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        value = strtol(input, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\n') {
            end++;
        }

        if (errno == 0 && end != input && *end == '\0' &&
            value >= INT_MIN && value <= INT_MAX) {
            return (int)value;
        }
        printf("Invalid input. Please enter a whole number.\n");
    }
}

static int read_array(int array[], const char *purpose)
{
    int count;
    int i;
    char prompt[INPUT_SIZE];

    printf("\n%s\n", purpose);
    do {
        count = read_int("How many elements (1-50)? ");
        if (count < 1 || count > MAX_ARRAY_SIZE) {
            printf("Please enter a number from 1 to %d.\n", MAX_ARRAY_SIZE);
        }
    } while (count < 1 || count > MAX_ARRAY_SIZE);

    for (i = 0; i < count; i++) {
        (void)snprintf(prompt, sizeof(prompt), "Element %d: ", i);
        array[i] = read_int(prompt);
    }
    return count;
}

static void print_array(const int array[], int count)
{
    int i;

    printf("[");
    for (i = 0; i < count; i++) {
        printf("%d%s", array[i], (i == count - 1) ? "" : ", ");
    }
    printf("]\n");
}

static void copy_array(int destination[], const int source[], int count)
{
    memcpy(destination, source, (size_t)count * sizeof(destination[0]));
}

/* ---------------------------- Stack section ---------------------------- */

static void stack_init(Stack *stack)
{
    stack->top = -1;
}

static int stack_is_empty(const Stack *stack)
{
    return stack->top == -1;
}

static int stack_is_full(const Stack *stack)
{
    return stack->top == CAPACITY - 1;
}

static void stack_display(const Stack *stack)
{
    int i;

    printf("Stack (top -> bottom): ");
    if (stack_is_empty(stack)) {
        printf("[empty]\n");
        return;
    }
    for (i = stack->top; i >= 0; i--) {
        printf("%d%s", stack->values[i], (i == 0) ? "" : " -> ");
    }
    printf("\n");
}

static void stack_push(Stack *stack, int value)
{
    if (stack_is_full(stack)) {
        printf("Stack overflow: capacity is %d, so %d cannot be pushed.\n",
               CAPACITY, value);
    } else {
        stack->values[++stack->top] = value;
        printf("Pushed %d onto the top of the stack.\n", value);
    }
    stack_display(stack);
}

static void stack_pop(Stack *stack)
{
    if (stack_is_empty(stack)) {
        printf("Stack underflow: there is nothing to pop.\n");
    } else {
        printf("Popped %d from the top of the stack.\n", stack->values[stack->top--]);
    }
    stack_display(stack);
}

static void stack_peek(const Stack *stack)
{
    if (stack_is_empty(stack)) {
        printf("The stack is empty; it has no top element.\n");
    } else {
        printf("Peek: the top element is %d.\n", stack->values[stack->top]);
    }
    stack_display(stack);
}

static void stack_menu(void)
{
    Stack stack;
    int choice;

    stack_init(&stack);
    printf("\n--- STACK DEMONSTRATION ---\n");
    printf("A stack follows LIFO: Last In, First Out.\n");
    printf("It starts empty and has capacity %d.\n", CAPACITY);

    do {
        printf("\n1. Push  2. Pop  3. Peek  4. Display  5. Check status  6. Back\n");
        choice = read_int("Enter your choice: ");
        switch (choice) {
        case 1:
            stack_push(&stack, read_int("Value to push: "));
            break;
        case 2:
            stack_pop(&stack);
            break;
        case 3:
            stack_peek(&stack);
            break;
        case 4:
            stack_display(&stack);
            break;
        case 5:
            printf("Empty: %s | Full: %s\n", stack_is_empty(&stack) ? "yes" : "no",
                   stack_is_full(&stack) ? "yes" : "no");
            stack_display(&stack);
            break;
        case 6:
            break;
        default:
            printf("Please choose a number from 1 to 6.\n");
        }
    } while (choice != 6);
}

/* ------------------------ Circular queue section ----------------------- */

static void queue_init(CircularQueue *queue)
{
    int i;

    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    for (i = 0; i < CAPACITY; i++) {
        queue->values[i] = 0;
    }
}

static int queue_is_empty(const CircularQueue *queue)
{
    return queue->count == 0;
}

static int queue_is_full(const CircularQueue *queue)
{
    return queue->count == CAPACITY;
}

static void queue_display(const CircularQueue *queue)
{
    int i;
    int index;

    printf("Queue (front -> rear): ");
    if (queue_is_empty(queue)) {
        printf("[empty]\n");
    } else {
        for (i = 0; i < queue->count; i++) {
            index = (queue->front + i) % CAPACITY;
            printf("%d%s", queue->values[index],
                   (i == queue->count - 1) ? "" : " -> ");
        }
        printf("\n");
    }

    printf("Array slots: ");
    for (i = 0; i < CAPACITY; i++) {
        printf("[%d:%d]%s", i, queue->values[i], (i == CAPACITY - 1) ? "" : " ");
    }
    printf("\nfront = %d, rear = %d, elements = %d\n",
           queue->front, queue->rear, queue->count);
}

static void queue_enqueue(CircularQueue *queue, int value)
{
    if (queue_is_full(queue)) {
        printf("Queue overflow: capacity is %d, so %d cannot be enqueued.\n",
               CAPACITY, value);
    } else {
        queue->rear = (queue->rear + 1) % CAPACITY;
        queue->values[queue->rear] = value;
        queue->count++;
        printf("Enqueued %d at array slot %d.\n", value, queue->rear);
    }
    queue_display(queue);
}

static void queue_dequeue(CircularQueue *queue)
{
    int value;

    if (queue_is_empty(queue)) {
        printf("Queue underflow: there is nothing to dequeue.\n");
    } else {
        value = queue->values[queue->front];
        printf("Dequeued %d from array slot %d.\n", value, queue->front);
        queue->front = (queue->front + 1) % CAPACITY;
        queue->count--;
    }
    queue_display(queue);
}

static void queue_menu(void)
{
    CircularQueue queue;
    int choice;

    queue_init(&queue);
    printf("\n--- CIRCULAR QUEUE DEMONSTRATION ---\n");
    printf("A queue follows FIFO: First In, First Out.\n");
    printf("The rear wraps to the beginning to reuse freed array slots.\n");
    printf("Try: enqueue 10,20,30,40; dequeue twice; enqueue 50,60.\n");

    do {
        printf("\n1. Enqueue  2. Dequeue  3. Display  4. Check status  5. Back\n");
        choice = read_int("Enter your choice: ");
        switch (choice) {
        case 1:
            queue_enqueue(&queue, read_int("Value to enqueue: "));
            break;
        case 2:
            queue_dequeue(&queue);
            break;
        case 3:
            queue_display(&queue);
            break;
        case 4:
            printf("Empty: %s | Full: %s\n", queue_is_empty(&queue) ? "yes" : "no",
                   queue_is_full(&queue) ? "yes" : "no");
            queue_display(&queue);
            break;
        case 5:
            break;
        default:
            printf("Please choose a number from 1 to 5.\n");
        }
    } while (choice != 5);
}

/* --------------------------- Search section ---------------------------- */

static void linear_search_demo(void)
{
    int array[MAX_ARRAY_SIZE];
    int count;
    int target;
    int i;
    int comparisons = 0;
    int found_index = -1;

    printf("\n--- LINEAR SEARCH DEMONSTRATION ---\n");
    printf("Linear search checks elements sequentially, from left to right.\n");
    count = read_array(array, "Enter the array for linear search.");
    target = read_int("Value to search for: ");

    printf("Array: ");
    print_array(array, count);
    printf("Searching for: %d\n", target);
    for (i = 0; i < count; i++) {
        comparisons++;
        printf("Comparison %d: checking index %d (value %d)", comparisons, i, array[i]);
        if (array[i] == target) {
            printf(" -> match found!\n");
            found_index = i;
            break;
        }
        printf(" -> not a match.\n");
    }

    if (found_index >= 0) {
        printf("Result: %d was found at index %d.\n", target, found_index);
    } else {
        printf("Result: %d was not found in the array.\n", target);
    }
    printf("Number of comparisons: %d\n", comparisons);
}

static int is_sorted_ascending(const int array[], int count)
{
    int i;

    for (i = 1; i < count; i++) {
        if (array[i - 1] > array[i]) {
            return 0;
        }
    }
    return 1;
}

static void binary_search_demo(void)
{
    int array[MAX_ARRAY_SIZE];
    int count;
    int target;
    int low;
    int high;
    int middle;
    int comparisons = 0;
    int found_index = -1;

    printf("\n--- BINARY SEARCH DEMONSTRATION ---\n");
    printf("Binary search repeatedly halves a sorted search range.\n");
    do {
        count = read_array(array, "Enter an array already sorted in ascending order.");
        if (!is_sorted_ascending(array, count)) {
            printf("This array is not in ascending order. Binary search needs sorted input.\n");
            printf("Please enter a sorted array again.\n");
        }
    } while (!is_sorted_ascending(array, count));

    target = read_int("Value to search for: ");
    printf("Array: ");
    print_array(array, count);
    printf("Searching for: %d\n", target);

    low = 0;
    high = count - 1;
    while (low <= high) {
        middle = low + (high - low) / 2;
        comparisons++;
        printf("Comparison %d: range [%d, %d], middle index %d (value %d).\n",
               comparisons, low, high, middle, array[middle]);
        if (array[middle] == target) {
            printf("The middle value matches the target.\n");
            found_index = middle;
            break;
        }
        if (target < array[middle]) {
            high = middle - 1;
            printf("%d is smaller, so search the left half: [%d, %d].\n", target, low, high);
        } else {
            low = middle + 1;
            printf("%d is larger, so search the right half: [%d, %d].\n", target, low, high);
        }
    }

    if (found_index >= 0) {
        printf("Result: %d was found at index %d.\n", target, found_index);
    } else {
        printf("Result: %d was not found in the array.\n", target);
    }
    printf("Number of comparisons: %d\n", comparisons);
}

/* ---------------------------- Sorting section -------------------------- */

static void swap(int *first, int *second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

static void bubble_sort_demo(int array[], int count)
{
    int pass;
    int i;
    int swapped;

    printf("Bubble Sort: adjacent out-of-order values are swapped.\n");
    for (pass = 0; pass < count - 1; pass++) {
        swapped = 0;
        for (i = 0; i < count - 1 - pass; i++) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = 1;
            }
        }
        printf("After pass %d: ", pass + 1);
        print_array(array, count);
        if (!swapped) {
            printf("No swaps were needed; the array is already sorted.\n");
            break;
        }
    }
}

static void selection_sort_demo(int array[], int count)
{
    int position;
    int i;
    int smallest;

    printf("Selection Sort: repeatedly selects the smallest remaining value.\n");
    for (position = 0; position < count - 1; position++) {
        smallest = position;
        for (i = position + 1; i < count; i++) {
            if (array[i] < array[smallest]) {
                smallest = i;
            }
        }
        swap(&array[position], &array[smallest]);
        printf("After selecting position %d: ", position);
        print_array(array, count);
    }
}

static void insertion_sort_demo(int array[], int count)
{
    int i;
    int key;
    int j;

    printf("Insertion Sort: inserts each value into its correct place in the sorted left part.\n");
    for (i = 1; i < count; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
        printf("After inserting %d: ", key);
        print_array(array, count);
    }
}

static void merge(int array[], int temporary[], int left, int middle, int right, int total_count)
{
    int i = left;
    int j = middle + 1;
    int k = left;
    int index;

    while (i <= middle && j <= right) {
        if (array[i] <= array[j]) {
            temporary[k++] = array[i++];
        } else {
            temporary[k++] = array[j++];
        }
    }
    while (i <= middle) {
        temporary[k++] = array[i++];
    }
    while (j <= right) {
        temporary[k++] = array[j++];
    }
    for (index = left; index <= right; index++) {
        array[index] = temporary[index];
    }

    printf("Merged indexes %d-%d: ", left, right);
    print_array(array, total_count);
}

static void merge_sort_recursive(int array[], int temporary[], int left, int right, int total_count)
{
    int middle;

    if (left >= right) {
        return;
    }
    middle = left + (right - left) / 2;
    merge_sort_recursive(array, temporary, left, middle, total_count);
    merge_sort_recursive(array, temporary, middle + 1, right, total_count);
    merge(array, temporary, left, middle, right, total_count);
}

static void merge_sort_demo(int array[], int count)
{
    int temporary[MAX_ARRAY_SIZE];

    printf("Merge Sort: splits the array into halves, then merges sorted halves.\n");
    merge_sort_recursive(array, temporary, 0, count - 1, count);
}

static int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

static void quick_sort_recursive(int array[], int low, int high, int total_count)
{
    int pivot_index;

    if (low >= high) {
        return;
    }
    pivot_index = partition(array, low, high);
    printf("Partitioned indexes %d-%d; pivot %d is now at index %d: ",
           low, high, array[pivot_index], pivot_index);
    print_array(array, total_count);
    quick_sort_recursive(array, low, pivot_index - 1, total_count);
    quick_sort_recursive(array, pivot_index + 1, high, total_count);
}

static void quick_sort_demo(int array[], int count)
{
    printf("Quick Sort: partitions values around a pivot, then sorts each side.\n");
    quick_sort_recursive(array, 0, count - 1, count);
}

static void sorting_menu(void)
{
    int original[MAX_ARRAY_SIZE];
    int working[MAX_ARRAY_SIZE];
    int count;
    int choice;

    printf("\n--- SORTING ALGORITHMS DEMONSTRATION ---\n");
    count = read_array(original, "Enter the array to sort (duplicates and negative values are allowed).");

    do {
        printf("\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n");
        printf("4. Merge Sort\n5. Quick Sort\n6. Back\n");
        choice = read_int("Choose an algorithm: ");
        if (choice >= 1 && choice <= 5) {
            copy_array(working, original, count);
            printf("\nOriginal array: ");
            print_array(working, count);
            switch (choice) {
            case 1:
                bubble_sort_demo(working, count);
                break;
            case 2:
                selection_sort_demo(working, count);
                break;
            case 3:
                insertion_sort_demo(working, count);
                break;
            case 4:
                merge_sort_demo(working, count);
                break;
            case 5:
                quick_sort_demo(working, count);
                break;
            default:
                break;
            }
            printf("Final sorted array: ");
            print_array(working, count);
        } else if (choice != 6) {
            printf("Please choose a number from 1 to 6.\n");
        }
    } while (choice != 6);
}

int main(void)
{
    int choice;

    do {
        printf("\n====================================\n");
        printf("       DATA STRUCTURES DEMO\n");
        printf("====================================\n\n");
        printf("1. Stack\n");
        printf("2. Circular Queue\n");
        printf("3. Linear Search\n");
        printf("4. Binary Search\n");
        printf("5. Sorting Algorithms\n");
        printf("6. Exit\n\n");
        choice = read_int("Enter your choice: ");

        switch (choice) {
        case 1:
            stack_menu();
            break;
        case 2:
            queue_menu();
            break;
        case 3:
            linear_search_demo();
            break;
        case 4:
            binary_search_demo();
            break;
        case 5:
            sorting_menu();
            break;
        case 6:
            printf("Thank you for using the Data Structures Demo.\n");
            break;
        default:
            printf("Please choose a number from 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
