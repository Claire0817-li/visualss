#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=25;
int n,k;
vi x(N+1);
vl tot;
void dfs(int pos,int cnt,ll sum)
{
    if(cnt==k)
    {
        tot.push_back(sum);
        return;
    }
    for(int i=pos;i<=n-k+cnt+1;i++)
    {
        dfs(i+1,cnt+1,sum+x[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    for(int i=1;i<=n;i++)    cin>>x[i];
    dfs(1,0,0);
    ll maxS=0;
    for(auto v:tot) maxS=max(maxS,v);
    vector<bool> isPrime(maxS+1,true);
    isPrime[0]=isPrime[1]=false;
    for(ll i=2;i*i<=maxS;i++)
    {
        if(isPrime[i])
        {
            for(ll j=i*i;j<=maxS;j+=i)
            {
                isPrime[j]=false;
            }
        }
    }
    int ans=0;
    for(auto s:tot)
    {
        if(isPrime[s]) ans++;
    }
    cout<<ans;
    return 0;
}