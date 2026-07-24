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
int la,lb,lc;
int A[3005],B[3005],C[6010];
void cheng(int A[],int B[],int C[])
{
    for(int i=0;i<la;i++)
    {
        for(int j=0;j<lb;j++)
        {
            C[i+j]+=A[i]*B[j];
        }
    }
    lc=la+lb;
    for(int i=0;i<lc;i++)
    {
        C[i+1]+=C[i]/10;
        C[i]%=10;
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
        la=a.size();lb=b.size();
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        memset(C,0,sizeof(C));
        for(int i=0;i<la;i++)   {A[la-i-1]=a[i]-'0';}
        for(int i=0;i<lb;i++)   {B[lb-i-1]=b[i]-'0';}
        cheng(A,B,C);
        for(int i=lc-1;i>=0;i--)
        {
            cout<<C[i];
        }
        cout<<"\n";
    }
    return 0;
}