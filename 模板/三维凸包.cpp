#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
typedef double ld;
char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int bb;ld aa,ee;ld F(){
    while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),isd(ch))aa=aa*10+ch-'0';ee=1;
    if(ch=='.')while(ch=getc(),isd(ch))aa+=(ch-'0')*(ee*=0.1);return bb?aa:-aa;
}
ld G(){
    return (rand()-(1<<30))/1e21;
}
int n,i,j,t[3],vis[2010][2010],now,las,tmp;ld ans;
struct P{ld x,y,z;}p[2010];
#define PP const P&
P operator-(PP a,PP b){return (P){a.x-b.x,a.y-b.y,a.z-b.z};}
P operator&(PP a,PP b){return (P){a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
ld operator|(PP a,PP b){return a.x*b.x+a.y*b.y+a.z*b.z;}
ld len(PP a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}
#define ck(a,b,c) ((b-a)&(c-a))
struct Sfc{
    int a,b,c;P s;
    void up(int x,int y,int z){
        a=x,b=y,c=z,s=ck(p[x],p[y],p[z]);
    }
}q[2][3010];
#define see(i,f) ((f.s|(p[i]-p[f.a]))>0)
#define ns q[las][j]
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++)p[i]=(P){F()+G(),F()+G(),F()+G()};
    for(q[1][++t[1]].up(1,2,3),q[1][++t[1]].up(3,2,1),i=4;i<=n;i++){
        now=i&1,las=now^1,t[now]=0;
        for(j=1;j<=t[las];j++){
            if(tmp=see(i,ns),!tmp)q[now][++t[now]]=ns;
            vis[ns.a][ns.b]=vis[ns.b][ns.c]=vis[ns.c][ns.a]=tmp;
        }
        for(j=1;j<=t[las];j++){
            if(vis[ns.a][ns.b]&&!vis[ns.b][ns.a])q[now][++t[now]].up(ns.a,ns.b,i);
            if(vis[ns.b][ns.c]&&!vis[ns.c][ns.b])q[now][++t[now]].up(ns.b,ns.c,i);
            if(vis[ns.c][ns.a]&&!vis[ns.a][ns.c])q[now][++t[now]].up(ns.c,ns.a,i);
        }
    }
    for(now=n&1,i=1;i<=t[now];i++)ans+=len(q[now][i].s);
    printf("%.3lf\n",ans*0.5);
}
