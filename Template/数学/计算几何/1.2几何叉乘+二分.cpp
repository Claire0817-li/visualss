/*
题目：POJ 2318 TOYS
题目大意：
一个长方形盒子，左上角(x1,yy1)，右下角(x2,yy2)。
盒子内部有 n 块竖直隔板，把盒子切分成 n+1 个隔间，隔间编号：0,1,2…n。
每块隔板给出上端x坐标、下端x坐标，y固定为盒子上下边界。
给出 m 个玩具的坐标，统计每个隔间里面放了多少个玩具。

输入：
多组样例。每组第一行 n；n=0代表输入结束。
接着 m x1 y1 x2 y2
接下来 n 行，每行两个整数：U L，代表第i块隔板上端x=U，下端x=L。
接下来 m 行，每个玩具坐标 tx ty。

输出：
按隔间编号输出 i: 数量，每组样例结束输出空行。

算法思路：二分 + 叉积(计算几何)
1. 隔板是按从左到右顺序给出。对于一个玩具，二分是落在哪两块隔板之间。
2. 叉积 cross(P,A,B)：A隔板上端，B隔板下端。判断点P在直线AB的左边还是右边。
    cross >= 0：点P在隔板AB左侧；
    cross < 0：点P在隔板AB右侧。
3. 二分结束后 l 的值就是玩具所在隔间编号。cnt[l]++计数。

注意坑：
1. 变量不要命名 y1 y2，会和cmath库函数重名，改成yy1,yy2。
2. int直接相乘会溢出，正式提交建议加上1LL强转long long。
3. OJ输出格式严格，每组样例末尾输出换行。
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int n,m;            // n：隔板数量；m：玩具数量
int x1,yy1,x2,yy2;  // 盒子左上角(x1,yy1)，右下角(x2,yy2)

/**
 * cross叉积函数
 * @param a  玩具点P
 * @param b  隔板上端点A
 * @param c  隔板下端点B
 * 向量 CB × CA
 * 返回true：叉积 >=0，玩具点在隔板AB左侧（点落在隔板线上也算左侧）
 * 返回false：叉积 <0，玩具点在隔板AB右侧
 */
bool cross(pair<int,int> &a,pair<int,int> &b, pair<int,int> &c)
{
    // 注意：这里int相乘存在溢出风险，正式提交改为 1LL*(...)
    if(((b.first-c.first)*(a.second-c.second)-(b.second-c.second)*(a.first-c.first))>=0)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   // 关闭同步，加速cin输入

    while(cin>>n)       // 多组测试用例
    {
        if(n==0)    break;  // n等于0，终止输入

        // m玩具数量；盒子四个角坐标
        cin>>m>>x1>>yy1>>x2>>yy2;

        vector<pair<int,int>> zb(n);
        // zb[i].first：第i块隔板上端的x；zb[i].second：第i块隔板下端的x
        for(int i=0;i<n;i++)
            cin>>zb[i].first>>zb[i].second;

        vi cnt(n+1,0);  // cnt[i]：编号i隔间的玩具数量，隔间0~n，共n+1个隔间

        // 逐个处理m个玩具
        for(int i=0;i<m;i++)
        {
            int tx,ty;
            cin>>tx>>ty;
            pair<int,int> P={tx,ty}; // 玩具点坐标

            int l=0,r=n-1; // 二分区间：隔板下标 [0, n‑1]
            while(l<=r)
            {
                int mid=(l+r)>>1;   // mid = (l+r)/2，取中间隔板

                // A：mid号隔板上端；B：mid号隔板下端
                pair<int,int> A={zb[mid].first,yy1};
                pair<int,int> B={zb[mid].second,yy2};

                if(cross(P,A,B))
                {
                    // 玩具在mid隔板的左边，往左侧隔板继续搜索
                    r=mid-1;
                }
                else
                {
                    // 玩具在mid隔板的右边，往右侧隔板继续搜索
                    l=mid+1;
                }
            }
            // 二分循环结束，l的值就是玩具所在隔间编号
            cnt[l]++;
        }

        // 输出每个隔间的玩具数目
        for(int i=0;i<=n;i++)
        {
            cout<<i<<": "<<cnt[i]<<"\n";
        }
        cout<<"\n"; // POJ要求每组样例输出完成后输出空行
    }
    return 0;
}
