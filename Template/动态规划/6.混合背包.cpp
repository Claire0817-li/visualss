/*
混合背包（完全背包 + 多重背包二进制拆分优化）
题意简述：
给定开始时间、结束时间，把时间换算成总分钟数T（背包总容量，代表总可用时间）。
有n个任务：
t[i]：做该任务消耗时间(物品体积w)
c[i]：做该任务获得收益(物品价值v)
p[i]：任务数量限制
    p[i] = 0：任务可以无限次做 → 完全背包
    p[i] > 0：该任务最多做p[i]次 → 多重背包，二进制拆分成01背包
背包容量是总时间T，求在不超过总时间的前提下，可以获得的最大总收益。

算法类型：混合背包DP
1.时间字符串解析函数 gettime：解析"hh:mm"格式，返回小时、分钟pair
2.计算总可用分钟T：结束时间减去起始时间，换算为分钟
3.dp[j]：消耗j分钟时间，可以得到的最大收益
4.p[i]==0：完全背包，体积循环正序
5.p[i]>0：多重背包，二进制拆分，拆成若干01物品，倒序循环体积
时间复杂度：O(n log p * T)
*/

#include <bits/stdc++.h>
using namespace std;

//类型别名简化代码
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

/**
 * gettime：解析 "hh:mm" 格式的时间字符串
 * @param s 输入时间字符串，例"08:30"
 * @return pair<小时,分钟>
*/
pair<ll,ll> gettime(string s)
{
    string s1,s2;
    bool ok=true;   //true代表还在读取小时部分，遇到':'切换为读分钟
    for(ll i=0;i<s.size();i++)
    {
        if(s[i]==':')
        {
            ok=false;
            continue;
        }
        if(ok)
            s1+=s[i];   //拼接小时字符串
        else
            s2+=s[i];   //拼接分钟字符串
    }
    ll h=stoll(s1);    //字符串转long long 小时
    ll m=stoll(s2);    //字符串转long long 分钟
    return {h,m};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1,s2;
    cin>>s1>>s2;    //s1开始时间，s2结束时间 hh:mm
    ll n;
    cin>>n;         //任务数量n

    vl t(n+1),c(n+1),p(n+1);
    // t[i] 消耗时间(背包体积w)
    // c[i] 获得收益(背包价值v)
    // p[i] 任务最大可做次数，0代表无限
    for(ll i=1;i<=n;i++)
        cin>>t[i]>>c[i]>>p[i];


    //解析两个时间
    auto t1=gettime(s1);  //开始时间 {h1,m1}
    auto t2=gettime(s2);  //结束时间 {h2,m2}

    //计算时间差，处理分钟借位：结束分钟 < 开始分钟，小时要减1，分钟+60
    ll k=(t2.second>=t1.second)?0:1;
    ll T=(t2.first-t1.first-k)*60+(t2.second+60*k-t1.second);
    // T：总可用时间，单位分钟，背包总容量

    vl dp(T+1,0); //dp[j]:花费j分钟能获取的最大收益，初始0

    //vv存拆分后物品价值，ww存拆分后物品体积；n*20是二进制拆分上限 log2(1e5)≈17
    vl vv(n*20+10,-1),ww(n*20+10,-1);

    for(ll i=1;i<=n;i++)
    {
        if(p[i]==0)
        {
            // =========完全背包：任务可以无限次做=========
            // 体积正序循环，允许物品多次选取
            for(ll j=t[i];j<=T;j++)
            {
                dp[j]=max(dp[j],dp[j-t[i]]+c[i]);
            }
        }
        else
        {
            // =========多重背包：最多p[i]次，二进制拆分转01背包=========
            ll num=0;               //拆分之后物品计数器
            ll v=c[i],w=t[i],m=p[i];//v价值，w时间(体积)，m最多做m次

            //二进制拆分：1,2,4,...,剩余部分
            for(ll j=1;j<=m;j<<=1)
            {
                num++;
                vv[num]=j*v;    //拆分物品总价值
                ww[num]=j*w;    //拆分物品总消耗时间
                m-=j;
            }
            if(m>0) //剩下不能被2的幂的部分单独作为一件物品
            {
                num++;
                vv[num]=m*v;
                ww[num]=m*w;
            }

            //把拆分出来的每一件当做01背包物品处理，倒序遍历容量
            for(ll kk=1;kk<=num;kk++)
            {
                for(ll j=T;j>=ww[kk];j--)
                {
                    dp[j]=max(dp[j-ww[kk]]+vv[kk], dp[j]);
                }
            }
        }
    }
    //总时间T，输出最大收益
    cout<<dp[T];

    return 0;
}
