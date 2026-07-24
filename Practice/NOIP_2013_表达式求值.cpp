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
const int MOD=10000;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;   cin>>s;
    int j=1;
    int ans=0;
    int cur=0;
    for(int i=0;i<s.size();i++)   
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            cur=(cur*10+(s[i]-'0'))%MOD;
        }
        else
        {
            j=j*cur%MOD;
            if(s[i]=='+')   {ans=(ans+j)%MOD;j=1;}
            cur=0;
        }
    }
    j=j*cur%MOD;
    ans=(ans+j)%MOD;
    cout<<ans;
    return 0;
}