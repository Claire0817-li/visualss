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
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x<<1) + (x<<3) + (ch^48);
        ch = getchar();
    }
    return x * f;
}
int main()
{
    int t = read();
    while(t--)   
    {
        int n=read(),k=read();
        priority_queue<int> a;                  
        for(int i=0;i<n;i++)
        {
            int x=read();
            a.push(x); 
            if(a.size()>k)  a.pop();
        }
        cout<<a.top()<<"\n";
    }
    return 0;
}