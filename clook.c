#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
void sort(int n,int nums[]){
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
  int n,head,totalTracks;
  printf("Enter the total no. of tracks :");
  scanf("%d",&totalTracks);
  printf("Enter the total no. of requests :");
  scanf("%d",&n);
  int req[n],seq[n];
  printf("Enter the request array :");
  for(int i=0;i<n;i++){
    scanf("%d",&req[i]);
  }
  printf("Enter the initial head position :");
  scanf("%d",&head);

  sort(n,req);
  printf("\n");
  for(int i=0;i<n;i++){
    printf("%d  ",req[i]);
  }
  printf("\n");
  int pos=0;
  for(int i=0;i<n;i++){
    if(req[i]>=head){
      pos=i;
      break;
    }
  }
  int cost=0;
  int curr=head;
  int index=0;
  for(int i=pos;i<n;i++){
    cost+=abs(curr-req[i]);
    curr=req[i];
    seq[index++]=req[i];
  }
  if(head>req[0]){
    cost+=abs(req[n-1]-req[0]);
    curr=req[0];
    seq[index++]=req[0];

    for(int i=1;i<pos;i++){
      cost+=abs(curr-req[i]);
      curr=req[i];
      seq[index++]=req[i];
    }
  }
  printf("\nTotal Cost :%d\n",cost);
  for(int i=0;i<n;i++){
    printf("%d  ",seq[i]);
  }
  
}