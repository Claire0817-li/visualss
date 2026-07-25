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
    int n,q;    cin>>n>>q;
    vl a(n+2,0),diff(n+2),pre(n+2,0);
    for(int i=1;i<=n;i++)   
    {
        cin>>a[i];
        diff[i]=a[i]-a[i-1];
    }
    while(q--)
    {
        int l,r,d;  cin>>l>>r>>d;
        diff[l]+=d,diff[r+1]-=d;
    }
    for(int i=1;i<=n;i++)   
    {
        pre[i]=pre[i-1]+diff[i];
        cout<<pre[i]<<" ";
    }
    return 0;
}