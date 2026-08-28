/*
记忆化搜索DP（自顶向下）
【题目：数字三角形】
题目描述：
给定一个数字三角形，第 i 行共有 i+1 个数字。
从顶端(0,0)出发，每一步可以走到正下方(x+1,y)或者右下方(x+1,y+1)。
求到达三角形最底层的所有路径中，路径数字总和的最大值。

算法类型：动态规划，记忆化DFS（递归实现）
状态定义：f[x][y]：从位置(x,y)出发，走到三角形底部的最大路径和
边界条件：x == r‑1（到达最后一行），f[x][y] = a[x][y]
转移方程：f[x][y] = a[x][y] + max(dfs(x+1,y), dfs(x+1,y+1))

记忆化原理：f数组初始‑1标记未计算；同一个(x,y)会被多条路径递归访问，只计算一次结果存入f[x][y]，后续直接读取，避免指数级暴力递归。
时间复杂度 O(r²)，r为三角形行数，每个格子仅计算一次。
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;


const int N=1005;
vvi a(N,vi(N));   // a：存储数字三角形，下标从0开始
vvi f(N,vi(N,-1));// f[x][y]记忆化缓存；‑1代表该位置还没有计算过
int r;            // r：三角形总层数


// dfs(x,y)：返回从坐标(x,y)位置走到三角形最底层的最大路径和
int dfs(int x,int y)
{
    // 记忆化：已经计算过该点，直接返回保存好的答案，不再递归
    if(f[x][y]!=-1)
        return f[x][y];

    // 递归边界：已经走到最后一行，无法继续向下走，路径和就是当前格子的值
    if(x==r-1)
        f[x][y]=a[x][y];
    else
    {
        // 当前格子的值 + 选择向下、右下两条路径中的较大值
        f[x][y]=a[x][y]+max(dfs(x+1,y),dfs(x+1,y+1));
    }
    return f[x][y];
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>r;  //读入三角形层数
    //读入三角形数据：第i行有 i+1 个数字，j范围 0~i
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<=i;j++)
            cin>>a[i][j];
    }
    //起点为三角形顶点(0,0)，输出最大路径和
    cout<<dfs(0,0);
    return 0;
}
