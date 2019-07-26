/**
    牛客网多校2019年第二场
    Eddy Walker 2
**/

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=1e3+10;
const int MAXM=2060;
const int mod=1e9+7;

LL power(LL a,LL b){
    LL c=1;
    while(b){
        if (b%2==1){
            c=(c*a)%mod;
        }
        a=(a*a)%mod;
        b/=2;
    }
    return c;
}

LL n,m,invM;

struct Matrix {
    /**
        m^2 的快速矩阵乘法，适用于线性递推方程生成的矩阵
    **/
    Matrix(){
        init();
    }
    void init(){
        for(int i=1;i<m;i++) x[i]=0;
        x[0]=1;
    }
    Matrix operator * (const Matrix &mm) const
    {
        Matrix ret;
        for (int i=0;i<=2*m-2;i++) ret.x[i]=0;
        for (int i=0;i<m;i++)
            for (int j=0;j<m;j++)
                ret.x[i+j]=(ret.x[i+j]+(LL)x[i]*mm.x[j])%mod;
        for (int i=2*m-2;i>=m;i--){
            for (int j=1;j<=m;j++)
                ret.x[i-j]=(ret.x[i-j]+(LL)ret.x[i]*invM)%mod;
            ret.x[i]=0;
        }
        return ret;
    }

    LL x[MAXM];
}bas,res;

LL f[MAXM];

LL solve(LL n){
    if (m==1) return 1;
    if (n==-1){
        LL ret=2;
        ret*=power(m+1,mod-2);
        ret%=mod;
        return ret;
    }
    f[0]=1;
    for(int i=1;i<=2*m;i++){
        f[i]=0;
        for(int j=1;j<=m && i-j>=0;j++){
            f[i]=(f[i]+f[i-j])%mod;
        }
        f[i]=(f[i]*invM)%mod;
    }
    if (n<m) return f[n];
    bas.init(); bas.x[0]=0; bas.x[1]=1;
    res.init();
    for(n-=m-1;n;n/=2,bas=bas*bas){
        if (n%2==1){
            res=res*bas;
        }
    }
    LL ans=0;
    for (int i=0;i<m;i++)
        ans=(ans+res.x[i]*f[m+i-1]%mod)%mod;
    return ans;
}

//long double g[10000005];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&m,&n);
        invM=power(m,mod-2);
        LL ans=solve(n);
        printf("%lld\n",ans);
    }
    return 0;
}
