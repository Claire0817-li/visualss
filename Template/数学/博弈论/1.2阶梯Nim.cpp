/*
题目：P3480 [POI2009]KAM-Pebbles
算法标签：博弈论、阶梯Nim(台阶博弈)、差分转化、SG博弈
题意回顾：
给不降序列 a₁ ≤ a₂ ≤ … ≤ aₙ
每次操作：选一堆拿走若干石子，操作后仍然保持不降；不能操作的人输
输出 TAK：先手必胜；NIE：先手必败

核心思想：
原问题操作有“不降”限制，不能直接用普通Nim。
构造一组【倒差分d】，把原问题的合法操作，等价变成阶梯Nim里“石子向左挪一级”。
阶梯Nim结论：只看奇数台阶上的值异或，偶数台阶只是中转站，不影响胜负。
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

void solve()
{
    int n;cin>>n;
    vi a(n+1);
    // a[1]~a[n] 读入，下标从1，方便公式对齐
    for(int i=1;i<=n;i++) cin>>a[i];

    vi d(n+1);
    /*
    构造倒差分 d 数组（这是本题最关键一步）
    d[1] = a[n] - a[n-1]
    d[2] = a[n-1] - a[n-2]
    d[3] = a[n-2] - a[n-3]
    ...
    d[n-1] = a[2] - a[1]
    d[n] = a[1]

    通俗理解：从最右边往左边，依次算相邻两项的差；最后单独把最左边a[1]放到d[n]
    */
    for(int i=1;i<=n-1;i++)
    {
        d[i]=a[n-i+1]-a[n-i];
    }
    d[n]=a[1];

    int sg=0;
    // 阶梯Nim规则：只异或d中下标为奇数的位置
    for(int i=1;i<=n;i++)
    {
        if(i&1) sg^=d[i];
    }

    /*
    sg != 0 → 先手可以构造局面，把sg变成0丢给对手，必胜 TAK
    sg == 0 → 无论先手怎么操作，都会把sg变成非0，对手必胜，先手NIE
    */
    if(sg!=0)  cout<<"TAK\n";
    else       cout<<"NIE\n";
}

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);          
    int t;  cin>>t;        
    while(t--)
    {
        solve();
    }
    return 0;
}
