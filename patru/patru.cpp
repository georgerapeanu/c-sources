#include<fstream>
#include<math.h>
using namespace std;
ifstream f("patru.in");
ofstream g("patru.out");
long long x,y,n,K,i,j,n4,s=0,uc,s4,lim,prod,z,power;
long long v[20005],S[20005];
bool e[1000000005];
long long nr[180];
bool ok;
double a;
int main()
{
    f>>n>>K;
    for(i=1;1;i++)
    {
        z=i;
        power=4;
        prod=1;
        while(power)
        {
            if(power&1) prod*=z;
            z*=z;
            power>>=1;
        }
        if(prod>1000000000)
            break;
        nr[++nr[0]]=prod;
        e[prod]=1;
    }
   for(i=0;i<n;i++)
    {
        f>>v[i];
        j=1;
        while(v[i]>nr[j]&&j<nr[0]&&e[v[i]-nr[j]]==0)
            j++;
        if(j!=nr[0]&&v[i]>nr[j])
            n4++;
        S[i+1]=(S[i]+(((v[i]*v[i])%10*v[i])%10*v[i])%10)%10;
    }
    for(i=1;i<=n-K+1;i++)
    {
        if((S[i+K-1]-S[i-1])%10==4||(S[i+K-1]-S[i-1])%10==-6)
            s4++;
    }
    g<<n4<<"\n"<<s4;
f.close();g.close();
return 0;
}
