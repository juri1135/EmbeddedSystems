#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 1024                  // Mximum number of elements
#define INPUT_FILE_NAME "input_matrix.txt"     // Input file containing input data to sort (+ the number of elements)
int resultArray[INPUT_MAX][INPUT_MAX];
// Read input data from a file and write the data into buffer
int readInput(int inputData[][INPUT_MAX], int *rowSize, int *columnSize)
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
	fscanf(fd, "%d x %d", rowSize, columnSize);
    if (*rowSize > INPUT_MAX||*columnSize >INPUT_MAX) {
        printf("The number of elements exceeds the limit %d.\n", INPUT_MAX);
        return -1;
    }
    printf("%d %d\n",*rowSize,*columnSize);
	for (i = 0; i < *rowSize; i++) {
        for(int k=0; k<*columnSize; k++){
		    fscanf(fd, "%d ", &inputData[i][k]);
        }
    }
    return 1;
}
void swap(int* a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void generateMatrixTranspose(int rowSize, int columnSize, int matrix[][INPUT_MAX]){
    for (int i = 0; i < rowSize; i++) {
        
        for(int k=0; k<columnSize; k++){
		    resultArray[i][k]=matrix[k][i];
        }
    }
}
int main(){
    int dataArray[INPUT_MAX][INPUT_MAX];
    
    int rowSize, columnSize;
    int check=readInput(dataArray,&rowSize,&columnSize);
    for (int i = 0; i < rowSize; i++) {
        for(int k=0; k<columnSize; k++){
		    printf("%d  ",dataArray[i][k]);
        }
        printf("\n");
    }
    printf("\n");
    swap(&rowSize,&columnSize);
    generateMatrixTranspose(rowSize,columnSize,dataArray);
    for (int i = 0; i < rowSize; i++) {
        for(int k=0; k<columnSize; k++){
		    printf("%d  ",resultArray[i][k]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}