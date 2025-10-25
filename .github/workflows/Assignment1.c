#include<stdio.h>
int main() {
	int arr[10]={39,45,26,90,34};
	for(int i=0;i<5;i++) 
		{
   	 		printf("%d ", arr[i]);
   	 	}
   	int x;
   	printf("\n1. LINEAR SEARCH\n2. INSERTION\n3.DELETION");
   	scanf("%d", &x);
   	switch(x) 
   	{
   		case 1:
		int val;
		int a=0;
		printf("\nEnter any number to search: \n");
		scanf("%d", &val);
			for(int j=0;j<10;j++) 
				{
    				if(val==arr[j]) 
    					{
       			 		printf("number found at %d ",j);
        			 	a++;
       				 	break;
       					}
     				}
				if(a==0) 
				{
      				printf("number not in list\n");
     			 	}
     			 	break;
       		case 2:
       		int value,pos;	
       		printf("Enter value to insert: \n");
       		scanf("%d", &value);
       		printf("Enter position to insert at: \n");
       		scanf("%d", &pos);
       			int arr2[6];
       			arr2[pos]=value;
       			int z=0;
       			for(int k=0;k<pos;k++)
       			{
       				arr2[k]=arr[z];
       				z++;
       			}
       			for(int k=pos+1;k<6;k++)
       			{
       				arr2[k]=arr[z];
       				z++;
       			}
       			
       			for(int i=0;i<6;i++)
       			{
       				printf("%d ",arr2[i]);
       			}
       			break;
       		case 3:
       		int num;
       		int p;
       		int c=0;
       		printf("Enter value to delete\n");
       		scanf("%d", &num);
       		printf("enter position to delete\n ");
       		scanf("%d", &p);
       			for(int i=p;i<10;i++) 
       			{
       				if(num==arr[i])
       				{
       					arr[i]=arr[i+1];
       					c++;
       				}
       			}
       				if(c==1)
       					printf("DELETION SUCCESSFUL\n");
       				else
       					printf("ERROR\n");
       		for(int m=0;m<10;m++)
       		{
       			printf("%d ",arr[m]);
       		}
       		break;
       	}		
       					
       		
       		
       					
 return 0;
 }
     
