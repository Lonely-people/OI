#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
char ch[22000005],ch2[22000005];
int r[22000005];
int main(){
    scanf("%s",ch2);
    memset(ch,0,sizeof(ch));
    int l=strlen(ch2);
    for(int i=l-1;i>=0;i--)
        ch[i*2+1]=ch2[i];
    l=2*l+1;
    int pos=0,maxright=0;
    int ans=-1;
    for(int i=1;i<l;i++){
        r[i]=1;
        if(i<=maxright)
            r[i]=min(r[pos*2-i],maxright-i+1);
        for(int j=r[i];j<=l;j++){
            if(i-j<0||i+j>l)
                break;
            if(ch[i-j]!=ch[i+j])
                break;
            r[i]=j+1;
        }
        if(i+r[i]-1>maxright)
            maxright=i+r[i]-1,pos=i;
        ans=max(ans,r[i]-1);
    }
    cout<<ans<<endl;
    return 0;
}
