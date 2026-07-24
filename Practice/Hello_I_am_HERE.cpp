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
const int N=5010;
int la,lb,lc;
int A[N],B[N],C[N];
void add(int A[],int B[],int C[])
{
    for(int i=0;i<lc;i++)
    {
        C[i]+=A[i]+B[i];
        C[i+1]+=C[i]/10;
        C[i]%=10;
    }
    if(C[lc])
    {
        lc++;
    }
    while(lc>1&&C[lc-1]==0)
    {
        lc--;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;  cin>>t;
    while(t--)
    {
        string a,b; cin>>a>>b;
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        memset(C,0,sizeof(C));
        la=a.size(),lb=b.size(),lc=max(la,lb);
        for(int i=la-1;i>=0;i--)    {A[la-1-i]=a[i]-'0';}
        for(int i=lb-1;i>=0;i--)    {B[lb-i-1]=b[i]-'0';}
        add(A,B,C);
        for(int i=lc-1;i>=0;i--)
        {
            cout<<C[i];
        }
        cout<<"\n";
    }
    return 0;
}