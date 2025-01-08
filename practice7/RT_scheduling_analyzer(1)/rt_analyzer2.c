#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// math.h는 표준 수학 함수 헤더 파일이지만 libm이라는 별도의 라이브러리를 링크해야 사용 가능
// Make file에서 컴파일 명령어에 wiringPi 라이브러리랑 같이 -lm 추가해주면 됨 
#define MAX_TASK 100
#define INT_MAX 0x7FFFFFFF

#define INPUT_FILE_NAME "sched_param.txt"

struct Task {
    char name[16];
    int ID;
    int period;
    int executionTime;
    int deadline;    
    int priority;       
    
    int responseTime;
} task[MAX_TASK];

int taskCount = 0;
int readInput()
{
    FILE *f;
    int i;
    char temp;

    f = fopen(INPUT_FILE_NAME, "r");
	if (f == NULL) {
		printf("Error: Failed to open %s.\n", INPUT_FILE_NAME);
		return -1;
	}

	/* Read input file to get task parameters */
	fscanf(f, "%c ", &temp);

	for (i = 0; i<MAX_TASK; i++) {
		fscanf(f, "%s ", task[i].name);
		if (task[i].name[0] == '$') {
            fclose(f);
            break;
		}

		task[i].ID = i;
		fscanf(f, "%d ", &task[i].period);
		fscanf(f, "%d ", &task[i].executionTime);
		fscanf(f, "%d ", &task[i].deadline);
		fscanf(f, "%d \n", &task[i].priority);
        task[i].responseTime = 0;
        taskCount++;
	}

	for (i = 0; i<taskCount; i++) {
		printf("Task %s: ", task[i].name);
		printf("Period = %d, ", task[i].period);
		printf("Execution time = %d, ", task[i].executionTime);
		printf("Deadline = %d, ", task[i].deadline);
		printf("Priority = %d, \n", task[i].priority);
	}

	printf("\n");

	return taskCount;
}
//여기 계산하는 로직이 이상한듯 수정해야 함
// 이게 안 되는 이유는,, deadline에 의해 계속 task들이 중간에 중단되고, 다른 task로 넘어갔다가 다시 실행하러 오는 등
// 계속 실행시간이 바뀌기 때문... 
void checkResponse(int k, int prev){
    int curRes=task[k].executionTime;
    int carry;
    for(int i=0; i<taskCount; i++){
        carry=0;
        if(task[i].priority<task[k].priority){
            float c=ceil((double)prev/task[i].period);
            carry=c*task[i].executionTime;
            curRes+=carry;
            printf("carry: %d\n",carry);
        }
    }
    printf("curRes: %d\n",curRes);
    task[k].responseTime=curRes;
}
float checkSchedulable(){
    float util=0;
    // total utilization 
    for(int i=0; i<taskCount; i++){
	    util+=(float)task[i].executionTime/task[i].period;
    }
    return util;
}
int main(){
   readInput();
   //response time=ith execution time + sigma(ceil(ith response time /jth period )* jth execution time )(j has higher priority than ith task)
   // 만약 우선 순위가 높은 순서대로 정렬해서 계산하면 
   //Initialization
   int initRes=0;
   for(int i=0; i<taskCount; i++) initRes+=task[i].executionTime;
//    printf("0th res time: %d\n",initRes);
   for(int i=0; i<taskCount; i++){
    checkResponse(i,initRes);
       if(task[i].responseTime>task[i].deadline) printf("Task %s might miss deadline: response time %d > deadline %d\n",task[i].name,task[i].responseTime,task[i].deadline);
    }
    float utilization=checkSchedulable();
    float maxutil=taskCount*(pow(2.0,(1.0/taskCount))-1);
    //utilization<= m(2^(1/m)-1) m: # of tasks
   if(utilization>maxutil) printf("\nThe total utilization is %.6f and the task set is NOT schedulable.\n",utilization);
   else printf("The total utilization is %.6f and the task set is schedulable.\n",utilization);
}

