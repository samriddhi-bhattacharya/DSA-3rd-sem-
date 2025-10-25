#include <stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
	}Node;
	
Node* createNode(int data) {
	Node* newNode =(Node*)malloc(sizeof(Node));
	if(!newNode) {
		printf("Memory error\n");
		return NULL;
		}
		newNode->data=data;
		newNode->next=NULL;
		return newNode;
	}
void insertAtBeginning(Node** head,int data) {
	Node* newNode=createNode(data);
	if(*head==NULL) {
		*head=newNode;
		}
	else{
		newNode->next=*head;
		*head=newNode;
	}
}
void insertAtEnd(Node** head, int data) {
	Node* newNode = createNode(data);
	if(*head ==NULL) {
	*head = newNode;
	}
	else{
		Node* temp =*head;
		while(temp->next!=NULL) {
			temp=temp->next;
			}
			temp->next=newNode;
		}
		}
	
	
void displayList(Node* head) {
	Node* temp=head;
	while(temp!=NULL) {
		printf("%d ", temp->data);
		temp=temp->next;
			}
		printf("\n");
		}
void deleteNode(Node** head, int data) {
	if(*head==NULL) return;
	
	if((*head)->data==data) {
		Node* temp= *head;
		*head =(*head)->next;
		free(temp);
		return;
		}
		Node* prev= *head;
		Node* current= (*head)->next;
		while(current!=NULL) {
			if(current->data == data) {
				prev->next = current->next;
				free(current);
				return;
				}
		prev=current;
		current=current->next;
		}
	}
void reverseList(Node** head) {
	Node* prev= NULL;
	Node* current = *head;
	Node* next = NULL;
	while(current!=NULL) {
		next = current->next;
		current->next=prev;
		prev=current;
		current=next;
		
	}
	*head = prev;
}
void sortList(Node** head) {
	Node* current=*head;
	while(current!=NULL) {
		Node* nextNode =current->next;
		while(nextNode!=NULL) {
			if(current->data > nextNode->data) {
				int temp=current->data;
				current->data = nextNode->data;
				nextNode->data = temp;
				}
				nextNode = nextNode->next;
			}
			current = current->next;
		}
	}
int main() {
	Node* head= NULL;
	int choice,data;
	
	while(1) {
		printf("Linked List Operations:\n1. Insert At Beginning\n2. Insert At End\n3. Delete Node\n4. Display List\n5. Reverse List\n6. Sort List\n7. Exit\nEnter your choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
		case 1:
			printf("Enter data to insert at beginning: ");
			scanf("%d", &data);
			insertAtBeginning(&head, data);
			break;
		case 2:
			printf("Enter data to insert at end: ");
			scanf("%d", &data);
			insertAtEnd(&head, data);
			break;
		case 3:
			printf("Enter data to delete: ");
			scanf("%d", &data);
			deleteNode(&head, data);
			break;
		case 4:
			printf("Linked List: ");
			displayList(head);
			break;
		case 5:
			reverseList(&head);
			printf("Reversed Linked List: ");
			displayList(head);
			break;
		case 6:
			sortList(&head);
			printf("Sorted Linked List: ");
			displayList(head);
			break;
		case 7:
			exit(0);
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
return 0;
}

	
				
