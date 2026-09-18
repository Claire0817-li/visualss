/*
POJ3071 Football
算法标签：概率DP + 区间淘汰赛DP
题目大意：
一共有 2^n 支球队，相邻两两比赛，输的淘汰，赢的晋级，单败淘汰赛。
给定 p[i][j] 代表i号球队战胜j号球队的概率。
求最终夺冠概率最大的球队，输出球队编号（题目编号从1开始）。

DP状态定义：
dp[i][j] 表示：打完第 i 轮比赛后，j号球队存活（晋级）的概率。

初始化：
dp[0][j] = 1.0
含义：第0轮，还没有进行任何比赛，所有队伍都活着，存活概率为1。

转移方程：
dp[i][j] += dp[i-1][j] * dp[i-1][k] * p[j][k]
条件：j和k可以在第i轮相遇。
含义：
1. j在上一轮成功晋级；
2. k在上一轮成功晋级；
3. 本轮比赛j击败k；
三者同时发生，把概率累加。

相遇判断条件：((j >> (i-1)) ^ 1) == (k >> (i-1))
淘汰赛分组规律：第i轮的每个区块大小是 2^i。
j和k必须在同一个大块，并且一个在区块左半、一个在区块右半，才有可能在本轮对战。
>>右移提取高位，^1翻转最后一位，用来判断分块。

答案：遍历 dp[n][0...m-1]，找到概率最大的球队编号，输出编号+1。

注意坑：
1. 数组变量长度VLA在标准C++不推荐，POJ提交会CE，建议改用vector；
2. 球队代码内0下标，输出要+1；
3. 移位运算符优先级，判断式括号不能省略。
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
    int n; 
    // n代表一共n轮，总球队数量 m = 2^n
    while(cin>>n)
    {
        if(n==-1)   break;
        int m=1<<n; // m = 2^n，球队总数
        
        // p[j][k] ：j打败k的概率
        // dp[i][j]：第i轮结束后，第j号球队存活晋级的概率
        double p[m+1][m+1];
        double dp[m+1][m+1];

        // 读入概率矩阵，球队编号 0 ~ m-1
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                cin>>p[i][j];
            }
        }

        // 初始化：第0轮（还没打任何比赛），所有球队都存活，概率=1
        for(int j=0;j<m;j++) dp[0][j]=1.0;

        // 枚举每一轮 i，从第1轮到第n轮
        for(int i=1;i<=n;i++)
        {
            // j 是当前球队
            for(int j=0;j<m;j++)
            {
                dp[i][j]=0.0; // 先清零本轮j获胜概率
                // k 枚举所有可能对手
                for(int k=0;k<m;k++)
                {
                    /*
                    判断条件：((j >> (i-1)) ^1) == (k >> (i-1))
                    含义：j 和 k 刚好能在第i轮相遇
                    原理：
                    第i轮每个大区块大小是2^i，区块对半分成左右两半；
                    j和k在同一个大块，并且分别在左右两半，才有机会本轮交手。
                    >> 右移，^1翻转二进制最后一位
                    */
                    if(((j>>(i-1))^1)==(k>>(i-1)))
                    {
                        // 转移：j上一轮晋级 && k上一轮晋级，本轮j打赢k
                        dp[i][j] += dp[i-1][j] * dp[i-1][k] * p[j][k];
                    }
                }
            }
        }

        // 在打完n轮后的所有球队里，找夺冠概率最大的球队
        double mx=0;
        int ans=0;
        for(int j=0;j<m;j++)
        {
            if(dp[n][j]>mx)
            {
                mx=dp[n][j];
                ans=j;
            }
        }
        // 题目输出球队编号从1开始，代码内部是0下标，+1
        cout<<ans+1<<endl;
    }
    return 0;
}
