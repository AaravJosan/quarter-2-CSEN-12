#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STUDENTS 100 

struct Student{
    int id;
    int priority; // Lower numbers indicate higher priority
};

typedef  struct PriorityQueue{
    int front, rear;
    int capacity;
    struct Student* students;
}PQ;

struct PriorityQueue* createPriorityQueue(int capacity){
    PQ* queue = (PQ*)malloc(sizeof(PQ));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->students = (struct Student*)malloc(capacity * sizeof(struct Student));
    return queue;
}

int isEmpty(PQ* queue){
    return queue->front == -1;
}

void enqueue(PQ* queue, int student, int priority){
    if(queue->rear == queue->capacity - 1){
        printf("Queue is full\n");
        return;
    }
    int i;
    for(i = queue->rear; (i >= 0 && queue->students[i].priority > priority); i--){
        queue->students[i + 1] = queue->students[i];
    }

    queue->students[i + 1].id = student;
    queue->students[i + 1].priority = priority;
    queue->rear++;

    if (queue->front == -1){
        queue->front = 0;
    }
}

struct Student dequeue(PQ* queue){
    if(isEmpty(queue)){
        printf("Priority Queue is empty. No students waiting.\n");
        return (struct Student){-1, -1};
    }

    struct Student student = queue->students[queue->front];
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

    for(int i = 1; i <= 100; i++){
        PQ* studentQueue = createPriorityQueue(MAX_STUDENTS);
        int currentTime = 0;

        while(currentTime <= 60){ 
            int arrivalRate = generateArrivalRate();
            int serviceRate = generateServiceRate();
            int studentPriority = rand() % 3; 

            if(currentTime + arrivalRate <= 60){
                totalStudents++;
                enqueue(studentQueue, totalStudents, studentPriority);
                currentTime += arrivalRate;
            } else {
                break;
            }
        }

        currentTime = 0; // Reset time for service
        while(!isEmpty(studentQueue)){
            struct Student nextStudent = dequeue(studentQueue);
            if(currentTime + generateServiceRate() <= 60){
                totalProfessorTime += generateServiceRate();
                currentTime += generateServiceRate();
            } else {
                totalAdditionalTime += generateServiceRate();
                currentTime += generateServiceRate();
            }
            totalWaitingTime += currentTime; 
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