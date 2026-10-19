/*
题目：洛谷 P10468 兔子与兔子
算法标签：字符串哈希、前缀哈希、自然溢出哈希、O(1)子串查询
题目大意：
给定一个字符串，m次询问。每次询问给出两组区间 [l1,r1]、[l2,r2]
判断这两个区间对应的子串是否完全相同。
字符串下标从1开始，区分大小写。

算法思路：
采用前缀哈希（多项式哈希）。
1. 定义哈希公式：h[i] 代表原串 s[1~i] 的哈希值
   h[i] = h[i-1] * P + s[i]
   P是基数，这里取131；ULL(unsigned long long)自动对2^64取模（自然溢出）
2. 预处理幂数组 p，p[i]=P^i，用于区间哈希换算
3. 子串 s[l~r] 的哈希公式：h[l,r] = h[r] - h[l-1] * p[r-l+1]
   原理：h[r] = h[l-1] * P^{r-l+1} + s[l]P^{r-l}+...+s[r]
   减去 h[l-1] * P^{r-l+1}，就只剩下 s[l]~s[r] 的哈希
4. 每次询问，直接算出两个子串哈希，哈希相等则子串相等（极小概率碰撞）
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
using pi=pair<int,int>;
using pl=pair<ll,ll>;
using ULL=unsigned long long; //自然溢出哈希类型

const int N=1e6+5; //字符串最大长度
const int P=131;   //哈希基数，常用131/13331
ULL p[N],h[N];     //p:幂数组 p[i]=P^i; h:前缀哈希数组 h[i] s[1~i]哈希
int n,m;
string s;

void init()
{
    p[0]=1;h[0]=0; //边界：P^0=1，空串哈希h[0]=0
    for(int i=1;i<=n;i++)
    {
        p[i]=p[i-1]*P; //递推求P的i次方
        h[i]=h[i-1]*P+s[i]; //递推前缀哈希
    }
}

//获取子串 s[l~r] 的哈希值，l,r下标从1开始
ULL get(int l,int r)
{
    return h[r]-h[l-1]*p[r-l+1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); //关闭同步，加速cin
    
    cin>>s;
    s=' '+s; //在字符串前面补空格，让原字符串下标从1开始，方便公式计算
    n=s.size()-1; //⚠️注意：s现在首字符是空格，真实长度要减1
    init(); //预处理幂数组和前缀哈希
    
    cin>>m;
    while(m--)
    {
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        //比较两个子串哈希值
        if(get(l1,r1)==get(l2,r2))  cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
