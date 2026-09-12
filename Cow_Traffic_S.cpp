#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=5005;
int n,m;
vi e[N];
vi re[N];
vi dp1(N,0),dp2(N,0);
vi din1(N,0);
vector<pair<int,int>> edges;
void topusort1()
{
    queue<int> q;
    for(int i=1;i<=n;i++)    
    {
        if(din1[i]==0)   {q.push(i);dp1[i]=1;}
    }
    while(q.size())
    {
        int x=q.front();    q.pop();
        for(int y:e[x])
        {
            if(--din1[y]==0) q.push(y);
            dp1[y]+=dp1[x];
        }
    }
}
void topusort2()
{
    vi din2(N,0);
    for(int u=1;u<=n;u++)
    {
        for(int v:re[u])    din2[v]++;
    }
    queue<int> q;
    q.push(n);
    dp2[n]=1;
    while(q.size())
    {
        int x=q.front();    q.pop();
        for(int y:re[x])
        {
            if(--din2[y]==0) q.push(y);
            dp2[y]+=dp2[x];
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v;    cin>>u>>v;
        edges.emplace_back(u,v);
        e[u].push_back(v);
        re[v].push_back(u);
        din1[v]++;
    }
    topusort1();
    topusort2();
    int ans=0;
    for(auto &pr:edges)
    {
        int u=pr.first,v=pr.second;
        ans=max(ans,dp1[u]*dp2[v]);
    }
    cout<<ans;
    return 0;
}