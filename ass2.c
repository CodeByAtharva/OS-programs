#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void bubbleSort(int nums[],int n){
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
void merge(int nums[],int left,int mid,int right){
  int m=mid-left+1;
  int n=right-mid;
  int lnums[m];
  int rnums[n];
  int k=left;

  for(int i=0;i<m;i++){
    lnums[i]=nums[k];
    k++;
  }
  for(int i=0;i<n;i++){
    rnums[i]=nums[k];
    k++;
  }
  int i=0;
  int j=0;
  k=left;
  while(i<m && j<n){
    if(lnums[i]<rnums[j]){
      nums[k]=lnums[i];
      i++;
    }
    else{
      nums[k]=rnums[j];
      j++;
    }
    k++;
  }
  while(i<m){
    nums[k]=lnums[i];
    i++;
    k++;
  }
  while(j<n){
    nums[k]=rnums[j];
    j++;
    k++;
  }
}
void mergeSort(int nums[],int left,int right){
  if(left<right){
    int mid=(left+right)/2;
    mergeSort(nums,left,mid);
    mergeSort(nums,mid+1,right);
    merge(nums,left,mid,right);
  }
}
void printNums(int nums[],int n){
  printf("Sorted array :");
  for(int i=0;i<n;i++){
    printf("%d ",nums[i]);
  }
  printf("\n");
}
int main(){
  int n;
  printf("Enter no. of elements in array :");
  scanf("%d",&n);
  printf("Enter the array elements :");
  int nums[n];
  for(int i=0;i<n;i++){
    scanf("%d",&nums[i]);
  }

  pid_t pid=fork();
  
  if(pid<0){
    printf("Something went wrong !");
  }
  else if(pid==0){
    printf("inside the child process pid:%d\n",getpid());
    bubbleSort(nums,n);
    printNums(nums,n);
  }
  else{
    printf("Inside the parent process process id :%d\n",getpid());
    printf("Waiting for child to execute !");
    wait(NULL);
    mergeSort(nums,0,n-1);
    printNums(nums,n);
    
  }
  return 0;
}