//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=200005;
int ls[N],rs[N];
bool f[N];
void pre(int root)
{
    if(root==0) return;
    cout<<root<<" ";
    pre(ls[root]);
    pre(rs[root]);
}
void in(int root)
{
    if(root==0) return;
    in(ls[root]);
    cout<<root<<" ";
    in(rs[root]);
}
void post(int root)
{
    if(root==0) return;
    post(ls[root]);
    post(rs[root]);
    cout<<root<<" ";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v,o;  cin>>u>>v>>o;
        if(o==0)    {ls[u]=v;}
        else    {rs[u]=v;}
        f[v]=true;
    }
    int root;
    for(int i=1;i<=n;i++)
    {
        if(!f[i])
        {
            root=i;
            break;
        }
    }
    pre(root);  cout<<"\n";
    in(root);  cout<<"\n";
    post(root);  cout<<"\n";
    return 0;
}