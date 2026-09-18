/*
算法标签：高斯-约旦消元、模运算、矩阵求逆、费马小定理
题目思路：
给定n阶方阵A，求A在模 1e9+7（质数）意义下的逆矩阵 A^{-1}。
原理：构造增广矩阵 [A | E]，E是n阶单位矩阵。
对增广矩阵做初等行变换，将左侧A转化为单位矩阵E；
因为初等行变换等价于左乘矩阵，变换后 [E | A^{-1}]，右侧部分就是A的逆矩阵。
如果消元过程中主元为0，说明矩阵不可逆，输出 No Solution。
模下除法不能直接除，利用费马小定理：质数mod下，a的逆元 = a^(mod-2) mod mod。
高斯-约旦特点：消元时同时消去主元列上方+下方所有行，直接得到对角化矩阵，无需回代。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=805;        // 矩阵最大尺寸，n<=400时2n=800，存[A|E]
const int mod=1e9+7;    // 模数，质数，支持费马小定理求逆元
int n;                  // 方阵阶数
ll a[N][N];             // 增广矩阵，1~n列为原矩阵A，n+1~2n列为单位矩阵E

// 快速幂：计算 x^y mod mod，用于求乘法逆元
ll qp(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

// 高斯-约旦消元，模意义求矩阵逆
// 返回true：矩阵可逆；false：矩阵不可逆（奇异矩阵）
bool gauss()
{
    // i：当前处理第i列（第i个主元）
    for(int i=1;i<=n;i++)
    {
        int r=i;
        // 从i行往下找，找到第i列不为0的行作为主元行
        for(int k=i;k<=n;k++)
        {
            if(a[k][i]!=0)
            {
                r=k;break;
            }
        }
        // 主元行不在i行，则交换两行
        if(r!=i)    swap(a[r],a[i]);
        // 主元为0，矩阵秩不足，不可逆
        if(a[i][i]==0)   return 0;

        // 归一化主元行：整行乘主元逆元，使a[i][i]=1
        ll inv=qp(a[i][i],mod-2);
        for(int j=1;j<=2*n;j++)
        {
            a[i][j]=a[i][j]*inv%mod;
        }

        // 消去所有其他行的第i列（上下全部消为0，高斯约旦核心）
        for(int k=1;k<=n;k++)
        {
            if(k==i)    continue; // 跳过主元本行
            ll t=a[k][i];         // 当前行第i列系数，消元倍数
            for(int j=1;j<=2*n;j++)
            {
                // 模减法，+mod再取模，防止负数
                a[k][j]=(a[k][j]-t*a[i][j]%mod+mod)%mod;
            }
        }
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    // 读入原方阵A，存入矩阵左半部分1~n列
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            a[i][j]%=mod; // 输入数规约到模mod范围
        }
    }
    // 矩阵右半部分n+1~2n列，初始化为单位矩阵E
    for(int i=1;i<=n;i++)
    {
        for(int j=n+1;j<=2*n;j++)
        {
            if(i+n==j)  a[i][j]=1;
            else    a[i][j]=0;
        }
    }
    if(!gauss())    cout<<"No Solution"; // 矩阵不可逆
    else
    {
        // 输出右半部分，即为A的逆矩阵
        for(int i=1;i<=n;i++)
        {
            for(int j=n+1;j<=2*n;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}
