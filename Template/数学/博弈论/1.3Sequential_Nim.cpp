/*
1. 标准 Nim
每一堆都是独立子游戏，直接适用 Sprague-Grundy 定理，所有 SG 值异或。
自由度最高，你随时可以挑任意一堆调整异或和。
2. 阶梯 Nim
石子可以传递，堆不独立；偶数台阶的石子是 “垃圾”：对手挪到偶数台阶，你可以再往下挪一层抵消。
只有奇数台阶等价于标准 Nim 里的石子堆，偶数台阶忽略不计。
3. Sequential Nim
完全破坏了独立子游戏前提，不能用 SG 异或。
前面连续的 1，两个人只能一人拿一个；谁先碰到第一个 > 1 的堆，谁掌握主动权：可以选择拿光或者留 1 颗，把胜负权交给对手。
*/

/*
题型：Sequential Nim CF1382B
规则：只能取编号最小的非空堆的石子
思路：找到第一个a[i]>1的位置pos；全1则胜负看堆数奇偶
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
    int n; cin>>n;
    vi a(n+1);
    int pos=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>1 && !pos) pos=i;
    }
    if(!pos)
    {
        // 全部都是1：奇数堆先手胜，偶数后手胜
        if(n%2==1) cout<<"First\n";
        else cout<<"Second\n";
    }
    else
    {
        // 第一个>1在pos，pos奇数先手胜，偶数后手胜
        if(pos%2==1) cout<<"First\n";
        else cout<<"Second\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}

