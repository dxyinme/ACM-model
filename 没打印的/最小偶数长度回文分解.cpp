#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int INF=1e9;
const int MAXN=1000004;
char s[MAXN];
struct PAT{
    int cnt,last;
    int ch[MAXN][26],len[MAXN],fa[MAXN],sz[MAXN];
    int slk[MAXN],diff[MAXN];
    int fp[MAXN];
    int create(int Len,int Fa){
        fa[cnt]=Fa;
        len[cnt]=Len;
        return cnt++;
    }
    void CLEAR(){
        for(int i=0;i<cnt;i++){
            fa[i]=0;len[i]=0;sz[i]=0;
            slk[i]=0;diff[i]=0;
            memset(ch[i],0,sizeof(ch[i]));
        }
        last=0;cnt=0;
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
            int nt=create(len[p]+2,ch[getfail(fa[p],pos)][c]);
            ch[p][c]=nt;
            diff[nt]=len[nt]-len[fa[nt]];
            slk[nt]=((diff[nt]==diff[fa[nt]])?slk[fa[nt]]:fa[nt]);
        }
        last=ch[p][c];
        return last;
    }
	
	/**
	对于字符串s，询问其最少能被表示成多少个偶数长度的回文串拼接的结果。
	dp[i]记录s[1...i]的答案，pre[i]记录dp[i]的转移前驱。
	pre[i] , i 为贡献答案的一个回文串。
	*/
    void solve(int l,int *dp,int *pre){
        for(int i=0;i<=l;i++){
            pre[i]=0;
            dp[i]=INF;
        }
        CLEAR();
        dp[0]=0;
        fp[0]=1;
        for(int i=1;i<=l;i++){
            for(int j=add(s[i]-'a',i);j;j=slk[j]){
                fp[j]=i-len[slk[j]]-diff[j];
                if(diff[j]==diff[fa[j]]&&dp[fp[j]]>dp[fp[fa[j]]]){
                    fp[j]=fp[fa[j]];
                }
                if(i%2==0&&dp[i]>dp[fp[j]]+1){
                    dp[i]=dp[fp[j]]+1;
                    pre[i]=fp[j];
                }
            }
            if(i%2==0&&s[i-1]==s[i]&&dp[i]>=dp[i-2]){
                dp[i]=dp[i-2];
                pre[i]=i-2;
            }
        }
    }
}pat;

/**
下方不重要...
*/

char ss[MAXN];
int dp[MAXN],pre[MAXN];
int main(){
    int n;
    scanf("%s",ss+1);
    n=strlen(ss+1);
    n<<=1;
    for(int i=1;i<=n;i+=2)s[i]=ss[i/2+1];
    scanf("%s",ss+1);
    for(int i=2;i<=n;i+=2)s[i]=ss[i/2];
    pat.solve(n,dp,pre);
    if(dp[n]>n)return puts("-1"),0;
    else printf("%d\n",dp[n]);
    for(int i=n;i;i=pre[i]){
        if(i-pre[i]>2)printf("%d %d\n",pre[i]/2+1,i/2);
    }
    return 0;
}
