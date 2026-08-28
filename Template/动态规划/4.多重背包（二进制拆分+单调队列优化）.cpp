#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,W; cin>>n>>W;  // n物品总数，W背包最大容量
    // 二进制拆分：每件物品最多拆log2(m)份，*20保证空间足够
    vl vv(n*20+10,-1),ww(n*20+10,-1);
    ll num=0;   // num：拆分之后得到的新物品总编号

    // 二进制拆分，多重背包转01背包
    // 思路：把m件物品拆成 1,2,4,...,剩余数，若干组，每组当作一件新物品
    for(ll i=1;i<=n;i++)    
    {
        ll v,w,m;
        cin>>v>>w>>m;   // v单件价值，w单件重量，m该物品数量

        // j取1,2,4,8... 二进制分组
        for(ll j=1;j<=m;j<<=1)
        {
            num++;
            vv[num]=j*v;    // 改组总价值
            ww[num]=j*w;    // 改组总重量
            m-=j;           // 减去已经拆分出去的数量
        }
        // 剩下不足2的幂次的部分，单独作为一组
        if(m)
        {
            num++;
            vv[num]=m*v;
            ww[num]=m*w;
        }
    }
    
    // dp[j]：背包容量为j时可以装的最大价值
    vl dp(W+1,0);

    // 对拆分完成的所有物品跑01背包：倒序遍历容量
    for(ll i=1;i<=num;i++)
    {
        // 倒序，防止一件物品被多次选取
        for(ll j=W;j>=ww[i];j--)
        {
            dp[j]=max(dp[j-ww[i]]+vv[i],dp[j]);
        }
    }
    cout<<dp[W];  // 背包容量W下最大价值，输出答案
    return 0;
}
