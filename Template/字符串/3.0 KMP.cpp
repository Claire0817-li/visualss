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
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);        

    string t1,t2;
    cin>>t1>>t2;                // t1主串，t2模式串（原生0下标）
    string s1=" "+t1;           // s1[1]开始存主串，空出s1[0]，适配1下标模板
    string s2=" "+t2;           // s2[1]开始存模式串，空出s2[0]

    int l1=s1.size()-1;         // 主串真实长度（去掉前面加的空格）
    int l2=s2.size()-1;         // 模式串真实长度

    vi nx(l2+1,0);              // nx数组，nx[i]代表s2[1~i]最长相等前后缀长度

    // ========== 构造next数组（模式串自匹配） ==========
    for(int i=2,j=0;i<=l2;i++)  // i：后缀末尾；j：当前匹配好的前缀长度，i从2开始，nx[1]=0
    {
        // 失配：j不为0，且当前字符不等，j回跳到nx[j]，循环直到j=0或者匹配
        while(j&&s2[i]!=s2[j+1])
            j=nx[j];
        if(s2[i]==s2[j+1])      // 当前字符匹配成功，已匹配前缀长度+1
            j++;
        nx[i]=j;                // 存入nx[i]，记录s2[1..i]最长相等前后缀长度
    }

    // ========== KMP主串匹配阶段 ==========
    for(int i=1,j=0;i<=l1;i++)  // i主串指针(只前进不回退)；j模式串已匹配字符数量
    {
        // 当前字符失配，j不断回跳，找次长可复用前后缀
        while(j&&s1[i]!=s2[j+1])
            j=nx[j];
        if(s1[i]==s2[j+1])      // 当前字符匹配，已匹配数量j+1
            j++;
        if(j==l2)               // j等于模式串全长，找到一次完整匹配
        {
            cout<<i-l2+1<<'\n'; // 输出匹配起始位置（题目要求1下标）
            j=nx[j];            // 关键：回跳，保留可复用后缀，继续查找重叠匹配
        }
    }

    // 打印next数组，调试用
    for(int i=1;i<=l2;i++)
    {
        cout<<nx[i]<<" ";
    }
    return 0;
}
