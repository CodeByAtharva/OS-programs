#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
// #include<cmath.h>
int minIndex(int req[],int visited[],int headPos,int n){
  int minIndex=-1;
  int minDist=INT_MAX;
  for(int i=0;i<n;i++){
    if(visited[i]==0){
      int dist=abs(req[i]-headPos);
      if(dist<minDist){
        minDist=dist;
        minIndex=i;
      }
    }
  }
  return minIndex;
}
int main(){
  int totalTracks,headPos,direction,n;
  printf("Enter total no. of tracks :");
  scanf("%d",&totalTracks);
  printf("Enter the initial head position :");
  scanf("%d",&headPos);
  printf("Enter total no. of requests :");
  scanf("%d",&n);
  int req[n],visited[n],seq[n];
  printf("Enter the requests :");
  for(int i=0;i<n;i++){
    scanf("%d",&req[i]);
    visited[i]=0;
  }
  int cost=0;
  for(int i=0;i<n;i++){
    int mi=minIndex(req,visited,headPos,n);
    visited[mi]=1;
    cost+=abs(headPos-req[mi]);
    headPos=req[mi];
    seq[i]=req[mi];
  }
  for(int i=0;i<n;i++){
    printf("%d ",seq[i]);
  }
  printf("\nTotal cost : %d",cost);
  return 0;
}