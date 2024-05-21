#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 100 

struct Queue {
    int front, rear;
    int capacity;
    int* students;
};

struct Queue* createQueue(int capacity){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->students = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue){
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int student){
    if(queue->rear == queue->capacity - 1){
        printf("Queue is full. Cannot add more students.\n");
        return;
    }
    queue->students[++queue->rear] = student;
    if (queue->front == -1) {
        queue->front = 0;
    }
}

int dequeue(struct Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty. No students waiting.\n");
        return -1;
    }
    int student = queue->students[queue->front];
    if(queue->front == queue->rear){
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return student;
}

int generateArrivalRate(){
    return rand() % 10 + 1; 
}

int generateServiceRate(){
    return rand() % 5 + 1; 
}

int main(){
    srand(time(NULL)); 

    int totalStudents = 0;
    int totalWaitingTime = 0;
    int totalProfessorTime = 0;
    int totalAdditionalTime = 0;

    for(int iteration = 1; iteration <= 100; iteration++){
        struct Queue* studentQueue = createQueue(MAX_STUDENTS);
        int currentTime = 0;

        while(1){ 
            int arrivalRate = generateArrivalRate();
            int serviceRate = generateServiceRate();

            if(currentTime + arrivalRate <= 60){
                totalStudents++;
                enqueue(studentQueue, totalStudents);

                currentTime += serviceRate;
                totalWaitingTime += currentTime; 
                totalProfessorTime += serviceRate; 
            }
            else 
                break;
        }

        if(!isEmpty(studentQueue)){
            totalAdditionalTime += (currentTime - 60);
        }
        free(studentQueue);
    }

    double avgWaitingTime = (double)totalWaitingTime / totalStudents;
    double avgProfessorTime = (double)totalProfessorTime / totalStudents;
    double avgAdditionalTime = (double)totalAdditionalTime / 100;

    printf("Average student waiting time: %.2f minutes\n", avgWaitingTime);
    printf("Average student time with professor: %.2f minutes\n", avgProfessorTime);
    printf("Average professor time beyond 1 hour: %.2f minutes\n", avgAdditionalTime);

    return 0;
}
