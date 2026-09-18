#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=505;
const double eps=1e-8;
int n,m;
vi e[N];
pair<int,int> edge[125005];
vi din(N,0);
double a[N][N];
double g[125005];
bool gauss()
{
    for(int i=1;i<=n-1;i++)
    {
        int r=i;
        for(int k=i;k<=n-1;k++)
        {
            if(fabs(a[k][i])>eps)
            {
                r=k;break;
            }
        }
        if(r!=i) swap(a[r],a[i]);
        if(fabs(a[i][i])<eps) return false;

        for(int k=1;k<=n-1;k++)
        {
            if(k==i) continue;
            double t=a[k][i]/a[i][i];
            for(int j=1;j<=n;j++)
            {
                a[k][j]-=t*a[i][j];
            }
        }
    }
    for(int i=1;i<=n-1;i++)
    {
        a[i][n]/=a[i][i];
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        din[u]++;
        din[v]++;
        edge[i]={u,v};
    }
    for(int u=1;u<=n-1;u++)
    {
        a[u][u]=1.0;
        for(int v:e[u])
        {
            if(v!=n)    a[u][v]-=1.0/din[v];
        }
        if(u==1)    a[u][n]=1;
        else    a[u][n]=0.0;
    }
    gauss();
    for(int i=1;i<=m;i++)
    {
        int u=edge[i].first,v=edge[i].second;
        g[i]=0.0;
        if(u!=n) g[i]+=a[u][n]/din[u];
        if(v!=n) g[i]+=a[v][n]/din[v];
    }
    sort(g+1,g+1+m);
    double ans=0.0;
    for(int i=1;i<=m;i++)
    {
        ans+=g[i]*(m-i+1);
    }
    cout<<fixed<<setprecision(3)<<ans<<endl;
    return 0;
}