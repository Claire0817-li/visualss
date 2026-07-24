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
int get(char c)
{
    if(c>='0'&&c<='9')
    {
        return c-'0';
    }
    return c-'A'+10;
}
char put(int x)
{
    if(x<10)
    {
        return '0'+x;
    }
    return 'A'+x-10;
}
bool check(string s)
{
    string ss=s;
    reverse(ss.begin(),ss.end());
    return s==ss;
}
string add(string a,string b,int n)
{
    string res;
    int i=a.size()-1,j=b.size()-1;
    int carry=0;
    while(i>=0||j>=0||carry)
    {
        int x=0,y=0;
        if(i>=0)
        {
            x=get(a[i]);
        }
        if(j>=0)
        {
            y=get(b[j]);
        }
        int sum=x+y+carry;
        res.push_back(put(sum%n));
        carry=sum/n;
        i--;
        j--;
    }
    reverse(res.begin(),res.end());
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  string m;
    cin>>n>>m;
    for(int step=0;step<30;step++)
    {
        if(check(m))
        {
            cout<<"STEP="<<step;
            return 0;
        }
        string rev=m;
        reverse(rev.begin(),rev.end());
        m=add(m,rev,n);
    }
    cout<<"Impossible!";
    return 0;
}