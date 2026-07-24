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
            cout<<fixed<<setprecision(20);
            int T;  cin>>T;
            while(T--)
            {
                double n;   cin>>n;
                int m=2*n;  cout<<m<<'\n';
                int k=(int)ceil(sqrt(n));
                double d=0.0100000000001;
                for(int i=0;i<n+1;i++)
                {
                    double x=(i/k)*d;
                    double y=(i%k)*d;
                    cout<<x<<" "<<y<<" 1.0\n";
                }
                for(int i=0;i<n+1;i++)
                {
                    double x=(i/k)*d;
                    double y=(i%k)*d;
                    cout<<x<<" "<<y<<" 0.0\n";
                }
            }
            return 0;
        }