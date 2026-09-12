/*
题目：给定二叉树的前序遍历、后序遍历，求中序遍历
注意：
前序：根 左子树 右子树
后序：左子树 右子树 根

⚠️重要性质：
只给前序+后序，**二叉树不一定唯一**；当某个节点只有左孩子或只有右孩子时，无法区分。
本题代码默认：pre[p1+1] 是根的左儿子，强行认为存在左子树，以此划分左右子树。
如果原树实际没有左子树、只有右子树，该代码会出错。

参数说明 dfs(p1,p2,len):
p1：前序数组的起始下标
p2：后序数组的起始下标
len：当前子树一共有 len 个节点

推导逻辑：
1. pre[p1] 是当前子树的根。
2. pre[p1+1] 是根的左子树的根（代码假设一定存在左子树）。
3. 在post数组找到左子树根的位置 pos[leftroot]。
4. leftsize：左子树节点数量。
5. 递归处理左子树；存入根到in（中序）；递归处理右子树。

输入：
n
前序n个数字
后序n个数字

输出：
输出中序遍历序列
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=100005;
int pre[N];   // pre[]：前序遍历数组
int post[N];  // post[]：后序遍历数组
int pos[N];   // pos[x]：记录值x在post数组中的下标，快速查找位置
vi in;        // 存储求出的中序遍历结果

/**
 * @param p1 当前子树在前序数组的起点下标
 * @param p2 当前子树在后序数组的起点下标
 * @param len 当前子树的节点总数
 */
void dfs(int p1,int p2,int len)
{
    if(len<=0)  return;                 // 子树节点数为0，直接返回
    if(len==1)
    {
        in.push_back(pre[p1]);          // 只有一个节点，直接加入中序序列
        return;
    }
    // pre[p1]是当前根；pre[p1+1]假定为左子树的根
    int leftroot=pre[p1+1];
    // 找到左子树根在后序数组中的下标
    int left_pos=pos[leftroot];
    // 计算左子树的节点个数
    int leftsize=left_pos-p2+1;

    // 递归处理左子树
    dfs(p1+1, p2, leftsize);
    // 中序：左子树处理完，访问根节点
    in.push_back(pre[p1]);
    // 递归处理右子树
    // p1+1+leftsize：前序中右子树起点；p2+leftsize：后序中右子树起点；len-leftsize-1：右子树节点数
    dfs(p1+1+leftsize, p2+leftsize, len-leftsize-1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;  cin>>n;
    for(int i=0;i<n;i++)   cin>>pre[i];
    for(int i=0;i<n;i++)
    {
        cin>>post[i];
        pos[post[i]]=i;   // 记录每个值在后序数组的下标
    }
    dfs(0,0,n);

    for(int x:in)
    {
        cout<<x<<" ";
    }
    return 0;
}
