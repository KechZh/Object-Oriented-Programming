#include<bits/stdc++.h>
using namespace std;
typedef struct link{
    int capacity;
    int load;
    double cost;
}link;
typedef struct flow{
    int start,end;
    int size;
    vector<int> path;
}flow;
int node_n,link_n,flow_n;
vector<int> accept;
int total=0;
int Map[1000][1000];
link L[1000];
flow F[1000];
void debug(){
    int i,j;
    for(i=0;i<node_n;i++)
        for(j=0;j<node_n;j++){
            if(j<node_n-1)
                printf("%d ",Map[i][j]);
            else
                printf("%d\n",Map[i][j]);
        }
    for(i=0;i<link_n;i++)
        printf("%d %d %lf\n",L[i].capacity,L[i].load,L[i].cost);
}
int check(int n,int parent[]){
    int now=F[n].end;
    while(now!=F[n].start){
        int edge=Map[now][parent[now]];
        if(L[edge].load+F[n].size>L[edge].capacity)
            return 0;
        now=parent[now];
    }
    return 1;
}
void find_path(int n,int parent[]){
    int stack[1000];
    int top=0;
    int now=F[n].end;
    while(now!=F[n].start){
        stack[top++]=now;
        now=parent[now];
    }
    stack[top]=F[n].start;
    while(top>=0)
        F[n].path.push_back(stack[top--]);
}
void update(int n,int parent[]){
    int now=F[n].end;
    while(now!=F[n].start){
        int edge=Map[now][parent[now]];
        L[edge].load+=F[n].size;
        if(L[edge].capacity-L[edge].load>0)
            L[edge].cost=(double)L[edge].load/(double)(L[edge].capacity-L[edge].load);
        else
            L[edge].cost=DBL_MAX;
        now=parent[now];
    }
}
void shortest_path(int n){
    double D[1000];
    int parent[1000]={0};
    queue<int> q;
    int i;
    for(i=0;i<1000;i++)
        D[i]=DBL_MAX;
    q.push(F[n].start);
    D[F[n].start]=0;
    while(!q.empty()){
        int now=q.front();
        for(i=0;i<node_n;i++)
            if(Map[now][i]>=0&&D[now]+L[Map[now][i]].cost<D[i]){
                D[i]=D[now]+L[Map[now][i]].cost;
                parent[i]=now;
                q.push(i);
            }
        q.pop();
    }
    if(check(n,parent)){
        accept.push_back(n);
        total+=F[n].size;
        find_path(n,parent);
        update(n,parent);
    }
}
int main(){
    freopen("request.txt","r",stdin);
    freopen("result.txt","w",stdout);
    int n1,n2;
    int i,j;
    scanf("%d%d",&node_n,&link_n);
    memset(Map,-1,sizeof(Map));
    for(i=0;i<link_n;i++){
        scanf("%d%d%d%d",&i,&n1,&n2,&L[i].capacity);
        L[i].load=0;
        L[i].cost=0;
        Map[n1][n2]=Map[n2][n1]=i;
    }
    scanf("%d",&flow_n);
    for(i=0;i<flow_n;i++){
        scanf("%d%d%d%d",&i,&F[i].start,&F[i].end,&F[i].size);
        shortest_path(i);
    }
    printf("%d %d\n",accept.size(),total);
    for(i=0;i<accept.size();i++){
        int now=accept[i];
        printf("%d ",now);
        for(j=0;j<F[now].path.size();j++){
            if(j<F[now].path.size()-1)
                printf("%d ",F[now].path[j]);
            else
                printf("%d\n",F[now].path[j]);
        }
    }
    return 0;
}
