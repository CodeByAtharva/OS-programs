#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("\nChild process (PID: %d)\n", getpid());
        printf("Sorting array in parent before execve...\n");

        // Sort array in parent process before execve
        bubbleSort(arr, n);

        // Prepare arguments for execve
        char *args[n + 2]; // +2 for program name and NULL terminator
        args[0] = "./reverse.c"; // name of program to execute

        for (int i = 0; i < n; i++) {
            char *num_str = malloc(10);
            sprintf(num_str, "%d", arr[i]);
            args[i + 1] = num_str;
        }
        args[n + 1] = NULL; // execve expects NULL-terminated array

        // Execute reverse program
        execve(args[0], args, NULL);

        perror("execve failed");
        exit(1);
    } 
    else {
        // Parent process
        wait(NULL);
        printf("\nParent process (PID: %d) finished.\n", getpid());
    }

    return 0;
}


/* 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void bubbleSort(int n,int nums[]){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(nums[j]>nums[j+1]){
                int temp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
}
int main(){
    int n;
    printf("Enter the no. of elements :");
    scanf("%d",&n);
    int nums[n];
    printf("Enter the array elements :");
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    bubbleSort(n,nums);

    pid_t pid=fork();

    if(pid<0){
        printf("error occured !");
    }
    else if(pid==0){
        char* argv[n+2];
        argv[0]="./execexample";
        for(int i=0;i<n;i++){
            char* strnum=malloc(10);
            sprintf(strnum,"%d",nums[i]);
            argv[i+1]=strnum;
        }
        argv[n+1]=NULL;

        execve(argv[0],argv,NULL);

        perror("exec failed");
        exit(0);
    }
    else{
        wait(NULL);
        printf("Inside parent process ! waiting for child to finish");
    }
    return 0;
} */