/*
POJ 2074 Line of Sight 视线
题目大意：
全部物体都是平行于x轴的水平线段。
1.房屋：线段[hx1, hx2]，y = hy；房屋一定在观察线的上方 hy > by。
2.产权观察线：线段[bx1, bx2]，y = by；我们只在这条线段上找位置。
3.障碍物：n条水平线段[xx1,xx2]，y = hh；障碍物必须夹在房屋和观察线中间 by < hh < hy，才会遮挡视线。

条件：观察线上某个点P，要能够完整看见【整栋房屋】。
完整看见房屋的含义：
从P看向房屋的左端点H1，视线不能被障碍物挡住；
从P看向房屋的右端点H2，视线不能被障碍物挡住。
只要有一条视线被挡住，这个P点就是盲区，不能选。

要求：求观察线上，满足条件的最长连续一段的长度，保留2位小数。
如果观察线上没有任何点可以完整看见房屋，输出字符串 "No View"。

算法思路：
核心思想：不枚举观察线上的点，而是计算障碍物造成的盲区，剩下的就是可视区域。
每一个位于中间高度的障碍物，会在观察线上打出一段【盲区】，盲区内部所有点都不能完整看见房屋。

怎么求单个障碍物对应的盲区：
  ①连线：房屋右端 H2(hx2,hy)  ↔ 障碍物左端点 B1(obs.x1,obs.h)，这条直线与观察线(y=by)相交，得到交点bl。
  ②连线：房屋左端 H1(hx1,hy)  ↔ 障碍物右端点 B2(obs.x2,obs.h)，这条直线与观察线(y=by)相交，得到交点br。
  ③[bl , br]就是这个障碍物在观察线上制造的盲区。
  注意：几何计算有可能bl>br，需要swap交换；交点可能跑到观察线外面，要裁剪到[bx1,bx2]。

后续步骤：
1.把所有有效盲区全部收集；
2.盲区按照左端点从小到大sort排序；
3.扫描合并盲区，统计盲区与盲区之间的空隙、观察线开头、观察线末尾的可视区间；
4.取最大可视区间长度作为答案；
5.浮点数全部使用eps(1e‑8)做判断，禁止直接==判等，规避浮点计算误差。
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const double eps = 1e-8;

//障碍物结构体，水平线段，x1左端点，x2右端点，h高度
struct zhangai
{
    double x1,x2,h;
    zhangai(){};
    zhangai(double nx1,double nx2,double nh):x1(nx1),x2(nx2),h(nh){}
};

//平面二维点结构体，存储x,y坐标
struct Point
{
    double x,y;
    Point(){}
    Point(double nx,double ny):x(nx),y(ny){}
};

//向量a × 向量b，二维叉积
//叉积>0：b在a逆时针方向；叉积<0：b在a顺时针方向；等于0共线
double cross(Point a,Point b)
{
    return a.x*b.y - a.y*b.x;
}

/*
getNode：求两条直线的交点，返回交点的x坐标
直线1：过A点，方向向量u；参数方程：A + t * u
直线2：过B点，方向向量v；参数方程：B + s * v

数学推导：
A + t*u = B + s*v
=> t * u − s * v = B − A
用叉积消元求出参数t，代入直线1算出交点坐标。
本题中第二条直线就是观察线，是一条水平线。
*/
double getNode(Point A,Point u,Point B,Point v)
{
    //向量BA = B - A
    Point BA(B.x-A.x,B.y-A.y);
    double t=cross(BA,v)/cross(u,v);
    Point p(A.x+u.x*t,A.y+u.y*t);
    return p.x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double hx1,hx2,hy;   //房屋：hx1房屋左，hx2房屋右，hy房屋高度
    while(cin>>hx1>>hx2>>hy)
    {
        if(fabs(hx1)<eps&&fabs(hx2)<eps&&fabs(hy)<eps) break;
        double bx1,bx2,by; //观察线：bx1观察线左，bx2观察线右，by观察线高度
        cin>>bx1>>bx2>>by;

        int n;
        cin>>n;
        vector<zhangai> p;
        for(int i=0;i<n;i++)
        {
            double xx1,xx2,hh;
            cin>>xx1>>xx2>>hh;
            //障碍物高度不在房屋与观察线中间，不会产生遮挡，直接跳过
            //hh必须严格大于by，严格小于hy
            if(hh<by+eps||hh>hy-eps) continue;
            zhangai obs(xx1,xx2,hh);
            p.push_back(obs);
        }

        vector<pair<double,double>> blind; //存储每一段盲区 pair<盲区左，盲区右>
        for(auto &obs:p)
        {
            Point H2(hx2,hy);       //房屋右端点
            Point B1(obs.x1,obs.h); //障碍物的左端点
            Point H1(hx1,hy);       //房屋左端点
            Point B2(obs.x2,obs.h); //障碍物的右端点
            Point L1(bx1,by);       //观察线左端点
            Point L2(bx2,by);       //观察线右端点

            //H2到B1的直线，和观察线相交得到盲区左边界bl
            Point dir1(B1.x-H2.x,B1.y-H2.y);
            Point dir2(L2.x-L1.x,L2.y-L1.y);
            double bl=getNode(H2,dir1,L1,dir2);

            //H1到B2的直线，和观察线相交得到盲区右边界br
            Point dir3(B2.x-H1.x,B2.y-H1.y);
            double br=getNode(H1,dir3,L1,dir2);

            //几何计算有可能bl>br，交换保证左<=右
            if(bl>br) swap(bl,br);

            //裁剪：把盲区限制在观察线[bx1,bx2]之内，超出部分无效
            bl = max(bl, bx1);
            br = min(br, bx2);

            //br‑bl>eps，代表是一段有长度的有效盲区，存入数组
            if(br - bl > eps)
            {
                blind.emplace_back(bl,br);
            }
        }

        //把所有盲区，按照盲区左端点从小到大排序，为区间合并做准备
        sort(blind.begin(),blind.end());
        int cnt=blind.size();
        double ans=0;

        if(cnt==0)
        {
            //没有任何盲区，整条观察线全部都可以完整看见房屋
            ans=bx2-bx1;
        }
        else
        {
            //第一种候选区间：观察线起点bx1到第一个盲区的左端点
            //第二种候选区间：最后一个盲区的右端点到观察线终点bx2
            ans=max(blind[0].first-bx1, bx2-blind[cnt-1].second);

            //r：记录已经扫描过的盲区，覆盖到的最右侧坐标
            double r=blind[0].second;

            //遍历剩下所有盲区，做区间合并，寻找盲区中间的空隙（可视段）
            for(int i=1;i<cnt;i++)
            {
                //当前盲区的左端点 > r，代表中间存在一段没有被盲区覆盖的可视空隙
                if(blind[i].first>r+eps)
                {
                    //更新最大可视长度
                    ans=max(ans,blind[i].first-r);
                }
                //更新r，取更大的右边界，合并重叠/相接的盲区
                r=max(r,blind[i].second);
            }
        }

        //ans小于eps，说明最长可视区间几乎等于0，没有能看见房屋的位置
        if(ans < eps)
        {
            cout<<"No View\n";
        }
        else
        {
            //输出，保留小数点后2位
            cout<<fixed<<setprecision(2)<<ans<<'\n';
        }
    }
    return 0;
}
