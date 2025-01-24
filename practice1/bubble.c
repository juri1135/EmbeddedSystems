#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 1024                  // Mximum number of elements
#define INPUT_FILE_NAME "input_sort.txt"     // Input file containing input data to sort (+ the number of elements)

// Read input data from a file and write the data into buffer
int readInput(int* buffer)
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
    if (dataTotal > INPUT_MAX) {
        printf("The number of elements exceeds the limit %d.\n", INPUT_MAX);
        return -1;
    }

	for (i = 0; i < dataTotal; i++) {
		fscanf(fd, "%d ", &buffer[i]);
    }
   
    return dataTotal;
}
void swapVariables(int* a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void bubbleSort(int dataTotal, int* dataArray){
    int change=1;
    while(change!=0){
        change=0;
        for(int k=0; k<dataTotal-1; k++){
            if(dataArray[k]>dataArray[k+1]){
                swapVariables(&dataArray[k],&dataArray[k+1]);
                change=1;
            }
        }
    }
}
int main(){
    int dataArray[INPUT_MAX];
    int dataTotal=readInput(dataArray);
    bubbleSort(dataTotal,dataArray);
    for(int i=0; i<dataTotal; i++){
        printf("%d ",dataArray[i]);
    }
    printf("\n");
    return 0;
}