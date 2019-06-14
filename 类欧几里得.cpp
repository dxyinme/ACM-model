#include<bits/stdc++.h>
#define LiangJiaJun main
#define ll long long
using namespace std;

/**
º∆À„
for(int i=0;i<=n;i++) ans += floor( (a*i + b) / c )
*/
ll f(ll a,ll b,ll c,ll n){
    if(a==0){
        return (b/c)*(n+1);
    }
    if(a>=c||b>=c){
        if(n&1){
            return f(a%c,b%c,c,n)+(a/c)*(n+1)/2*(n)+(b/c)*(n+1);
        }
        else{
            return f(a%c,b%c,c,n)+(a/c)*(n)/2*(n+1)+(b/c)*(n+1);
        }
    }
    else{
        ll m=(a*n+b)/c;
        return (m*n)-f(c,c-b-1,a,m-1);
    }
}

ll a,b,c,n;

int LiangJiaJun(){

}
