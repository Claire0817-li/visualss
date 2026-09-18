#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;    cin>>n>>m;
    vi a(n+1);
    for(int i=1;i<=n;i++)   cin>>a[i];
    int ans=2e9;
    vi q(n+1);
    vi f(n+1);
    int h=1,t=0;
    for(int i=1;i<=n;i++)
    {
        while(h<=t&&f[q[t]]>=f[i-1])    t--;
        q[++t]=i-1;
        if(q[h]<i-m)    h++;
        f[i]=f[q[h]]+a[i];
        if(i>n-m)   ans=min(ans,f[i]);
    }
    cout<<ans;
    return 0;
}