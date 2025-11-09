#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
typedef struct{
  int pid;
  int at,bt,ct,tat,wt,rt,rbt;
  int isStarted;
} Process;
int takeInput(Process p[]){
  int n;
  printf("Enter no. of processes :");
  scanf("%d",&n);

  for(int i=0;i<n;i++){
    printf("Process  p%d:\n\n",i);

    printf("Enter Arrival Time :");
    scanf("%d",&p[i].at);

    printf("Enter burst Time :");
    scanf("%d",&p[i].bt);
    p[i].rbt=p[i].bt;

    p[i].ct=p[i].tat=p[i].wt=p[i].rt=0;

    p[i].isStarted=0;

  }
  return n;
}
void SJF(Process p[],int n){
  int done=0;
  int time=0;
  while(done<n){
    int shortestProcess=-1;
    int shortestTime=1e9;
    for(int i=0;i<n;i++){
      if(p[i].at<=time && p[i].rbt>0){
        if(p[i].rbt<shortestTime){
          shortestTime=p[i].rbt;
          shortestProcess=i;
        }
      }
    }

    if(shortestProcess==-1){
      time++;
      continue;
    }
    if(p[shortestProcess].isStarted==0){
      p[shortestProcess].isStarted=1;
      p[shortestProcess].rt=time-p[shortestProcess].at;
    }
    time++;
    p[shortestProcess].rbt--;

    if(p[shortestProcess].rbt==0){
      p[shortestProcess].ct=time;
      p[shortestProcess].tat=time-p[shortestProcess].at;
      p[shortestProcess].wt=p[shortestProcess].tat-p[shortestProcess].bt;
      done++;
    }
  }
}
void roundRobin(Process p[],int n,int tq){
  int time=0;
  int done=0;
  while(done<n){
    int progress=0;
    for(int i=0;i<n;i++){
      if(p[i].at<=time && p[i].rbt>0){
        if(p[i].isStarted==0){
          p[i].isStarted=1;
          p[i].rt=time-p[i].at;
        }

        int exec=(p[i].rbt>tq)?tq:p[i].rbt;
        time+=exec;
        p[i].rbt-=exec;
        progress=1;

        if(p[i].rbt==0){
          p[i].ct=time;
          p[i].tat=p[i].ct-p[i].at;
          p[i].wt=p[i].tat-p[i].bt;
          done++;
        }
      }
    }
    if(progress==0){
      time++;
    }
  }
}
void RoundRobin(Process p[], int n, int tq) {
    int time = 0, done = 0;

    while (done < n) {
        int progress = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].rbt > 0 && p[i].at <= time) {
                if (!p[i].isStarted) {
                    p[i].rt = time - p[i].at;
                    p[i].isStarted = 1;
                }

                int exec = (p[i].rbt > tq) ? tq : p[i].rbt;
                p[i].rbt -= exec;
                time += exec;
                progress = 1;

                if (p[i].rbt == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
        if (!progress) time++; // CPU idle
    }
}
void printOutput(Process p[],int n){
  int avgwt=0,avgtat=0,avgct=0;
  printf("process  |  AT  |  BT  |  CT  |  TAT  |  WT   |  RT   |\n");
  for(int i=0;i<n;i++){
  printf("  p%d    |  %d  |  %d  |  %d  |  %d   |  %d   |  %d   |\n",i,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    avgwt+=p[i].wt;
    avgtat+=p[i].tat;
    avgct+=p[i].ct;
  }
  printf("Average waiting time : %f",(avgwt/(float)n));
  printf("Average TAT time : %f",(avgtat/(float)n));
  printf("Average CT time : %f",(avgct/(float)n));
}
int main(){
  int n;
  Process p[20];
  n=takeInput(p);
  int tq;
  printf("Enter the time quantum :");
  scanf("%d",&tq);

  RoundRobin(p,n,tq);

  printOutput(p,n);
}
