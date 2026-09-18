/*
题目：度的数量 LibreOJ 10163
算法：数位DP + 组合数预处理
题意：求[X,Y]区间内，B进制表示中恰好有K个1，其余全是0的数字个数
思路：dp(n) 统计 0~n 内满足条件的数，答案 = dp(Y)-dp(X-1)
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=35; //最多30位足够
int B,K;
ll f[N][N];    //组合数 f[i][j]:i个位置选j个放1的方案数
int a[N];      //存放n转成B进制后的每一位，a[1]是最高位

//预处理杨辉三角，计算组合数 C(i,j)
void init()
{
    for(int i=0;i<=30;i++)   f[i][0]=1; //任何位置选0个1，方案为1
    for(int i=0;i<=30;i++)
    {
        for(int j=1;j<=i;j++)
        {
            f[i][j]=f[i-1][j]+f[i-1][j-1];
        }
    }
}

//dp函数：计算 0 ~ n 中符合条件数字的数量
ll dp(ll n)
{
    if(!n)  return 0; //n=0，没有符合条件的数
    int cnt=0;
    //把n拆成B进制，低位先存入数组
    while(n)
    {
        a[++cnt]=n%B;
        n/=B;
    }
    reverse(a+1,a+cnt+1); //翻转，让a[1]是最高位，a[cnt]最低位
    ll res=0;    //记录答案总数
    int last=0;  //沿着原数紧贴路径，已经选了多少个1

    //逐位遍历B进制每一位，数位DP核心循环
    for(int i=1;i<=cnt;i++)
    {
        int x=a[i]; //当前原数这一位的数字
        if(x>0)
        {
            //情况1：当前位填0，剩下cnt-i位，需要选K-last个1，方案累加
            res+=f[cnt-i][K-last];

            if(x>1)
            {
                //情况2：当前位填1（1<x，所以后面不受原数限制）
                if(K-last-1>=0)
                {
                    res+=f[cnt-i][K-last-1];
                }
                /*
                重点break解释：
                原数当前位x>1，紧贴原数的路径必须选x。
                但我们的数只能由0和1组成，选x是非法。
                紧贴路径直接断掉，后面数位不需要继续沿着原数检查，跳出for循环。
                所有本位选更小数字(0/1)的方案，上面已经全部统计完毕。
                */
                break;
            }
            else // x == 1，当前位可以选1，继续走紧贴原数的路径
            {
                last++; //紧贴路径，这一位选1，已选1的数量+1
                if(last>K)   break; //紧贴路径1的数量超过K，不可能合法，直接跳出
            }
        }
        // x == 0：本位只能填0，紧贴路径继续，不需要累加方案

        //循环走到最后一位，并且紧贴路径刚好凑够K个1，说明n本身合法，答案+1
        if(i==cnt&&last==K) res++;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init(); //预处理组合数
    ll X,Y;
    cin>>X>>Y;
    cin>>K>>B;
    //容斥思想：区间[X,Y] = dp(Y) - dp(X-1)
    ll ans=dp(Y)-dp(X-1);
    cout<<ans<<'\n';
    return 0;
}
