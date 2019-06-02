#include<iostream>
#include<cstring>
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)<(b)?(b):(a))
using namespace std;
const long long MAXN=10,mo=1e9+7;

struct matrix{
    public:
        matrix(int han,int lin){
            h=han,l=lin;
            memset(v,0,sizeof(v));  
        }
        
        matrix(){
            memset(v,0,sizeof(v));          
        }
        
        void cleanForPow(void){
            memset(v,0,sizeof(v));
            int p=min(h,l);
            for(int i=1;i<=p;++i){
                v[i][i]=1;
            }
        }
        
        friend matrix operator *(matrix a,matrix b){
            matrix c(a.h,b.l);
            if(a.l!=b.h)return c;
            
            for(int i=1;i<=a.h;++i){
                for(int j=1;j<=b.l;++j){
                    long long s=0;
                    for(int k=1;k<=a.l;++k){
                        s=s%mo+(a.v[i][k]*b.v[k][j]%mo);
                    }
                    c.v[i][j]=s;
                }
            }
            return c;
        }
        
        matrix pow(int k){
            matrix res=*this;
            matrix ret(h,l);
            ret.cleanForPow();
            while(k){
                if(k&1){
                    ret=ret*res;
                }
                res=res*res;
                k>>=1;
            }
            return ret;
        }
        
        void setV(long long t[MAXN][MAXN]){
            for(int i=1;i<=h;++i){
                for(int j=1;j<=l;++j){
                    v[i][j]=t[i][j];
                }
            }
        }
        long long v[MAXN][MAXN];
        
    private:
        int h,l;
        
};

int main(void){
    int T;
    cin>>T;
    long long tmp[MAXN][MAXN]={{0},{0,2,1,1,1}};
    long long tmp2[MAXN][MAXN]={
        {0},
        {0,1,1,0,0},
        {0,0,0,1,0},
        {0,1,0,0,1},
        {0,0,0,0,0}
    };
    matrix a(1,4);
    matrix b(4,4);
    a.setV(tmp);
    b.setV(tmp2);
    while(T--){
        int n;
        cin>>n;
        if(n<=3) {cout<<"1\n";continue;}
        matrix ans=a*b.pow(n-4);
        cout<<ans.v[1][1]<<'\n';
    }
    return 0;
}
