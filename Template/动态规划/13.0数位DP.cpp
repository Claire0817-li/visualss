/*
题目：洛谷 P2657 [SCOI2009] windy数
算法标签：数位DP（递推预处理版，非记忆化DFS）
题意：
定义windy数：不含前导零，且相邻两个数字之差至少为2的正整数。
给定a,b，求区间[a,b]内windy数的数量。

核心思路：
数位DP通用公式：ans = dp(b) - dp(a-1)
dp(x) 代表 1 ~ x 之间有多少个合法windy数。

1. init()预处理打表 f[i][j]
f[i][j] 的含义：一共有i位数字，最高位是j，满足windy条件的数字总数。
边界：1位数 0~9全部合法，f[1][k]=1
转移：i位最高位为j，枚举下一位k，如果abs(j-k)>=2，则累加f[i-1][k]

2. dp(n)函数，统计1~n的windy数
分两部分统计：
① 位数小于n的所有windy数：一定比n小，直接查表累加。
② 位数等于n的windy数：从高位到低位逐位枚举
   - 当前位填数字j < now(原数本位)：只要满足windy规则，剩下低位任意合法组合，查表f直接加到答案
   - 当前位选等于原数now：检查相邻数字是否满足windy条件；一旦不满足，原数这条分支直接break，不再继续向下探测
   - 如果完整走完所有数位没有break，说明n本身是windy数，答案+1
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=15; // 修改：原来N=10会数组越界，预处理用到i=10，数组下标最大需要到10
ll f[N][10];    // f[i][j]：i位数，最高位是j，windy数的个数
int a[N];       // 存放数字拆分后的每一位

//预处理f数组，打表
void init()
{
    //边界：1位数，0~9都是合法windy数
    for(int i=0;i<=9;i++)   f[1][i]=1;
    //预处理2~10位（题目上限2e9最多10位）
    for(int i=2;i<=10;i++)
    {
        //j是i位数的最高位
        for(int j=0;j<=9;j++)
        {
            //k是i位数的第二位
            for(int k=0;k<=9;k++)
            {
                //相邻数字差值>=2，满足windy条件
                if(abs(j-k)>=2)
                {
                    f[i][j]+=f[i-1][k];
                }
            }
        }
    }
}

//dp(n):计算[1,n]内windy数总数
ll dp(ll n)
{
    if(!n)  return 0; //n=0，1~0没有数字，返回0
    int cnt=0;
    //把n拆成十进制，先存低位
    while(n)
    {
        a[++cnt]=n%10;
        n/=10;
    }
    reverse(a+1,a+cnt+1); //翻转，a[1]变成最高位，方便高位遍历
    ll res=0;

    //第一部分：统计所有位数 < cnt 的windy数
    for(int i=1;i<cnt;i++)
    {
        for(int j=1;j<=9;j++) //i位数最高位不能为0
        {
            res+=f[i][j];
        }
    }

    int last=-1; //last=-1表示还没有选有效数字（前导状态）
    //第二部分：统计位数等于cnt的windy数，从高位到低位逐位枚举
    for(int i=1;i<=cnt;i++)
    {
        int now=a[i]; //原数当前位的数字上限
        //枚举当前位可以填的数字j
        for(int j=(i==1?1:0);j<now;j++)
        {
            //没有前导 或者 当前数字j和上一位last差值≥2，满足windy条件
            if(last==-1||abs(j-last)>=2)
                res+=f[cnt-i+1][j];
        }
        //尝试走原数这条分支：本位选now，检查是否合法
        //上一位存在，并且差值小于2 → 原数已经不合法，直接break，不用继续看低位
        if(last!=-1&&abs(now-last)<2)
            break;
        last=now; //合法，更新上一位数字，继续下一位
        //所有数位全部走完，说明n本身是windy数，答案+1
        if(i==cnt)
            res++;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a,b;    cin>>a>>b;
    init(); //预处理，只执行一次
    //区间[a,b] = 1~b的数量 减去 1~a-1的数量
    cout<<dp(b)-dp(a-1)<<'\n';
    return 0;
}
