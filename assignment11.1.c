#include<stdio.h>
#include<stdlib.h>
void dfs(int **graph,int n,int start,int *visited){
    printf("%d ",start);
    visited[start]=1;
    for(int i=0;i<n;i++){
        if(graph[start][i]==1 && !visited[i])
            dfs(graph,n,i,visited);
    }
}
int main(){
    int n;
    printf("ENTER NUMBER OF VERTICES : ");
    scanf("%d",&n);
    int **graph=(int **)malloc(n*sizeof(int *));
    for(int i=0;i<n;i++){
        graph[i]=(int *)malloc(n*sizeof(int));
    }
    printf("ENTER ADJACENT MATRIX OF ORDER %d X %d\n ",n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
    }
    }
    int *visited=(int *)calloc(n,sizeof(int));
    int start;
    printf("Enter starting vertex (0-%d) : ",n-1);
    scanf("%d",&start);
    printf("DFS Transversal");
    dfs(graph,n,start,visited);
    free(visited);
    for(int i=0;i<n;i++){
        free(graph[i]);
    }
    free(graph);
    return 0;
}

