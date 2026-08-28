/*
题目：炮兵阵地（状态压缩DP）
洛谷 P2704 [NOI2001]炮兵阵地
题目背景：
司令部的将军们打算在N*M的网格地图上部署他们的炮兵部队。
一个N*M的地图由N行M列组成，地图的每一格可能是山地（用"H" 表示），
也可能是平原（用"P"表示），在山地不能部署炮兵。
炮兵攻击范围：横向左右两格，纵向上下两格。
求整个地图最多能够摆放多少炮兵。

核心思路：状态压缩DP
1. m不大，把每一行炮兵摆放状态压缩成二进制mask，1代表放炮兵，0不放。
2. 合法行状态：同一行不能有两个炮兵距离<=2，也就是mask中不能相邻、隔一位也不能有1。
   条件： !(i & (i>>1))  不能左右相邻
         !(i & (i>>2))  不能隔一个位置放
3. dp[i][cur][pre] : 处理到第i行，第i行状态是a[cur]，第i‑1行状态是a[pre]，最多炮兵数量
   因为炮兵会攻击上下两行，所以转移的时候要看 i,i‑1,i‑2 三行状态互相不能冲突。
4. a数组：预先筛出所有单行合法mask；num数组记录每个mask里面1的个数（炮兵数量）
5. g[i]：第i行地形，二进制，1代表平原P，可以放炮兵；mask & g[i]==mask 代表该状态可以放在i行
*/
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

    int n,m;
    cin>>n>>m;

    // g[i] 记录第i行地形，二进制位为1表示该处是平原P，可以放炮兵
    vi g(n+5,0);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char c; cin>>c;
            if(c=='P') 
            {
                // j列对应二进制第j‑1位，置1代表平原
                g[i]|=(1<<(j-1));
            }
        }
    }

    vi a;               // a[]保存所有单行合法状态mask（同行炮兵不互相攻击）
    vi num(1<<m,0);     // num[mask]：该mask里面炮兵的数量，即二进制1的个数

    // 枚举全部m位二进制状态
    for(int i=0;i<(1<<m);i++)
    {
        // 判断本行状态合法：不能相邻，不能隔1位有炮兵
        // i & (i>>1)：存在两个1相邻；i & (i>>2)：存在两个1中间隔一个格子
        if(!((i>>1)&i) && !((i>>2)&i))
        {
            a.push_back(i);
        }
        // 统计该mask里面1的数量
        for(int j=0;j<m;j++)
        {
            num[i] += ((i>>j)&1);
        }
    }
    int len=a.size();   //合法状态总数量

    /*
    dp[i][c][b]
    i：当前处理第几行
    c：a数组下标，第i行选用状态 a[c]
    b：a数组下标，第i‑1行选用状态 a[b]
    值：最大炮兵数；初始‑1代表该状态不可达
    炮兵纵向攻击上下两行，所以转移需要 i,i‑1,i‑2三行互不冲突
    */
    vector<vector<vl>> dp(n+5,vector<vl>(len+5,vl(len+5,-1)));

    // 初始化第1行(i=1)
    for(int c=0;c<len;c++)
    {
        // a[c] & g[1]==a[c]：该状态所有炮兵都落在平原上，没有放在山地
        if((a[c] & g[1]) == a[c])
        {
            // 第1行，前一行不存在，用0号下标代表无状态，炮兵数量为本行1的数目
            dp[1][c][0] = num[a[c]];
        }
    }
    dp[0][0][0]=0; //第0行虚拟边界，作为初始条件

    // 从第2行到第n行逐行DP
    for(int i=2;i<=n;i++)
    {
        // c：当前第i行状态下标 a[c]
        for(int c=0;c<len;c++)
        {
            // 当前行状态不能放在山地，跳过
            if((a[c] & g[i]) != a[c]) continue;

            // b：i‑1行状态下标 a[b]
            for(int b=0;b<len;b++)
            {
                // i‑1行状态不能放在山地
                if((a[b] & g[i-1]) != a[b]) continue;
                // 当前行i 和 i‑1行炮兵不能冲突，上下不能重叠
                if(a[c] & a[b]) continue;

                // bb：i‑2行状态下标 a[bb]
                for(int bb=0;bb<len;bb++)
                {
                    // i行 和 i‑2行不能冲突；i‑1行 和 i‑2行不能冲突
                    if( !(a[c] & a[bb]) && !(a[b] & a[bb]) )
                    {
                        // 状态转移：i‑1行的dp值 + 当前行炮兵数量
                        dp[i][c][b] = max(dp[i][c][b], dp[i-1][b][bb] + num[a[c]]);
                    }
                }
            }
        }
    }

    // 答案：枚举最后一行n的所有合法(i,j)状态，取最大值
    ll ans=0;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            ans = max(dp[n][i][j], ans);
        }
    }
    cout<<ans;
    return 0;
}
