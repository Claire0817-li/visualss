/*
算法标签：博弈论、Anti-Nim、SJ定理（小约翰的游戏）
题目：取最后一颗石子的人输，每次任选一堆取任意非0数量石子，多组测试
SJ定理先手必胜条件：
1. 所有石子堆都为1：堆数为偶数先手John胜，奇数先手必败(Brother)
2. 存在至少一堆石子>1：全局异或和不为0则先手John胜，异或和=0先手必败(Brother)
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
    int n;  cin>>n;
    vi a(n+1);
    bool al1=1;    // al1标记：是否所有堆都是1
    int seg=0;     // seg：全局异或和
    for(int i=1;i<=n;i++)   
    {
        cin>>a[i];
        if(a[i]!=1) al1=0;
        seg^=a[i];
    }
    if(al1) 
    {
        // 全是1：奇数堆先手被迫拿最后一个，输；偶数堆先手赢
        cout<<((n%2)?"Brother":"John")<<'\n';
    }
    else
    {
        // 存在堆>1：异或非0先手胜，异或0先手败
        cout<<(seg?"John\n":"Brother\n");
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;  cin>>t;
    while(t--)   
    {
        solve();
    }
    return 0;
}
