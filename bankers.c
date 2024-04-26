#include<stdio.h>
#include <stdbool.h>
int allocMatrix[10][10], maxMatrix[10][10], needMatrix[10][10];
int availMatrix[10];
int numProcsess, numResources;

// takes input from terminal and saves it into a 2-d matrix
void readMatrix(int matrix[10][10]) {
    for (int i = 0; i<numProcsess; i++) {
        for (int j=0; j<numResources; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// print out matrix passed to it
void displayMatrix(int matrix[10][10]) {

    for(int i = 0; i < numProcsess; i++) {
        printf("\n P%d", i);                                                                   // Prints out process number
        for(int j=0; j < numResources; j++) {
            printf(" %d", matrix[i][j]);
        }
    }
}

void calculateNeed() {
    for(int i = 0; i < numProcsess; i++) {
        for(int j = 0; j < numResources; j++) {
            needMatrix[i][j] = maxMatrix[i][j] - allocMatrix[i][j];
        }
    }
}

void banker() {
    int finish[10], safeSequence[10];
    int flag;
    int k = 0;
    int j, i;
    for (i = 0; i < numProcsess; i++) {
        finish[i] = 0;
    }
    for (i = 0; i < numProcsess; i++) {
        flag = 0;
        if (finish[i] == 0) {                                                                   // if process is incomplete, then execute it
            for (j = 0; j < numResources; j++) {                                                // checking if need of each process is greater than available
                if (needMatrix[i][j] > availMatrix[j]) {
                    flag = 1;                                                                   // not enough resources available for the process to be able to execute so we break out of the loop and move to the next process
                    break;
                }
            }
            if (flag == 0) {                                                                    // if a process made it to this point that means its need is less than available so we are able to complete process
                finish[i] = 1;                                                                  // finish array value is set to one to symbolize it is complete
                safeSequence[k] = i;                                                            // i symbolizes the PID
                k++;                                                                            // move to the next safe sequence

                for (j = 0; j < numResources; j++) {                                            // adds the allocated resources of the finished process to available 
                    availMatrix[j] += allocMatrix[i][j];
                }                                    

                i = -1;                                                                         // start back at the first process
            }
        }
    }
    flag = 0;
    for (i = 0; i < numProcsess; i++) {
        if (finish[i] == 0) {                                                                   // if we got to this point with all processes incomplete, that means resources are stuck
            printf("\n OS is in deadlock");
            flag = 1;
            break;
        }
    }   
    if (flag == 0 ) {                                                                           // if we got to this point that means all processes are complete, which means all resources were made available to all processes
        printf("\n Yes, the system is in a safe state. \n The safe sequence is:");              // resulting in a safe state
        for (i = 0; i < numProcsess; i++) {
            printf(" P%d", safeSequence[i]);
        }
    }
}

int main() {
    int j;

    // this block will receive input from the user
    {
        printf("\nEnter number of processes");
        scanf("%d", &numProcsess);
        printf("\nEnter number of resources");
        scanf("%d", &numResources);
        printf("\nEnter initial allocation matrix:");
        readMatrix(allocMatrix);
        printf("\nEnter Max requirement matrix:");
        readMatrix(maxMatrix);
        printf("\n Enter available resources: ");
        for(j=0; j<numResources;j++) {
            scanf("%d", &availMatrix[j]);
        }
    }

    // displays data entered by user
    {
        printf("\n =======Entered Data=======\n\n");
        printf("\n Initial Allocation:\n");
        displayMatrix(allocMatrix);
        printf("\n Maximum Requirement:\n");
        displayMatrix(maxMatrix);
        printf("\nAvailable Resources\n");
        for(j=0; j<numResources;j++) {
            printf(" %d", availMatrix[j]);
        }
    }

    // calculates need matrix
    {
        calculateNeed();
        printf("\n\n\n Need is \n");
        displayMatrix(needMatrix);
    }

    // executes bankers algorithm
    banker();
    return 0;
}
