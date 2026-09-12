/*
题目：洛谷 P1347 排序
算法标签：图论、Kahn拓扑排序、判环、拓扑序列唯一性判定
题目大意：
给定n个大写字母(A~Z)，m组 A<B 的大小关系。
每添加一组关系后立刻做检测，分三种情况：
1. 出现环(矛盾)：输出 Inconsistency found after x relations. 程序直接结束
2. 可以确定n个元素唯一完整排序：输出 Sorted sequence determined after x relations: xxx. 程序直接结束
3. m组关系全部处理完，既无环也无法确定唯一顺序：输出 Sorted sequence cannot be determined.
提示：一旦发现矛盾或者确定顺序，后面输入不再处理。

解题思路：
1. 字符映射数字：A→0，B→1……。A<B 建立有向边 u→v。
2. 每新增一条边，复制一份入度数组副本跑Kahn，绝对不能修改原图入度，原图还要继续加边。
3. Kahn算法过程：
   ① 将入度为0的点入队列。
   ② 如果队列同时存在≥2个入度0点，说明有多条可选路径，拓扑序不唯一 only=false。
   ③ 弹出队首节点，加入拓扑序列，消除它所有出边，后继节点副本入度减一；入度变为0则入队列。
   ④ 拓扑序列长度不等于n：存在环 cycle=true。
4. 每读入1条边就跑一次拓扑；一旦命中矛盾/确定顺序立刻break终止；全部读完无结果输出第三种。
n≤26，规模很小，每次完整重跑拓扑时间完全够用。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=27;   //最多26个大写字母
int n;            //需要排序的元素总个数
vi e[N];          //邻接表，存图 e[u]存放u所有后继节点
vi din(N, 0);     //原图入度数组，全局，Kahn只能拷贝副本，严禁直接修改此数组

//Kahn函数返回结果结构体
struct res
{
    bool cycle;   //true代表图存在环，发生矛盾
    bool only;    //true代表拓扑序列唯一
    vi seq;       //保存拓扑排序得到的序列
};

// topo函数：不修改原图，拷贝入度副本执行Kahn拓扑排序
res topo()
{
    int cur[N];
    //复制原图din到cur副本，所有操作只修改cur，保护原图din
    for(int i = 0; i < N; ++i)
        cur[i] = din[i];

    queue<int> q;
    res ans;
    ans.only = true;    //初始标记拓扑序是唯一
    ans.seq.clear();    //清空拓扑序列

    //第一步：把所有入度为0的点压入队列
    for(int i = 0; i < n; ++i)
    {
        if(cur[i] == 0)
            q.push(i);
    }

    while(!q.empty())
    {
        //核心判断：队列size>1，有多个可选起点，拓扑序不可能唯一
        if(q.size() > 1)
            ans.only = false;

        int x = q.front();
        q.pop();
        ans.seq.push_back(x);   //x加入拓扑序列

        //遍历x所有后继y，删除x→y这条边（只修改副本cur）
        for(int y : e[x])
        {
            if(--cur[y] == 0)
                q.push(y);
        }
    }
    //拓扑序列长度不等于n，说明有节点无法访问到，图存在环
    ans.cycle = (ans.seq.size() != n);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> n >> m;
    bool finished = false;  //标记是否已经得到答案，用来提前结束程序

    //循环读取m组关系，i从0开始，输出序号i+1
    for(int i = 0; i < m; ++i)
    {
        string s;
        cin >> s;               //直接读取整行关系字符串，格式"A<B"
        int a = s[0] - 'A';     //左边字符转为数字
        int b = s[2] - 'A';     //右边字符转为数字
        e[a].push_back(b);      //添加有向边 a → b
        din[b]++;               //原图b节点入度+1

        res r = topo();         //【重要】只跑一次拓扑排序，结果保存到r，复用r，禁止重复调用topo()

        //情况1：检测出环，关系矛盾
        if(r.cycle)
        {
            cout << "Inconsistency found after " << i+1 << " relations.\n";
            finished = true;
            break;  //跳出读入循环，不再处理后面输入
        }
        //情况2：无环，拓扑序唯一，并且已经排满n个元素，确定完整顺序
        if(r.only && r.seq.size() == n)
        {
            cout << "Sorted sequence determined after " << i+1 << " relations: ";
            for(int x : r.seq)
            {
                cout << (char)('A' + x);  //数字转回大写字母输出
            }
            cout << ".\n";
            finished = true;
            break;  //跳出读入循环，不再处理后面输入
        }
        //既无环也没有得到完整唯一顺序：什么都不做，继续读下一组关系
    }
    //m组关系全部处理完毕，依旧没有得到矛盾或者确定顺序
    if(!finished)
    {
        cout << "Sorted sequence cannot be determined.\n";
    }
    return 0;
}
