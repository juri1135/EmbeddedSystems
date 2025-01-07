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
// curRes를 매번 새로 계산해서 업데이트해야 하는데 누적합으로 계산해서 오류...
int checkResponse(int k, int prev){
    int carry;
    int totalInterference = 0;
        for(int i=0; i<taskCount; i++){
            carry=0;
            if(task[i].priority<task[k].priority){
                float sigma = ceil((float)prev / task[i].period);
                carry = sigma* task[i].executionTime;
                totalInterference += carry;
                
                // printf("carry %d\n",carry);
                // printf("k is %d and i is %d\n",task[k].priority,task[i].priority);
            }
        }
        task[k].responseTime = task[k].executionTime + totalInterference;
        // deadline 어긋나면 종료 조건을 여기서 걸면 maximum response time 계산을 못 하고 중간에 멈춤춤
        // if(task[k].responseTime>task[k].deadline) return -1;

        // 이미 수행한 연산이면 종료
        if (task[k].responseTime == prev) return 0;
        // 그 외는 재귀적으로 넘어가야 함,, 여기서의 prev는 현재 계산한 결과값값 
        else return checkResponse(k, task[k].responseTime);
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
   // 근데 이 response time를 재귀적으로 계산해야 함 i번 째를 계산하기 위해 i번 째가 필요하고, 이 과정에서 i가 업데이트됨
   // 업데이트된 i번 째와 바로 직전 호출했을 때의 response time이 동일하면 재귀 종료
   //Initialization
   for(int i=0; i<taskCount; i++) task[i].responseTime=task[i].executionTime;
   for(int i=0; i<taskCount; i++){
    checkResponse(i,task[i].executionTime);
       if(task[i].responseTime>task[i].deadline) printf("Task %s might miss deadline: response time %d > deadline %d\n",task[i].name,task[i].responseTime,task[i].deadline);
    }
    float utilization=checkSchedulable();
    float maxutil=taskCount*(pow(2.0,(1.0/taskCount))-1);
    //utilization<= m(2^(1/m)-1) m: # of tasks
   if(utilization>maxutil) printf("\nThe total utilization is %.6f and the task set is NOT schedulable.\n",utilization);
   else printf("The total utilization is %.6f and the task set is schedulable.\n",utilization);
}

