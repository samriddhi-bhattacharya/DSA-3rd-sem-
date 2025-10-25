#include<stdio.h>
#include<stdlib.h>

void enqueue(int *arr, int *rear,int *val) 
{
	arr[++*rear]=*val;
	printf("%d inserted\n",*val);
}

void dequeue(int *arr, int *front)
{
	int a;
	a=arr[++*front];
	printf("%d deleted\n",a);
}
void disp(int *arr, int *rear, int *front)
{
	if(*rear==*front)
		printf("queue is empty\n");
	else {
		for(int i=*front+1;i<=*rear;i++) 
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	     }
}
int main()
{
	int n=1,rear=-1,front=-1;
	int *arr=(int*)malloc(n*sizeof(int));
	while(1)
	{
		int choice;
		printf("Press 1 to insert\nPress 2 to delete\nPress 3 to display\nPress 4 to exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				int val;
				printf("Enter value ->\n");
				scanf("%d",&val);
				enqueue(arr,&rear,&val);
			}
			n+=1;
			arr=realloc(arr,n*sizeof(int));
			break;
			
			case 2:
				dequeue(arr,&front);
				break;
			case 3:
				disp(arr,&rear,&front);
				break;
			
			case 4:
				return 0;
				
			default:
				printf("INVALID CHOICE\n");
				break;
		}
	}
	free(arr);
	return 0;
}
