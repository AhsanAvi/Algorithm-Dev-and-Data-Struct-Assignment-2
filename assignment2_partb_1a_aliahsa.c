/** 
 * • Name: Ahsan Ali (aliahsa)
 * • Assignment: Assignment 2, Part 2 1A
 * • Date: September 25, 2020
 * 
 * • This program creates a priorityQueue from a unsorted array
 * which has full functionality of enqueue and dequeuing
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void dequeueArr(int a[], int size) {
    int loopcounter = 0;
    int dequeueArr[size];
    
    FILE *file = fopen("dequeued.txt", "w"); 
    //open the dequeue text file to store dequeued numbers
    if (file == NULL) { //if the file is not opened exit
        printf("Cannot Open File");
        exit(1);
    }

    //the purpose of loop counter is to continuously: find the lowest number, replace it with the last number in the array, and put it into the file until it reaches the size of input.
    while (loopcounter < size) {    
        int temp = 999999;
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (a[i] < temp && a[i] != 0) {    
                temp = a[i];
                counter = i;
            }
        }
        /* ^^ for loop
        making sure that a[i] is not 0 because 0 is the last 
        element in the array, 0 is not to be considered 
        the smallest number
        */
        
        //test code to see what the index of lowest number is
        //printf("%d", counter);
        
        dequeueArr[loopcounter] = a[counter];
        //store smallest number in the dequeue array before dequeuing
        a[counter] = a[size-(loopcounter+1)];
        /*a[smallest number] = a[size-loopcounter]
        do +1 so that loopcounter is initially 1 on the first run
        and is the correct size
        */
        a[size-(loopcounter+1)] = 0;
        //set last number in the array to 0 since it has been copied
        

        //you can uncomment these lines to see output of the algorithm working
        //puts("");
        // for (int i = 0; i < size; i++) {
        //     printf("%d ", a[i]);
        // }

        loopcounter++;
    }

    for (int i = 0; i < size; i++){
        fprintf(file, "%d ", dequeueArr[i]);
    }
    fclose(file);
}

 void enqueueArr(int a[], int size) {
    int counter;
    int buffer[300]; 

    FILE *file = fopen("test_dat.txt", "r"); 
    //open the file and read from it
    if (file == NULL) {
        //if the file is not opened exit
        printf("Cannot Open File");
        exit(1); 
    }
    
    while (!feof(file) && counter < size) {
        fgets(buffer, 300, file);   //gets the whole file as a string
        a[counter] = atoi(buffer); //converting string to int and storing into array
        counter++;
    }

    //TEST CODE TO SEE IF ENQUE IS WORKING
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", a[i]);
    // } //REMOVE THIS LATER

    fclose(file);
}

int main() {
    int arraySize = 50000;
    int priortyQueue[arraySize];
    clock_t start;
    clock_t end;

    printf("Enqueueing size..");
    start = clock();
    enqueueArr(priortyQueue, arraySize);
    end = clock();
    double time= ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nEnqueue took %f seconds", time);

    printf("\nDequeuing...");
    start = clock();
    dequeueArr(priortyQueue, arraySize);
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nDequeue took %f seconds.", time);
}