#include <iostream>
using namespace std;
int x1,x2,b[100000],k[100000],n,i,j;
bool rez=0;
int main()
{
    cin>>n>>x1>>x2;
    for(i=1;i<=n;i++)
    {
        cin>>k[i]>>b[i];
    }
    i=1;
    while(i<=(n+1)/2&&!rez){
        j=i+1;
        while(j<=(n+1)/2&&!rez){
            if(k[i]-k[j]!=0)
            {
                if(double(x1)<double(double(b[j]-b[i])/(k[i]-k[j]))&&double(x2)>double(double(b[j]-b[i])/(k[i]-k[j])))
                    rez=1;
                    if(double(x1)<double(double(b[j]-b[n-i+1])/(k[n-i+1]-k[j]))&&double(x2)>double(double(b[j]-b[n-i+1])/(k[n-i+1]-k[j])))
                    rez=1;
            }
            if(k[n-i+1]-k[n-j+1]!=0)
            {
                    if(double(x1)<double(double(b[n-j+1]-b[n-i+1])/(k[n-i+1]-k[n-j+1]))&&double(x2)>double(double(b[n-j+1]-b[n-i+1])/(k[n-i+1]-k[n-j+1])))
                    rez=1;
                    if(double(x1)<double(double(b[n-j+1]-b[i])/(k[i]-k[n-j+1]))&&double(x2)>double(double(b[n-j+1]-b[i])/(k[i]-k[n-j+1])))
                    rez=1;
            }
            j++;
        }
        i++;
    }
    cout<<(rez==1 ? "YES":"NO");
    return 0;
}