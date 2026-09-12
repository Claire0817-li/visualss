/*
【算法标签】快速幂、费马小定理求逆元、数学推导
【题意分析】
公式： ans = n*(n‑1)/2 * 2^{n‑2}
边界： n < 2 输出 0

推导说明：
1. 除法 /2 在模 mod(质数 1e9+7) 下不能直接除，等价于乘以2的模逆元。
2. 根据费马小定理：模数mod为质数时，x的逆元 = pow(x, mod‑2, mod)。
   所以 1/2 mod mod = quickpow(2, mod‑2)
3. ans1 = n*(n‑1) * inv(2) mod mod，对应 n*(n‑1)/2
4. ans2 = 2^{n‑2} mod mod
5. 最终答案 ans = ans1 * ans2 % mod

边界：
n = 0 或 n =1，结果为0。

注意点：
输入n可能很大，先对mod取模再相乘，防止long long溢出。
时间复杂度：O(log n)，快速幂二进制拆分。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int mod=1e9+7;

/**
 * @brief 普通快速幂，计算 a^n mod mod
 * @param a 底数
 * @param n 指数
 * @return a^n % mod
 */
ll quickpow(ll a,ll n)
{
    ll res=1;               //答案初始值，普通乘法的单位元1
    while(n)                //二进制拆分指数n
    {
        if(n&1)             //当前二进制位为1，乘入答案
            res=res*a%mod;
        a=a*a%mod;          //底数平方，模运算
        n>>=1;              //指数右移一位
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;  cin>>n;
    // n<2，直接输出0
    if(n<2)
    {
        cout<<0<<endl;
        return 0;
    }
    // ans1 = n*(n‑1)/2 mod mod
    // /2 等价乘2的逆元 quickpow(2,mod‑2)
    ll ans1=(n%mod)*((n-1)%mod)%mod;
    ans1=ans1*quickpow(2,mod-2)%mod;

    // ans2 = 2^{n‑2} mod mod
    ll ans2=quickpow(2,n-2)%mod;

    // 总答案 = ans1 * ans2 % mod
    cout<<ans1*ans2%mod;
    return 0; 
}
