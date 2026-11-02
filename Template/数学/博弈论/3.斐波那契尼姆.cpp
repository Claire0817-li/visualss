/*
算法标签：博弈论、斐波那契尼姆 Fibonacci Nim、齐肯多夫分解 Zeckendorf
题意：
n颗石子，先手第一次可以取任意数量；
之后每一轮，最多取对手上一轮取的2倍；取走最后一颗石子获胜。
求先手第一次最少取多少颗，保证必胜。
结论：
将n做齐肯多夫分解：拆成若干互不相邻的斐波那契数之和，答案为分解里最小的斐波那契数。
斐波那契增长极快，只需预处理几十项就超过 1e15。
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

ll n;
vl fb;
// 预处理斐波那契数列，直到数值大于1e18
void findfb()
{
    fb.push_back(1);
    fb.push_back(2);
    while(1)
    {
        ll nx=fb.back()+fb[fb.size()-2];
        if(nx>1e18) break;
        fb.push_back(nx);
    }
}
void solve()
{
    cin>>n;
    ll ans=n;
    // 从大到小贪心分解，保证选出的斐波那契数互不相邻
    for(int i=fb.size()-1;i>=0;i--)
    {
        if(fb[i]<=n)
        {
            n-=fb[i];
            ans=min(ans,fb[i]);
            i--; // 跳过下一项，禁止选取相邻斐波那契数
        }
    }
    cout<<ans<<'\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    findfb();
    while(t--)  solve();
    return 0;
}
