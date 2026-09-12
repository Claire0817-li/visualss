#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=100005;
int n,m;
vi e[N];
vi din(N);
vi tp()
{
    vi res;
    priority_queue<int,vi,greater<int>> q;
    for(int i=1;i<=n;i++)
    {
        if(din[i]==0)   q.push(i);
    }
    while(q.size())
    {
        int x=q.top();  q.pop();
        res.push_back(x);
        for(int y:e[x])
        {
            if(--din[y]==0)
            {
                q.push(y);
            }
        }
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v;    cin>>u>>v;
        e[u].push_back(v);
        din[v]++;
    }
    for(int x:tp())
    {
        cout<<x<<" ";
    }
    return 0;
}