#include<stdio.h>
#include<stdlib.h>
void bfs(int **graph,int n,int start,int *visited){
    int *queue=(int *)malloc(n*sizeof(int));
    int front=0,rear=0;
    queue[rear++]=start;
    visited[start]=1;
    while(front<rear){
        int curr=queue[front++];
        printf("%d ",curr);
        for(int i=0;i<n;i++){
            if(graph[curr][i]==1 && !visited[i]){
                queue[rear++]=i;
                visited[i]=1;
            }
        }
    }
    free(queue);
}
int main(){
    int n;
    printf("Enter no. of vertices : ");
    scanf("%d",&n);
    int **graph=(int **)malloc(n*sizeof(int *));
    for(int i=0;i<n;i++){
        graph[i]=(int *)malloc(n*sizeof(int));
    }
    printf("Enter adjacent matrix of order %d X %d : \n",n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }
    int *visited=(int*)calloc(n,sizeof(n));
    int start;
    printf("Enter the start point(0-%d) : ",n-1);
    scanf("%d",&start);
    printf("BFS Transversal : ");
    bfs(graph,n,start,visited);
    free(visited);
    for(int i=0;i<n;i++){
        free(graph[i]);
    }
    free(graph);
    return 0;
}
