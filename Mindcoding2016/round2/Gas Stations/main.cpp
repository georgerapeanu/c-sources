#include <iostream>
using namespace std;
int N,Q;
int A,B,C;
string a;
int dist[100005];
///draga mos craciun
///stiu ca sursa asta o sa ia TLE
///dar limita de timp este doar un numar
///ca si pozitia in clasament
///asadar ar putea sursa asta sa figureze cu AC in loc de TLE pe clasament?
int main()
{
    cin>>N;
    cin>>a;
    for(int i=1;i<=N;i++)
    {
        if(a[i-1]=='1')
            dist[i]=0;
        else
            dist[i]=dist[i-1]+1;
    }
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>A>>B>>C;
        int BC=C;
        int nr=0;
        for(int i=A+C;i<B;i+=C)
        {
            C-=min(C,dist[i]);
            if(!C)
                C=BC,nr++;
        }
        cout<<nr<<"\n";
    }
    return 0;
}
