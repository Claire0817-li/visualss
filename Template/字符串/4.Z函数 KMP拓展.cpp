/*
【算法标签】
Z函数 / 扩展KMP(exKMP)
【题目思路】
输入两个字符串a,b
任务1：求b串的Z数组。z_b[i] = LCP( b[i...], b[1...] )，即b从i开头的后缀与b自身前缀的最长公共前缀。
       按公式计算权值：ansz = 依次异或 i*(z_b[i]+1)，i∈[1,m]，m是b长度。
任务2：求p数组。p[i] = LCP( a[i...], b[1...] )，即a从i开头的后缀与b整个前缀的最长公共前缀。
       按公式计算权值：ansp = 依次异或 i*(p[i]+1)，i∈[1,n]，n是a长度。
实现要点：
1. Z函数get_z：输入一个串，求该串自己的Z数组（1-based）。
2. 扩展KMP get_zz：给定模式串s、s的Z数组，文本串t；求出t每个后缀和s前缀的LCP，存入zz。
   本题：模式串s=b，文本串t=a，得到p数组。
3. 下标全部转为1-based，匹配板子习惯。
4. 乘法使用1LL提升为long long，防止int相乘溢出。
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

/*
Z函数（Z数组）
参数：
    a：1-based字符串
    n：字符串a长度
    z：输出z数组，z[i]代表 a[i...] 与 a[1...] 的LCP长度
原理：维护区间[l,r]，代表当前已知匹配的最右边界的窗口。
如果i落在[l,r]内，可以利用镜像位置z值快速初始化，减少暴力匹配次数。
*/
void get_z(string a,int n,vi &z)
{ 
    z[1]=n;  // 串首位置，整个串和自己匹配，LCP等于全长
    // l,r：当前Z-box窗口 [l,r]，窗口内是已经算过匹配的区间
    for(int i=2,l=0,r=0;i<=n;i++)
    {
        // i落在窗口内部，复用镜像位置的z值，取不超过窗口右边界的值
        if(i<=r) z[i]=min(z[i-l+1],r-i+1);
        // 暴力向外扩展，比较s[z[i]+1] 和 s[i+z[i]]，直到不相等/越界
        while(i+z[i]<=n&&a[1+z[i]]==a[i+z[i]])    z[i]++;
        // 如果当前后缀匹配到的右端超过r，更新窗口边界l,r
        if(i+z[i]-1>r)  l=i,r=l+z[i]-1;
    }
}

/*
扩展KMP exKMP
参数：
    s：模式串（用来当基准前缀，1-based）
    n：模式串s长度
    t：文本串（枚举t的每个后缀去匹配s）
    m：文本串t长度
    z：模式串s预先计算好的Z数组（必须提前调用get_z(s,n,z)）
    zz：输出数组，zz[i] = LCP( s[1...], t[i...] )
原理：维护匹配窗口[l,r]，t[i...]和s前缀的匹配，利用s的Z数组加速初始化，减少暴力比较。
*/
void get_zz(string s,int n,string t,int m,vi &z,vi &zz)
{
    // l,r：exKMP当前匹配窗口，t[l~r]与s[1~r-l+1]完全匹配
    for(int i=1,l=0,r=0;i<=m;i++)
    {
        // i在窗口内，借助模式串Z数组初始化zz[i]
        if(i<=r)    zz[i]=min(z[i-l+1],r-i+1);
        // 暴力扩展匹配：s的第zz[i]+1位 和 t的i+zz[i]位对比
        while(1+zz[i]<=n&&i+zz[i]<=m&&s[1+zz[i]]==t[i+zz[i]])   zz[i]++;
        // 若本次匹配突破旧窗口右边界，更新窗口
        if(i+zz[i]-1>r) l=i,r=l+zz[i]-1;
    }
}

int main()
{
    ios::sync_with_stdio(false); // 关闭cin与stdio同步，加速输入
    cin.tie(nullptr);           // 解绑cin、cout，避免cout刷新拖慢cin

    string a,b; cin>>a>>b;
    a=" "+a;    // 转为1-based下标，a[1]是第一个字符
    b=" "+b;    // 转为1-based下标，b[1]是第一个字符
    int n=a.size()-1; // n = a的长度
    int m=b.size()-1; // m = b的长度

    vi z_b(m+1);
    get_z(b,m,z_b);   // 计算b自身Z数组，用于任务1，同时作为exKMP模式串b的Z数组

    vi p(n+1);        // p数组长度等于a的长度，p[i] = LCP(b, a[i...])
    get_zz(b,m,a,n,z_b,p); // exKMP：模式串b，文本串a，结果存入p

    ll ansz=0,ansp=0; // 两个权值，用long long防止溢出
    // 计算b的Z数组对应的权值，遍历b全部位置 i=1~m
    for(int i=1;i<=m;i++)
    {
        ansz^=1LL*i*(z_b[i]+1); //1LL将表达式提升long long，避免int乘法溢出
    }
    // 计算p数组权值，遍历a全部位置 i=1~n
    for(int i=1;i<=n;i++)
    {
        ansp^=1LL*i*(p[i]+1);
    }
    cout<<ansz<<"\n"<<ansp;
    return 0;
}
