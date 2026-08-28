/*
【题目：AcWing 292 愤怒的小鸟】
题目描述：
多组测试数据。
所有小鸟都从原点 (0,0) 发射，飞行轨迹抛物线 y = a*x² + b*x。
抛物线必须开口向下，也就是 a < 0。
平面上一共有 n 只小猪，每只猪坐标(xi, yi)。
一只小鸟沿抛物线飞过，抛物线上所有猪都会被消灭。
求最少发射多少只小鸟，可以消灭全部小猪。

输入：
第一行整数 t，代表测试组数。
每组第一行两个整数 n,m；n是小猪数量，m本题无实际作用。
接下来 n 行，每行两个小数 x,y，代表小猪坐标。

输出：每组输出一个整数，最少小鸟数量。

数据范围：1 ≤ n ≤ 18
n=18，总状态数 2^18 = 262144，适合状态压缩DP

解题思路：
1.预处理：任意两只猪i,j，计算过原点、i、j的抛物线参数a,b；a<0才合法。
  算出这条抛物线能击中哪些猪，保存为二进制mask，存入 line[i][j]。
2.状态压缩DP：
  dp[s]：s是二进制mask，第k位=1代表第k只猪已经被打死。dp[s]代表达成状态s最少需要多少只小鸟。
  初始 dp[0]=0，其余状态赋值无穷大。
  剪枝：每次找当前状态下编号最小还活着的猪f，只对f做转移，避免重复枚举等价方案，提升速度。
  转移1：单独给f开一枪，只打死f。
  转移2：用经过f和j的抛物线，一枪打死mask覆盖的全部猪。
3.答案 dp[(1<<n)-1]，二进制n位全1，代表全部小猪消灭。
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

//浮点数精度阈值，计算机浮点数运算存在微小误差，禁止直接用==判断double相等
const double eps=1e-8;

/*
 * inline：内联函数，短小高频工具函数，减少函数调用的开销
 */
inline int cmp(double a,double b)
{
    if(fabs(a-b)<eps)   return 0;
    else    return a>b?1:-1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int t;  cin>>t;
    while(t--) 
    {
        int n,m;   cin>>n>>m;
        //p[i]：存储第 i 号小猪坐标，下标从0开始
        //⚠重要：题目输入坐标是小数，必须使用double，int会截断小数，直接导致计算全部出错
        vector<pair<double,double>> p(n);
        for(int i=0;i<n;i++)
        {
            cin>>p[i].first>>p[i].second;
        }

        /*
         line[i][j]：int类型二进制mask掩码
         含义：经过原点、小猪i、小猪j的合法抛物线，能够击中的全部小猪状态
         mask二进制第k位 = 1：代表k号猪会被这条抛物线击中；0代表打不到
        */
        vvi line(20,vi(20,0));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j)   continue;  //两点不能是同一只猪，两点确定一条抛物线

                //取出i,j两只猪的坐标
                double x1=p[i].first,x2=p[j].first;
                double y1=p[i].second,y2=p[j].second;

                /*
                抛物线公式推导：小鸟从原点出发 y = a*x² + b*x
                将点(x1,y1)代入：y1 = a*x1² + b*x1，两边除以x1(x1≠0)
                => y1/x1 = a*x1 + b
                同理：y2/x2 = a*x2 + b
                两式相减求a： a = (y2/x2 - y1/x1) / (x2 - x1)
                回代求b： b = y1/x1 - a * x1
                */
                double a=(y2/x2-y1/x1)/(x2-x1);
                double b=y1/x1-a*x1;

                if(cmp(a,0)>=0)   continue; //a>=0开口向上，游戏不合法，直接跳过

                int mask=0;
                //遍历所有小猪，标记哪些猪落在这条抛物线上
                for(int k=0;k<n;k++)
                {
                    double x=p[k].first,y=p[k].second;
                    //浮点数必须调用cmp，禁止直接 ==
                    if(cmp(a*x*x+b*x,y)==0)
                    {
                        mask |= (1<<k); //把k号猪对应的bit置1
                    }
                }
                line[i][j]=mask;
            }
        }

        /*
        dp[s]：状态压缩DP数组
        s：二进制mask，第k位=1代表第k只猪已经被打死
        dp[s]：达成状态s，最少需要发射多少只小鸟
        0x3f3f3f3f代表无穷大，表示该状态暂时不可达
        */
        vi dp(1<<n,0x3f3f3f3f);
        dp[0]=0; //初始状态：一只猪都没打死，需要0发子弹

        //枚举所有状态
        for(int s=0;s<(1<<n);s++)
        {
            if(dp[s]==0x3f3f3f3f)   continue; //这个状态无法到达，跳过

            //找当前状态s下，编号最小还活着的小猪f（剪枝核心）
            int f=0;
            for(f=0;f<n;f++)
            {
                //s & (1<<f) 判断s的第f位；!取反，结果为true代表猪还活着
                if(!(s&(1<<f))) break;
            }
            if(f>=n)   continue; //全部猪已经打死，不需要继续转移

            //方案1：单独给f号猪开一枪，只打死f
            dp[s|(1<<f)]=min(dp[s|(1<<f)],dp[s]+1);

            //方案2：用一条经过f和j的抛物线，一枪打死抛物线覆盖的所有猪
            for(int j=0;j<n;j++)
            {
                if(f==j)   continue; //不能是同一只猪
                if(line[f][j]==0) continue; //没有合法抛物线，跳过
                int ns=s|line[f][j]; //新状态：原有打死的猪 + 抛物线新打死的猪
                dp[ns]=min(dp[ns], dp[s]+1);
            }
        }
        //(1<<n)-1：二进制n个1，代表全部小猪消灭，输出最小小鸟数
        cout<<dp[(1<<n)-1]<<"\n";
    }
    return 0;
}
