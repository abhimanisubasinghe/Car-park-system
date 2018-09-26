#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX 10

int count = 0;

struct park_stack{
	struct park_stack *next;
	char data[10];
	int x;
};

struct park_stack *top = NULL;

void push(char num[],int x){
	
	struct park_stack *ptr;
	ptr = (struct park_stack*)malloc(sizeof(struct park_stack));
	strcpy(ptr -> data,num);
	ptr -> x = x;

	if( top == NULL ){
		ptr -> next = NULL;
		top = ptr;
	}
	else{
		ptr -> next = top;
		top = ptr;
	}

}

void display_stack(){

	printf("\nStack order:\n");
	struct park_stack *ptr;
	ptr = top;
	while( ptr -> next != NULL){
		printf("%s\n",ptr -> data);
		ptr = ptr ->  next;
	}
	printf("%s\n",ptr -> data);

}

struct park_stack *pop(){

	struct park_stack *ptr;
	char num[10];

	ptr = top;

	strcpy(num,ptr -> data);

	if ( top == NULL ){
		printf("error");
	} 
	else{
		top = top -> next;
	}
	printf("\n%s will be deleted from stack\n",ptr -> data);
	return ptr;
}

struct garage_queue{
	struct garage_queue *next;
	char data[10];
	int x;
};

struct waiting_queue{
	struct waiting_queue *next;
	char data[10];
	int x;
};

struct garage_queue *front = NULL;
struct garage_queue *rear = NULL;

int arrival(char num[]){

	struct garage_queue *ptr;
	int flag = 0;
	ptr = (struct garage_queue*)malloc(sizeof(struct garage_queue));

	strcpy(ptr -> data,num);

	if( count == MAX ){
		printf("\nPark is full.\n");
		flag = 0;
	}
	else{
		ptr -> x = 1;
		flag = 1;
		if( front == NULL ){
			ptr -> next = NULL;
			front = rear = ptr;
		}
		else{
						
			rear -> next = ptr;
			ptr -> next = NULL;
			rear = ptr;
		}
		printf("%s has arrived to the park",rear -> data);
		count++;
	}	
	return flag;

}

void display(){

	struct garage_queue *ptr;
 	int i=1;

	ptr = front;

	if (front == NULL){
		printf("\nGarage is empty\n");
	}
	else{

		printf("\nVehicle order in the garage\n");

		while(ptr -> next != NULL){
			printf("%d %s\n",i,ptr -> data);
			ptr = ptr -> next;
			i++;
		} 
		printf("%d %s",i,ptr -> data);
	}	

}

struct garage_queue * out_garage(struct garage_queue *front){
	
	struct garage_queue *ptr;
	char num[10];
	int x;

	ptr = front;

	if( front == NULL ){
		printf("\nGarage is empty\n");
	}
	else{
		front = front -> next;
		strcpy(num,ptr -> data);
		x = ptr -> x;
		push(num,x);
		free(ptr);
	}
	return front;
}

struct garage_queue * in_garage(struct park_stack *top){

	struct garage_queue *ptr;
	int y;

	ptr = (struct garage_queue*)malloc(sizeof(struct garage_queue));

	strcpy(ptr -> data,top -> data);
	y = top -> x;
	y++;
	ptr -> x = y;

	if( front == NULL ){
		ptr -> next = NULL;
		front = rear = ptr;
	} 
	else{
		ptr -> next = front;
		front = ptr;
	}

	return front;

}

struct waiting_queue *wfront =NULL;
struct waiting_queue *wrear =NULL;

void in_waiting(char num[]){

	struct waiting_queue *ptr;

	ptr = (struct waiting_queue*)malloc(sizeof(struct waiting_queue));
	strcpy(ptr -> data, num);
	ptr -> x = 0;

	if( wfront == NULL ){
		ptr -> next = NULL;
		wrear = wfront = ptr;
	}
	else{
		wrear -> next = ptr;
		ptr -> next = NULL;
		wrear = ptr;
	} 

}

struct waiting_queue * out_waiting(){

	struct waiting_queue *ptr;
	char num[10];

	ptr = wfront;

	strcpy(num,ptr->data);

	if( wfront == NULL){
		printf("\nThere aren't any cars waiting.\n");
	}
	else{
		printf("\n%s will be removed from the waiting list\n",wfront -> data);
		wfront = wfront -> next;
	}
	return ptr;

}

void display_waiting(){

	struct waiting_queue *ptr;
 	int i=1;

	ptr = wfront;

	if (wfront == NULL){
		printf("\nThere aren't any cars waiting\n");
	}
	else{

		printf("\nVehicle order in the waiting list\n");

		while(ptr -> next != NULL){
			printf("%d %s\n",i,ptr -> data);
			ptr = ptr -> next;
			i++;
		} 
		printf("%d %s",i,ptr -> data);
	}	

}


int main(){
	
	int option,i,check;
	char num[10];
	struct garage_queue *ptr;
	struct park_stack *preptr;
	struct waiting_queue *wptr;
	int pos = 0;

	printf("\nMAIN MENUE\n");
	printf("1. ARRIVAL\n");
	printf("2. DEPARTURE\n");
	printf("3. DISPLAY\n");
	printf("4. DISPLAY WAITING LIST\n");
	printf("5. EXIT\n");

	do{
		printf("\nEnter your option : ");
		scanf("%d",&option);

		switch(option){
			case 1: 
				
				printf("Insert vehicle plate : ");
				scanf("%s",num);
				check = arrival(num);
				if ( check == 0 ){
					in_waiting(num);
				}
				check =0;
				break;
			
			case 2:
				pos = 0;
				printf("\nEnter the vehicle number to be departed : ");
				scanf("%s",num);

				ptr = front;

				while( strcmp(ptr -> data,num) != 0 ){
					front = out_garage(front);
					ptr = front;
					pos++;
				}
				front = out_garage(front);
				pos++;
				printf("\n%s will be departed from the garage from %d position\n",num,pos);
				display_stack();
				display();
				for( i=1; i<=pos; ){
					if(i==1){
						preptr = pop();
						printf("\n%s departed from the garage. It has been moved %d times.\n",preptr -> data,preptr -> x);
						i++;
					}
					else{
						preptr = pop();
						front = in_garage(preptr);
						i++;
					}
				}
				printf("\nGarage has been relocated\n");
				count--;
				printf("\nThere are space to %d cars\n",MAX - count);
				if( wfront == NULL ){
					printf("\nThere aren't any cars waiting\n");
				}
				else{
					wptr = out_waiting();
					strcpy(num,wptr -> data);
					check = arrival(num);
				}
				
				break;
			
			case 3:
				display();
				break;
			case 4:
				display_waiting();
				break;
			case 5: 
				break;
			default:
				printf("Enter a valid option\n");
				break;
		}

	}while( option != 5 );

	return 0;
}
