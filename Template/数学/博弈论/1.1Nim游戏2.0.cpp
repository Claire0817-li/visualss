/*
【算法标签】博弈论、Nim游戏、SG函数、异或
【核心思路 · Nim博弈原理详解】
Nim游戏结论：把所有堆石子数量做异或（nim和，也叫SG和）
设 res = a1 ^ a2 ^ a3 ^ ... ^ an
1. res != 0：先手必胜态（N-position，Next-position）
   ✅ 先手一定可以找到一种取法，让取完之后所有数异或变成 0，把必败态丢给后手
   之后不管后手怎么拿，都会破坏异或为0的局面，先手再恢复成异或0，持续下去后手最后无石子可取。
2. res == 0：先手必败态（P-position，Previous-position）
   ❌ 先手无论从哪一堆拿多少石子，都会让异或和不再等于0，后手就拿到必胜局面，后手可以一直控场赢。

补充：
SG定理（Sprague-Grundy）：多个独立公平组合游戏，整体游戏的SG值 = 各个子游戏SG值的异或。
Nim里每一堆石子本身就是一个独立子游戏，一堆k个石子的SG值 = k，所以总SG就是全部堆异或。
SG≠0 先手胜；SG=0先手败。

题型：标准Nim游戏 洛谷 P1247 取火柴游戏
规则：有k堆火柴，每堆a[i]根；每次选一堆，拿走任意正整数根火柴，不能不取；不能操作的人输
结论：把所有堆数量异或起来得到sg。sg=0为先手必败态，sg≠0为先手必胜态
任务：必胜时输出一步合法操作：拿走多少根、第几堆，再输出操作后各堆数量；必败直接输出 lose
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
    int k;cin>>k;        // k：火柴堆的总数
    vi a(k+1);           // a[1]~a[k]存每堆火柴数，下标从1开始，方便和题目堆号对应
    int sg=0;            // sg：全局异或和（Nim的SG值）
    for(int i=1;i<=k;i++)
    {
        cin>>a[i];
        sg^=a[i];        // 依次异或所有堆，算出总异或和
    }

    if(!sg)              // 总异或和等于0：先手必败
    {
        cout<<"lose\n";
        return;
    }

    // 寻找可以操作的堆：找到一个a[i]，使得 tar = a[i]^sg < a[i]
    // 把a[i]改成tar，新的全局异或和就变成0，丢给对手必败态
    for(int i=1;i<=k;i++)
    {
        int tar=a[i]^sg;
        if(tar<a[i])     // tar < a[i] 代表可以从这一堆拿走 a[i]-tar 根火柴
        {
            int mv=a[i]-tar;  // mv：本次要拿走的火柴数量
            cout<<mv<<' '<<i<<'\n'; // 输出：拿走多少，第几堆
            a[i]=tar;       // 更新这一堆火柴数量为修改后的值
            break;          // 只需要输出任意一个合法方案，找到就退出循环
        }
    }

    // 输出修改之后所有堆的火柴数量
    for(int i=1;i<=k;i++) cout<<a[i]<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);        
    int t=1; 
    while(t--) solve();       
    return 0;
}
