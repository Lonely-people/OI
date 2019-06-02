#include <cstdio>
#include <iostream>
using namespace std;
long long x[999][999];
long long ans[999][999];
long long dx[999][999];
const int p=1e9+7;
void ans_cf(int n)
{
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      dx[i][j]=ans[i][j],ans[i][j]=0;

    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      for(int k=1;k<=n;k++)
       ans[i][j]=(ans[i][j]+(x[i][k]*dx[k][j])%p)%p;
}
void x_cf(int n)
{
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      dx[i][j]=x[i][j],x[i][j]=0;

    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      for(int k=1;k<=n;k++)
       x[i][j]=(x[i][j]+(dx[i][k]*dx[k][j])%p)%p;
}
void fast_pow(long long n,long long w)
{
    while(w)
    {
        if(w%2==1) ans_cf(n);
        w/=2;
        x_cf(n);
    }
}
int main()
{
    long long n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      scanf("%d",&x[i][j]),ans[i][j]=x[i][j];
    fast_pow(n,k-1);

    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
       printf("%lld ",ans[i][j]);
      puts("");
    }

}
