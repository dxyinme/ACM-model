/**
你有四种操作：
1.往字符串的开头加一个字符
2.往字符串的结尾加一个字符
3.询问这个字符串的子串中本质不同的回文串的数量
4.询问这个字符串的子串中回文串的总数（相同的也要计算）
刚开始字符串长度是0

双端回文自动机
由于回文自动机的插入是O(1)的，所以可以借此来拓展一下回文自动机的应用范围。使其能够支持前后同时插入字符。
需要两个pos指针和两个last指针，分别左边界和右边界，last指针表示左边插入之后的最后一个节点，和右边插入之后的最后一个节点。
每个节点记录一个ca[x]表示当前节点所表示的字符串的数量。
对于询问3，我们只需要输出节点个数-2即可。
对于询问4，我们需要在插入的时候统计所有节点的ca[x]总和
当插入当前字符串之后，总串是个回文串的时候，这次插入操作的last可以被赋值给在另一个方向插入的last
**/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=200014;
const int D=27;
int m,s[MAXN];
struct dePAM{
    int cnt;
    int last[2],pos[2];
    ll sum;
    int ch[MAXN][D],len[MAXN],ca[MAXN],fa[MAXN];
    int create(int Len,int Fa){
        len[cnt]=Len;
        fa[cnt]=Fa;
        return cnt++;
    }
    void CLEAR(){
        for(int i=0;i<cnt;i++){
            len[i]=0;ca[i]=0;fa[i]=0;
            memset(ch[i],0,sizeof(ch[i]));
        }
        memset(s,-1,sizeof(s));
        last[0]=0;last[1]=0;
        pos[0]=m;pos[1]=m-1;
        cnt=0;sum=0;
        create(0,1);
        create(-1,0);
    }
    int getfail(int p,int n,int op){
        int g=-1;if(!op)g=1;
        for(;s[n+g*(len[p]+1)]!=s[n];p=fa[p]);
        return p;
    }
    int add(int c,int op){
        if(!op){
            s[--pos[op]]=c;
        }
        else{
            s[++pos[op]]=c;
        }
        int p=getfail(last[op],pos[op],op);
        if(!ch[p][c]){
            int nt=create(len[p]+2,ch[getfail(fa[p],pos[op],op)][c]);
            ca[nt]=ca[fa[nt]]+1;
            ch[p][c]=nt;
        }
        last[op]=ch[p][c];
        if(pos[1]-pos[0]+1==len[last[op]])last[op^1]=last[op];
        sum+=ca[last[op]];
        return last[op];
    }
}pam;

int w33ha(){
    pam.CLEAR();
    while(m--){
        int op;
        char ch[4];
        scanf("%d",&op);
        if(op<=2){
            scanf("%s",ch+1);
            pam.add(ch[1]-'a',op-1);
        }
        else if(op==3){
            printf("%d\n",pam.cnt-2);
        }
        else{
            printf("%lld\n",pam.sum);
        }
    }
    return 0;
}

int main(){
    while(scanf("%d",&m)!=EOF)w33ha();
    return 0;
}