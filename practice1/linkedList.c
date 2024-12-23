#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 1024                  // Mximum number of elements
#define INPUT_FILE_NAME "input_linked_list_stack.txt"     // Input file containing input data to sort (+ the number of elements)

typedef struct Node{
    int data;
    struct Node* next;
}Node;
Node* Head=NULL;
// Read input data from a file and write the data into buffer
// using only head node. double linked list(prev, next), control both head and tail etc...
void push(int item){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->data=item;
    newNode->next=Head;
    Head=newNode;
}
int pop(){
    Node* temp=Head;
    int data=Head->data;
    Head=Head->next;
    
    free(temp);
    return data;
}
int main()
{   printf("hello");
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
    while(Head!=NULL){
        printf("%d ",pop());
    }
   printf("\n");
    return 0;
}

