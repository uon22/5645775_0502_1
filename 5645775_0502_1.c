#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 100

struct Stack {
    int top;
    char items[MAX_LENGTH];
};

struct Queue {
    int front, rear, size;
    unsigned capacity;
    char* array;
};

void push(struct Stack* stack, char item) {
    stack->items[++stack->top] = item;
}

char pop(struct Stack* stack) {
    return stack->items[stack->top--];
}

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (char*)malloc(queue->capacity * sizeof(char));
    return queue;
}

void enqueue(struct Queue* queue, char item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

char dequeue(struct Queue* queue) {
    char item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int isPalindrome(char* str) {
    struct Stack stack;
    struct Queue* queue = createQueue(strlen(str));

    stack.top = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            push(&stack, tolower(str[i]));
            enqueue(queue, tolower(str[i]));
        }
    }

    while (stack.top != -1 && queue->size != 0) {
        if (pop(&stack) != dequeue(queue)) {
            free(queue->array);
            free(queue);
            return 0; 
        }
    }

    free(queue->array);
    free(queue);
    return 1; 
}

int main() {
    int choice;
    char input[MAX_LENGTH];

    do {
        printf("1. 회문 입력\n");
        printf("2. 회문 검사\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            getchar(); 
            scanf_s("%[^\n]s", input, sizeof(input));
            while (getchar() != '\n'); 
            break;
        case 2:
            if (strlen(input) == 0) {
                printf("입력된 문자열이 없습니다.\n");
            }
            else {
                if (isPalindrome(input))
                    printf("회문입니다.\n", input);
                else
                    printf("회문이 아닙니다.\n", input);
            }
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("올바른 메뉴를 선택하세요.\n");
        }
    } while (choice != 3);

    return 0;
}