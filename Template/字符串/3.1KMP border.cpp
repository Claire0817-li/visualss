/*
题目思路：
border定义：字符串S的border是既为前缀又为后缀的子串，完整字符串本身也算border。
要求找出S全部不同border，对每个border，求该子串在S中作为子串的出现总次数，按长度从小到大输出。

算法标签：KMP、前缀函数(pi/nx数组)、border、计数递推
核心原理：
1. 前缀函数nx[i]：s[1..i]的最长border长度。利用nx数组回溯，可以取出字符串全部border。
2. 计数统计：
   ① cnt[x]初始：统计有多少个前缀，它的最长border恰好是x。
   ② 倒序递推：长border自带更小的border，将长border的计数累加传递给它自身的border。
   ③ 最终cnt[L]代表：有多少个其他前缀将L作为border；答案需要+1，补上L自己作为前缀的那一次出现。
3. 收集border：从n出发不断跳nx[len]，得到所有border（从长到短），反转后从小到大输出。
时间复杂度 O(n)，n≤1e5，线性复杂度。
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

int main()
{
    ios::sync_with_stdio(false);  // 关闭cin与C stdio同步，加速输入
    cin.tie(nullptr);            // 解绑cin、cout，消除cout强制刷新开销
    string s;   cin>>s;
    s=" "+s;                     // 字符串前补空格，改成【下标从1开始】，s[1]是原串首字符
    int n=s.size()-1;           // n = 原字符串真实长度

    vi nx(n+1,0);                // nx数组(前缀函数)：nx[i]表示 s[1..i] 的最长border长度
    // KMP前缀函数 1下标模板
    for(int i=2,j=0;i<=n;i++)
    {
        // j：当前已经匹配好的border长度
        // 失配：不断跳nx[j]缩短匹配长度，直到j=0或者字符匹配
        while(j&&s[i]!=s[j+1])
            j=nx[j];
        if(s[i]==s[j+1])        // 当前字符匹配成功，匹配长度+1
            j++;
        nx[i]=j;                // 记录s[1~i]最长border
    }

    vi cnt(n+1,0);
    // 第1轮统计：cnt[x] 记录有多少个前缀，它的【最长border恰好等于x】
    for(int i=1;i<=n;i++)
        cnt[nx[i]]++;

    /*
    倒序遍历：长border的所有计数，要传递给它自己的border
    原理：如果某个前缀最长border是i，那么i的border(nx[i])，也一定是这个前缀的border
    执行完之后 cnt[x] = 有多少个前缀，把x当做border（不限是不是最长）
    */
    for(int i=n;i>=1;i--)
    {
        cnt[nx[i]]+=cnt[i];
    }

    vi ans;
    // 收集全部border：从完整串长度n开始，不断跳nx[len]拿到所有border，直到len=0停止
    // border链：n → nx[n] → nx[nx[n]] → ... >0
    for(int len=n;len>0;len=nx[len])
        ans.push_back(len);
    reverse(ans.begin(), ans.end()); // 刚才收集是从长到短，反转变成从小到大输出

    cout<<ans.size()<<'\n';
    for(int len:ans)
        // cnt[len]：别的前缀把len当成border的次数；+1：补上len自身作为前缀出现的那一次
        cout<<len<<" "<<cnt[len]+1<<'\n';
    return 0;
}
