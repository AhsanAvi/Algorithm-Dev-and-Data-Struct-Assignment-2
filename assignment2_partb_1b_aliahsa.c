/** 
 * • Name: Ahsan Ali (aliahsa)
 * • Assignment: Assignment 2, Part 2 1B
 * • Date: October 10, 2020
 * 
 * • This program creates a min-heap in a priorityQueue
 * which has (almost)full functionality of enqueue and dequeuing
 * Dequeue has minor issues where it does not downheap correctly after each dequeue
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void dequeueArr(int priority[], int size) {
    int dqArr[size], temp= 0;
    
    FILE *file = fopen("dequeued.txt", "w"); 
    //open the dequeue text file to store dequeued numbers
    if (file == NULL) { //if the file is not opened exit
        printf("Cannot Open File");
        exit(1);
    }

    for (int counter = 1; counter < size; counter++) {
        dqArr[counter] = priority[1];
        //storing min number in dqarray to print to the file later
        priority[1] = priority[size-counter];
        //set last non zero number in the heap to 1
        priority[size-counter] = 0;
        //make last non zero number = 0

        for (int i = 1; i>0;) {
            //for the element (index=counter) enqueued into the heap; do below
            if (priority[i] > priority[i*2] &&
                  priority[i*2] < priority[i*2+1] && priority[i*2] != 0) {
            //tried to compare which of the two children are smaller, so that the
            //correct if statement can be used, but this is where the program fails
            //it does not take the correct if statement depending on which child is smaller
                temp = priority[i];
                priority[i] = priority[i*2];
                priority[i*2] = temp;
                i=i*2;
                //traverse children
            } 
            if (priority[i] > priority[i*2+1] &&
                  priority[i*2+1] < priority[i*2] && priority[i*2+1] != 0) {
                    temp = priority[i];
                    priority[i] = priority[i*2+1];
                    priority[i*2+1] = temp;
                    i = i*2+1;
                    //traverse children
                }
            else { 
                i = 0;
                //when there are no more comparisons needed, stop.
            } 
        }
    }

    for (int i = 1; i < size; i++){
        fprintf(file, "%d ", dqArr[i]);
    } 
    //storing dequeued elements into file
    fclose(file);
}

void enqueueArr(int unSorted[], int size) {
     int counter=0, temp, buffer[300];
     //counter is used to keep track of how many elements are
     //enqueued into the unsorted array
     
     FILE *file = fopen("test_dat.txt", "r"); 
     //open the file and read from it
        if (file == NULL) {
            //if the file is not opened exit
            printf("Cannot Open File");
            exit(1); 
        }
    
    while (!feof(file) && counter < (size-1)) {
    //if file is not end of file, and if 0 and < the size of the array-1
    //this is used to choose how many elements can actually fit into the unsorted array
        fgets(buffer, 300, file);   //gets the whole file as a string
        unSorted[counter+1] = atoi(buffer); //converting string to int and storing into array
        counter++;
        //++ to keep track of the next element being enqueued
        if (feof(file)) { 
            break; //exiting the loop after EOF is read
        }
    }
    fclose(file);
}

void buildHeap(int unSorted[], int priority[], int size) {
    int temp = 0;

    for (int counter = 1; counter < size; counter++) {
    //counter (basically an i) will keep track of the element in the unsorted array
        priority[counter] = unSorted[counter];
        //appending unsorted array to heap one by one within the for loop
        for (int i = counter; i > 1;) {
            //for the element (index=counter) enqueued into the heap; do below
            
            if (priority[i] < priority[i/2]) { 
                temp = priority[i];            
                priority[i] = priority[i/2];   
                priority[i/2] = temp;          
                i = i/2;                       
            } /*if the element just enqueued is smaller than its parent
              / then swap and continue to up heap */
            else { 
                i = 0;
            } 
        }
    }  
}




int main(void) {
    int arraySize = 100;
    int priorityQueue[arraySize];
    int unsortedArr[arraySize];
    clock_t start;
    clock_t end;

    printf("upheaping..\n");
    enqueueArr(unsortedArr,arraySize);
    start = clock();
    buildHeap(unsortedArr, priorityQueue, arraySize);
    end = clock();
    double time= ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nupheap took %f seconds", time);

    printf("\nDequeuing...\n");
    start = clock();
    dequeueArr(priorityQueue, arraySize);
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nDequeue took %f seconds.", time);
    

}