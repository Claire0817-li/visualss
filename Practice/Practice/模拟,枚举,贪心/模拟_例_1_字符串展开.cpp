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
    int p1,p2,p3;   cin>>p1>>p2>>p3;
    string s,ans;   cin>>s;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='-')
        {
            char a=s[i-1],b=s[i+1];
            string m;
            if(isdigit(a)&&isdigit(b))
            {
                if(a<b)
                {
                    if(p1==1||p1==2)
                    {
                        for(char i=a+1;i<b;i++)
                        {
                            for(int j=0;j<p2;j++)
                            {
                                m+=i;
                            }
                        }
                    }
                    else if(p1==3)
                    {
                        for(char i=a+1;i<b;i++)
                        {
                            for(int i=0;i<p2;i++)
                            {
                                m+="*";
                            }
                        }
                    }
                    if(p3==2)   reverse(m.begin(),m.end());
                    ans+=m;
                }
                else    ans+='-';
            }
            else if(isalpha(a)&&isalpha(b)&&islower(a)&&islower(b))
            {
                if(a<b)
                {
                    if(p1==1)
                    {
                        for(char i=a+1;i<b;i++)
                        {
                            for(int j=0;j<p2;j++)
                            {
                                m+=i;
                            }
                        }  
                    }
                    else if(p1==2)
                    {
                        for(char i=a+1;i<b;i++)
                        {
                            for(int j=0;j<p2;j++)
                            {
                                m+=(char)towupper(i);
                            }
                        }  
                    }
                    else if(p1==3)
                    {
                        for(int i=a+1;i<b;i++)
                        {   
                            for(int j=0;j<p2;j++)
                            {
                                m+="*";
                            }
                        }
                    }
                    if(p3==2) reverse(m.begin(),m.end());
                    ans+=m;
                }   
                else
                {
                    ans+='-';
                }
            }
            else
            {
                ans+=s[i];
            }
        }
        else
        {
            ans+=s[i];
        }
    }
    cout<<ans;
    return 0;
}