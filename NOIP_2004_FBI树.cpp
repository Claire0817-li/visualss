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
char getroot(string s)
{
    bool B=true,I=true;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]!='1') I=false;
        else B=false;
    }
    if(B)   {return 'B';}
    if(I)   {return 'I';}
    return 'F';
}
void buid(string s)
{
    char root=getroot(s);
    int len=s.size();
    if(len>1)
    {
        string left=s.substr(0,len/2);
        string right=s.substr(len/2);
        buid(left);buid(right);
    }
    cout<<root;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    string s;   cin>>s;
    buid(s);
    return 0;
}