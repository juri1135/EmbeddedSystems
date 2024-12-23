#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 1024                  // Mximum number of elements
#define INPUT_FILE_NAME "input_array_stack.txt"     // Input file containing input data to sort (+ the number of elements)

int resultArray[INPUT_MAX];
int idx=0;
// Read input data from a file and write the data into buffer
void push(int item){
    resultArray[idx++]=item;
}
int pop(){
    return resultArray[--idx];
}
int main()
{ 
    FILE* fd;    
    int dataTotal; 
    int i;
    
    fd = fopen(INPUT_FILE_NAME, "r");
	if (fd == NULL)	{
		printf("Error: Failed to open '%s'.\n", INPUT_FILE_NAME);
		return -1;
	}
    
	/* read input file to get task parameters */
	fscanf(fd, "%d \n", &dataTotal);
    

	for (i = 0; i < dataTotal; i++) {
    	char inpu[10];
        fscanf(fd, "%s ",inpu);
        if(!strcmp(inpu,"push")){
            int data;
            fscanf(fd, "%d", &data);
            push(data);
        }
        else{
            int top=pop();
        }
    }
    printf("The remaining elements in the stack: ");
    int index=idx;
   for(int i=0; i<index; i++){
    printf("%d ",pop());
   }
   printf("\n");
    return 0;
}

