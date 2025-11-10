#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
void sort(int req[],int n){
  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-i-1;j++){
      if(req[j]>req[j+1]){
        int temp=req[j];
        req[j]=req[j+1];
        req[j+1]=temp;
      }
    }
  }
}
int main(){
  int totalTracks,head,n;
  printf("Enter total no. of tracks :");
  scanf("%d",&totalTracks);
  printf("Enter total no. of requests :");
  scanf("%d",&n);
  int req[n],seq[n];
  printf("Enter the request array :");
  for(int i=0;i<n;i++){
    scanf("%d",&req[i]);
  }
  printf("Enter initial head position :");
  scanf("%d",&head);
  sort(req,n);
  int pos;
  for(int i=0;i<n;i++){
    if(req[i]>=head){
      pos=i;
      break;
    }
  }
  int curr=head;
  int cost=0;
  int index=0;
  for(int i=pos;i<n;i++){
    cost+=abs(req[i]-curr);
    seq[index++]=req[i];
    curr=req[i];
  }
  if(curr!=totalTracks-1){
    cost+=abs(curr-(totalTracks-1));
    curr=totalTracks-1;
  }
  for(int i=pos-1;i>=0;i--){
    cost+=abs(curr-req[i]);
    curr=req[i];
    seq[index++]=req[i];
  }

  printf("\nTotal Cost :%d\n",cost);
  for(int i=0;i<n;i++){
    printf("%d ",seq[i]);
  }
  return 0;
}