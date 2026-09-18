/*题目：二叉树的前序、中序、后序遍历
题目描述：
给定一棵 n 个节点的二叉树，节点编号 1~n。
接下来 n‑1 条边：u v o
u：父节点，v：子节点
o=0：v 是 u 的左孩子；o=1：v 是 u 的右孩子。
f数组标记哪些点是子节点，用来寻找根节点（根不会作为别人的孩子）。

输出：
第一行：前序遍历
第二行：中序遍历
第三行：后序遍历

思路：
1. ls[] 存左孩子，rs[] 存右孩子；0 代表空节点。
2. f[]标记：如果某个点是别人的孩子，则 f[v]=true。
3. 遍历1~n，f[i]==false 的就是根节点。
4. 递归实现三种遍历：
    前序：根 → 左子树 → 右子树
    中序：左子树 → 根 → 右子树
    后序：左子树 → 右子树 → 根

注意点：
- n个节点的二叉树一共 n‑1 条边
- 节点编号从1开始，空孩子存0
- 递归终止条件 root == 0
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=200005;   // 最大节点数，2e5+5
int ls[N],rs[N];       // ls[u]:u的左孩子; rs[u]:u的右孩子; 0表示无孩子
bool f[N];             // f[v]=true 代表v是某个节点的子节点

// 前序遍历：根 -> 左 -> 右
void pre(int root)
{
    if(root==0) return;    // 空节点直接返回，递归出口
    cout<<root<<" ";       // 访问根节点
    pre(ls[root]);         // 递归遍历左子树
    pre(rs[root]);         // 递归遍历右子树
}

// 中序遍历：左 -> 根 -> 右
void in(int root)
{
    if(root==0) return;
    in(ls[root]);          // 递归遍历左子树
    cout<<root<<" ";       // 访问根节点
    in(rs[root]);          // 递归遍历右子树
}

// 后序遍历：左 -> 右 -> 根
void post(int root)
{
    if(root==0) return;
    post(ls[root]);        // 递归遍历左子树
    post(rs[root]);        // 递归遍历右子树
    cout<<root<<" ";       // 访问根节点
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;  cin>>n;
    for(int i=1;i<n;i++)   // n个节点，n‑1条父子边
    {
        int u,v,o;  cin>>u>>v>>o;
        if(o==0)
        {
            ls[u]=v;      // o=0：v是u的左孩子
        }
        else
        {
            rs[u]=v;      // o=1：v是u的右孩子
        }
        f[v]=true;        // v成为子节点，标记为true
    }

    // 找根节点：根不会作为任何点的孩子，f[root]=false
    int root;
    for(int i=1;i<=n;i++)
    {
        if(!f[i])
        {
            root=i;
            break;
        }
    }

    pre(root);  cout<<"\n";   // 输出前序
    in(root);   cout<<"\n";   // 输出中序
    post(root); cout<<"\n";   // 输出后序

    return 0;
}
