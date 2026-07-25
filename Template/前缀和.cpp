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
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,q;    cin>>n>>q;
    vl a(n+1);
    vl pre(n+1,0);
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
        pre[i]=pre[i-1]+a[i];
    }
    while(q--)
    {
        ll l,r;    cin>>l>>r;
        cout<<pre[r]-pre[l-1]<<"\n";
    }
    return 0;
}