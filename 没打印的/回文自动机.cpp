#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=300004;
const int D=27;
char s[300004];
int n;
struct PAM{
    int last,cnt;
    int fa[MAXN],sz[MAXN],len[MAXN],ch[MAXN][D];
    int create(int Len,int Fa){
        len[cnt]=Len;
        fa[cnt]=Fa;
        return cnt++;
    }
    void CLEAR(){
        for(int i=0;i<cnt;i++){
            fa[i]=0;sz[i]=0;len[i]=0;
            memset(ch[i],0,sizeof(ch[i]));
        }
        cnt=0;
        last=0;
        create(0,1);
        create(-1,0);
    }
    int getfail(int p,int n){
        for(;s[n-len[p]-1]!=s[n];p=fa[p]);
        return p;
    }
    int add(int c,int pos){
        int p=getfail(last,pos);
        if(!ch[p][c]){
            ch[p][c]=create(len[p]+2,ch[getfail(fa[p],pos)][c]);
        }
        last=ch[p][c];
        sz[last]++;
        return last;
    }
    ll getans(){
        ll res=0;
        for(int i=cnt-1;i>=2;i--){
            sz[fa[i]]+=sz[i];
            /**
                这里需要将每种串的出现次数统计清楚。
            **/
        }
        for(int i=cnt-1;i>=2;i--){
            res=max(res,1LL*sz[i]*len[i]);
        }
        return res;
    }
}pam;
int w33ha(){
    n=strlen(s+1);
    pam.CLEAR();
    for(int i=1;i<=n;i++){
        pam.add(s[i]-'a',i);
    }
    printf("%lld\n",pam.getans());
}
int main(){
    while(scanf("%s",s+1)!=EOF)w33ha();
    return 0;
}
