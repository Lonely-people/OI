#include<bits/stdc++.h>
#define N 3000010
typedef long long ll;
using namespace std;
int inv[N],n,p;
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
int main(){
    n=read();p=read();inv[1]=1;puts("1");
    for(int i=2;i<=n;i++){
        inv[i]=(ll)(p-p/i)*inv[p%i]%p;
        printf("%d\n",inv[i]);
    }
}
