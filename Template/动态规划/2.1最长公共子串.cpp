/*
线性DP：最长公共子串（注意：不是子序列！子串要求字符连续）
题目简述：
输入一整个字符串，格式形如 "abcde","bcdfg" （中间逗号分隔，两边带引号）
解析得到两个字符串 s 和 t。
求 s 与 t 的**最长公共连续子串**，输出带双引号的结果。

算法类型：DP，最长公共子串 LCS（Longest Common Substring，连续）
⚠️区分：最长公共子序列LCS(Longest Common Subsequence)字符可以不连续。

状态定义：
f[i][j]：s以i下标结尾，t以j下标结尾的公共连续子串的长度。

转移方程：
if(s[i] == t[j])
    f[i][j] = f[i‑1][j‑1] + 1;
else
    f[i][j] = 0;
字符不相等，连续子串直接断开，长度清零。

记录：ans保存最大长度，pos保存s中该子串结束的下标。
最后从s截取：起始位置 pos‑ans+1，截取长度 ans。

输入处理说明：
原始输入 o 样例："abcde","bcdfg"
o.find(',') 找到逗号位置p
s = o.substr(1, p‑2)：跳过开头引号，截取到逗号前；p‑2是去掉逗号前的引号
t = o.substr(p+2, o.size()-p-3)：跳过逗号+后引号，截取到末尾前的右引号。

时间复杂度 O(n*m)，n=s长度，m=t长度。
*/

#include <bits/stdc++.h>
using namespace std;

//类型别名简化书写
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string o;
    cin>>o; //读入整行输入，格式 "s","t"

    string s,t;
    int p=o.find(',');   //找到逗号分隔符的下标

    /*
    o样例："abcde","bcdfg"
    substr(pos,len)：从pos开始取len个字符
    s从下标1开始，跳过第一个双引号；p-2：跳过逗号前面的双引号
    t从p+2开始：跳过逗号+后面的双引号；size-p-3 去掉末尾的双引号
    */
    s=o.substr(1,p-2);
    t=o.substr(p+2,o.size()-p-3);

    int n=s.size(),m=t.size();
    // f[i][j]：s[i]结尾、t[j]结尾的最长公共连续子串长度
    vvi f(n,vi(m,0));

    int ans=0;   //记录最长公共子串长度
    int pos=0;   //记录s中最长子串的结束下标

    //初始化第0行：s[0]和t各个位置匹配
    for(int j=0;j<m;j++)
    {
        if(s[0]==t[j])
        {
            f[0][j]=1;
            ans=1;
            pos=0;
        }
    }
    //初始化第0列：t[0]和s各个位置匹配
    for(int i=0;i<n;i++)
    {
        if(t[0]==s[i])
        {
            f[i][0]=1;
            ans=1;
            pos=i;
        }
    }

    //DP递推 i从1，j从1开始
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            if(s[i]==t[j])
            {
                //字符相等，继承左上角状态+1，保持连续
                f[i][j]=f[i-1][j-1]+1;
                //更新最大长度、结束位置
                if(f[i][j]>ans)
                {
                    ans=f[i][j];
                    pos=i;
                }
            }
            else
            {
                //字符不等，连续子串断裂，长度置0
                f[i][j]=0;
            }
        }
    }
    // 从s截取：起始下标 pos‑ans+1，截取ans个字符
    string res=s.substr(pos-ans+1,ans);
    cout<<"\""<<res<<"\"";

    return 0;
}
