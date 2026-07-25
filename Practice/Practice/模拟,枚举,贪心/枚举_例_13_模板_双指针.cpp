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
    int n;  cin>>n;
    vi a(n);
    for(int i=0;i<n;i++)    cin>>a[i];
    unordered_map<int,int>pos;
    vector<pair<int,int>> ans;
    int l=0,mx=0;
    for(int r=0;r<n;r++)
    {
        if(pos.find(a[r])!=pos.end()&&pos[a[r]]>=l)
        {
            l=pos[a[r]]+1;
        }
        int len=r-l+1;
        pos[a[r]]=r;
        if(len>mx)
        {
            mx=len;
            ans.clear();
            ans.push_back({l,r});
        }
        else if(len==mx)
        {
            ans.push_back({l,r});
        }
    }
    cout<<ans.size()<<"\n";
    for(auto [l,r]:ans)
    {
        cout<<l+1<<" "<<r+1<<"\n";
    }
    return 0;
}