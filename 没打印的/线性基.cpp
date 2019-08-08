#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct LinearBasis{
    int sz,cnt;
    ll bs[74],p[74];
    set<int>num;
    LinearBasis(int Sz=63){
        sz=Sz;cnt=0;
        memset(p,0,sizeof(p));
        memset(bs,0,sizeof(bs));
        num.clear();
    }
    bool ins(ll x,int sit){ // 插入
        for(ll i=sz-1,bin=(1LL<<(sz-1));i>=0;i--,bin>>=1){
            if(x&bin){
                if(!bs[i]){
                    bs[i]=x;
                    num.insert(sit);
                    break;
                }
                x^=bs[i];
            }
        }
        return x>0;
    }
    /**
        如果要验证一个数字是否属于这个线性空间的话，只需要将这个数字插入线性基，
        如果返回false，则这个数字存在，否则不存在。
    **/
    ll getmax(){ // 获取线性异或空间内的最大值
        ll res=0;
        for(ll i=sz-1;i>=0;i--){
            if((res^bs[i])>res)res^=bs[i];
        }
        return res;
    }
    ll getmin(){ // 获取线性异或空间内的最小值
        for(ll i=0;i<sz;i++){
            if(bs[i])return bs[i];
        }
        return 0;
    }
    void rebuild(){ // 重构线性基，用于查询第k小
        for(int i=sz-1;i>=0;i--)
            for(int j=i-1;j>=0;j--)
                if(bs[i]&(1LL<<j))bs[i]^=bs[j];
        for(int i=0;i<sz;i++)
        if(bs[i])p[cnt++]=bs[i];
    }
    ll getK(ll k){// 获取线性异或空间中第k小的值
        ll ret=0;
        if(k>=(1LL<<cnt))return -1;
        for(int i=sz-1;i>=0;i--)
            if(k&(1LL<<i))ret^=p[i];
        return ret;
    }
};
// 合并两个基底
LinearBasis Merge(const LinearBasis &n1,const LinearBasis &n2){
    LinearBasis ret=n1;
    for(int i=n2.sz-1;i>=0;i--)
        if(n2.bs[i])ret.ins(n2.bs[i],i);
    return ret;
}

// 线性基求交集
LinearBasis Inter(LinearBasis n1,LinearBasis n2){
    LinearBasis a=n2,b=n2;
    LinearBasis ret=LinearBasis();
    for(int i=0;i<n1.sz;i++){
        if(!n1.bs[i])continue;
        ll temp=0,x=n1.bs[i];
        int j;
        for(j=i;j>=0;j--){
            if(x&(1LL<<j)){
                if(a.bs[j]){
                    x^=a.bs[j];
                    temp^=b.bs[j];
                }
                else break;
            }
        }
        if(x==0)ret.bs[i]=temp;
        else{
            a.bs[j]=x;
            b.bs[j]=temp;
        }
    }
    return ret;
}
int main(){

    return 0;
}
