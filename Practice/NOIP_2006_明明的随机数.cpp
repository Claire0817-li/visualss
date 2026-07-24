//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
// 猫神大人请赐我本世纪最难得的运气[^]_[^]
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
    int n;  cin>>n;
    vi a(n);set<int>b;
    for(int i=0;i<n;i++)    
    {cin>>a[i];
    b.insert(a[i]);}
    cout<<b.size()<<"\n";
    for(int x:b)
    {
        cout<<x<<" ";
    }
    
    return 0;
}