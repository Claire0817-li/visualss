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
string s,ans;
void dfs(int l,int r)
{
    bool has0=false,has1=false;
    for(int i=l;i<=r;i++)
    {
        if(s[i]=='0') has0=true;
        else has1=true;
    }
    char ch;
    if(!has1)   ch='B';
    else if(!has0) ch='I';
    else ch='F';

    if(l<r)
    {
        int mid=(l+r)/2;
        dfs(l,mid);
        dfs(mid+1,r);
    }
    ans+=ch;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    cin>>s;
    dfs(0,s.size()-1);
    cout<<ans;
    return 0;
}