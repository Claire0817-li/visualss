/*
算法标签：博弈论、威佐夫博弈 Wythoff Game 洛谷 P2252
题意：两堆石子，两种取法：任选一堆拿任意颗 / 两堆同时拿相同颗数，拿光石子获胜
威佐夫必败奇异局势判定公式：
设 x <= y，差值 d = y - x，黄金分割比 phi = (sqrt(5)+1)/2
k = floor(d * phi)
如果 k == x，当前是必败态，先手输出 0；否则先手必胜，输出 1
坑点：大数(1e9)下必须用 long double 保证浮点精度，double 容易舍入错误WA
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
using ULL=unsigned long long;

// 打表代码，仅用于小范围找奇异局势，无法处理1e9大数据
// int dp[101][101];
// void test()
// {
//     dp[0][0]=0;
//     for(int i=0;i<=101;i++)
//     {
//         for(int j=0;j<=101;j++)
//         {
//             bool ok=0;
//             for(int k=0;k<i;k++)    if(!dp[k][j]) ok=true;
//             for(int k=0;k<j;k++)    if(!dp[i][k]) ok=true;
//             int lim=min(i,j);
//             for(int t=1;t<=lim;t++) if(!dp[i-t][j-t]) ok=true;
//             dp[i][j]=ok;
//         }
//     }
//     for(int i=1;i<=100;i++)
//     {
//         for(int j=i+1;j<=100;j++)
//         {
//             if(!dp[i][j])    cout<<i<<','<<j<<'\n';
//         }
//     }
// }
ll a,b;
const long double phi=(sqrtl(5.0)+1.0)/2.0; // 黄金分割，long double高精度

void solve()
{
    cin>>a>>b;
    if(a<b) swap(a,b); // 交换后保证 a >= b，b是较小的那一堆
    ll d=a-b;          // 两堆石子差值
    ll k=(ll)(d*phi);  // 向下取整得到奇异局势的下界
    if(b==k) cout<<"0\n"; // 匹配必败态，先手输
    else cout<<"1\n";    // 先手可以走到必败态，先手赢
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    while(t--)
    {
        solve();
    }
    // test();
    return 0;
}
