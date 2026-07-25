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
    string s;  cin>>s;
    int len=s.size();
    int q;  cin>>q;
    while(q--)
    {
        string t;   cin>>t;
        int l=0,r=0;
        while(l<len)
        {
            if(s[l]==t[r])  {r++;l++;}
            else
            {
                l++;
            }
        }
        cout<<((r==t.size())?"YES":"NO")<<"\n";
    }
    return 0;
 }