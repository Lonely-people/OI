#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=1e6+5;

char s[N];
int n,m;
int tax[N],tp[N],rnk[N],sa[N];

inline void Qsort()
{
    for(int i=1;i<=m;++i)
        tax[i]=0;
    for(int i=1;i<=n;++i)
        ++tax[rnk[i]];
    for(int i=1;i<=m;++i)
        tax[i]+=tax[i-1];
    for(int i=n;i>=1;--i)
        sa[tax[rnk[tp[i]]]--]=tp[i];
}

inline void Suffix_Sort()
{
    n=strlen(s+1),m='z';
    for(int i=1;i<=n;++i)
        rnk[i]=s[i],tp[i]=i;
    Qsort();
    for(int l=1,p=0;p<n;m=p,l<<=1)
    {
        p=0;
        for(int i=n-l+1;i<=n;++i)
            tp[++p]=i;
        for(int i=1;i<=n;++i)
            if(sa[i]>l)
                tp[++p]=sa[i]-l;
        Qsort();
        swap(rnk,tp);
        rnk[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rnk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+l]==tp[sa[i-1]+l])?p:++p;
    }
    for(int i=1;i<=n;++i)
        cout<<sa[i]<<' ';
}

int main()
{
    scanf("%s",s+1);
    Suffix_Sort();
    return 0;
}
