#include<cstdio>
#define INF 0x3f3f3f3f
#define maxn 3000001
#define _min(a, b) a < b ? a : b
#define _max(a, b) a > b ? a : b
#define _abs(a) a < 0 ? -a : a
#define cmax(a, b) (a > b) && (a = b)
#define cmin(a, b) (a < b) && (a = b)
inline int read(){
    int r=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        r=r*10+c-'0';
        c=getchar();
    }
    return r*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}
struct edge{
    int v,c,nxt;
}e[2*maxn];
    int S,T,N,head[maxn],q[maxn],cur[maxn],level[maxn],tot=0,hd,tl,v;
    inline void init(int s,int t,int n){
        S=s;
        T=t;
        N=n+1;
        for(register int i=1;i<N;i++)
            head[i]=-1;
    }
    inline void add_edge(int u,int v,int c){
        e[tot]=(edge){v,c,head[u]};
        head[u]=tot++;
    } 
    inline void add(int u,int v,int c){
        add_edge(u,v,c);
        add_edge(v,u,0);
    }
    inline bool BFS(){
        for(register int i=1;i<N;i++){
            cur[i]=head[i];
            level[i]=0;
        }
        q[1]=S;
        level[S]=1;
        hd=0;tl=1;
        while(hd^tl){
            hd++;
            for(register int i=head[q[hd]];i!=-1;i=e[i].nxt){
                if(e[i].c&&!level[e[i].v]){
                    tl++;
                    level[e[i].v]=level[q[hd]]+1;
                    q[tl]=e[i].v;
                    if(e[i].v==T)return true;
                }
            }
        }
        return false;
    }
    inline int min(int a,int b){
        if(a<b)return a;
        return b;
    }
    int DFS(int f,int u){
        if(u==T)return f;
        int d=0,used=0;
        for(int &i=cur[u];i!=-1;i=e[i].nxt){
            if(e[i].c&&level[u]==level[e[i].v]-1){
                if((d=DFS(min(f-used,e[i].c),e[i].v))){
                    e[i].c-=d;
                    e[i^1].c+=d;
                    used+=d;
                }
            }
        }
        if(!used)level[u]=0;
        return used;
    }
    inline int Dinic(){
        int max_flow=0;
        while(BFS()){
            int d=0;
            while((d=DFS(INF,S)))
                max_flow+=d;
        }
        return max_flow;
    }

int main(){
    int n=read(),m=read(),s=read(),t=read(),i;
    init(s,t,n);
    for(i=1;i<=m;i++){
        int a=read(),b=read(),v=read();
        add(a,b,v);
    }
    int ans=Dinic();
    write(ans);
    return 0;
}
