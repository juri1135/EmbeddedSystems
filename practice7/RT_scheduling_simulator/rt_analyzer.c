#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TASK 100
#define INT_MAX 0x7FFFFFFF
#define INPUT_FILE_NAME "sched_param_rc.txt"
struct Task {
    char name[16];
    int ID;
    int releaseTime;
    int period;
    int executionTime;
    int deadline;    
    int priority;       
    int remainingTime;
    int responseTime;
} task[MAX_TASK];
int taskCount = 0;
//ready queue (val is next release time per task)
int nextRelease[MAX_TASK];
int schedule = 1;
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
        fscanf(f, "%d ", &task[i].releaseTime);
		fscanf(f, "%d ", &task[i].period);
		fscanf(f, "%d ", &task[i].executionTime);
		fscanf(f, "%d ", &task[i].deadline);
		fscanf(f, "%d \n", &task[i].priority);
        task[i].responseTime = 0;
        taskCount++;
	}

	for (i = 0; i<taskCount; i++) {
		printf("Task %s: ", task[i].name);
        printf("Release time = %d, ",task[i].releaseTime);
		printf("Period = %d, ", task[i].period);
		printf("Execution time = %d, ", task[i].executionTime);
		printf("Deadline = %d, ", task[i].deadline);
		printf("Priority = %d, \n", task[i].priority);
	}

	printf("\n");

	return taskCount;
}

float checkSchedulable() {
    float util = 0;
    // total utilization
    for (int i = 0; i < taskCount; i++) {
        util += (float)task[i].executionTime / task[i].period;
    }
    return util;
}

void simulate() {
     // long term scheduler에 의해 ready 상태로 들어와... ready가 되려면 처음 release + period*n일 때
    //n을 다 따로 계산하기 애매하니까 구조체에 추가,, deadline도 추가,, 
   // short term scheduler에 의해 ready queue에 있는 애들 중 우선순위가 젤 높은 애를 cpu에 보내
   // cpu에서 실행하다가 deadline되면 다시 초기 memory 상으로 돌아가서 다음 release까지 기다려 
   // 주기적으로 ready queue에서 대기하는 애들의 deadline이 현재 time을 안 넘겼는지 확인해야 함 
   // cpu 뺏길 때마다 done 여부 체크하고 remainTime 계산해줘야 함 
    //모든 task가 종료되면 done. 엥 근데 종료 시점이 뭐지? 모르겠음. 
    // response time은 period 기준 response time이라서 진짜 종료가 아님,, 그럼 진짜 종료 기준이 뭐지 while 조건을 어케 잡아야 할까요

    int time = 0;
    

    // initialization 
    for (int i = 0; i < taskCount; i++) {
        task[i].remainingTime = task[i].executionTime;
        nextRelease[i] = task[i].releaseTime;
    }
    int minPriorityTask = -1;
    while (time < 1000000000) { 
        // check deadline. if time > nextDeadline then task[i] missed deadline
        for (int i = 0; i < taskCount; i++) {
            if (time > nextRelease[i]+ task[i].deadline && task[i].remainingTime > 0) {
                printf("Task %s missed deadline: time %d.\n", task[i].name, time);
                schedule = 0;
                printf("Duration of Simulation is %d\n", time);
                return; 
            }
        }

        // check readyQueue 
        
        for (int i = 0; i < taskCount; i++) {
            if (time >= nextRelease[i] && task[i].remainingTime > 0) {
		// check task[i] priority 
		// if min==-1 any task doesn't holds cpu. 
		// if task's priority holds cpu lower than task[i]'s priority => task[i] preempts cpu 
                if (minPriorityTask == -1 || task[i].priority < task[minPriorityTask].priority) {
                    minPriorityTask = i;
                }
            }
        }

        // if any task does't holds cpu => skip and time goes on 
        if (minPriorityTask == -1) {
            time++;
            continue;
        }

        // if any task holds cpu => that task's remainTime reduced
        task[minPriorityTask].remainingTime--;

        // if that task's remainTime==0 => initialization 
        if (task[minPriorityTask].remainingTime == 0) {
            nextRelease[minPriorityTask] += task[minPriorityTask].period; 
            task[minPriorityTask].remainingTime = task[minPriorityTask].executionTime; 
	    minPriorityTask=-1;
	}

        
        time++;
    }

    printf("\nDuration of Simulation is %d\n", time);
}

int main() {
    readInput();
    
    simulate();
    float utilization=checkSchedulable();
    float maxutil=taskCount*(pow(2.0,(1.0/taskCount))-1);
    //utilization<= m(2^(1/m)-1) m: # of tasks
   if(utilization>maxutil||schedule==0) printf("\nThe total utilization is %.6f and the task set is NOT schedulable.\n",utilization);
   else printf("The total utilization is %.6f and the task set is schedulable.\n",utilization);
}
