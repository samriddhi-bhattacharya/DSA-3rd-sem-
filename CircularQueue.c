#include <stdio.h>
#include <stdlib.h>

void enqueue(int *arr, int *rear, int *front, int val, int n)
{
	if ((*front == 0 && *rear == n - 1) || (*rear + 1) % n == *front)
	{
		printf("Queue is overflow\n");
		return;
	}

	if (*front == -1 && *rear == -1)
	{
		*front = *rear = 0;
		arr[*rear] = val;
	}
	else
	{
		*rear = (*rear + 1) % n;
		arr[*rear] = val;
	}
	printf("%d inserted\n", val);
}

void dequeue(int *arr, int *rear, int *front, int n)
{
	if (*front == -1 && *rear == -1)
	{
		printf("Queue is underflow\n");
		return;
	}

	int deleted = arr[*front];

	if (*front == *rear)
	{
		*front = *rear = -1;
	}
	else
	{
		*front = (*front + 1) % n;
	}
	printf("%d deleted\n", deleted);
}

void disp(int *arr, int *rear, int *front, int n)
{
	if (*front == -1 && *rear == -1)
	{
		printf("Queue is empty\n");
		return;
	}

	printf("Queue elements: ");
	int i = *front;
	while (1)
	{
		printf("%d ", arr[i]);
		if (i == *rear)
			break;
		i = (i + 1) % n;
	}
	printf("\n");
}

int main()
{
	int n, rear = -1, front = -1;
	printf("Enter the size of array-> ");
	scanf("%d", &n);

	int *arr = (int *)malloc(n * sizeof(int));

	while (1)
	{
		int choice;
		printf("\nPress 1 to insert\tPress 2 to delete\tPress 3 to display\tPress 4 to exit\n");
		printf("Enter your choice-> ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
		{
			int val;
			printf("Enter the value-> ");
			scanf("%d", &val);
			enqueue(arr, &rear, &front, val, n);
			break;
		}
		case 2:
			dequeue(arr, &rear, &front, n);
			break;
		case 3:
			disp(arr, &rear, &front, n);
			break;
		case 4:
			free(arr);
			return 0;
		default:
			printf("Invalid choice\n");
		}
	}
}
