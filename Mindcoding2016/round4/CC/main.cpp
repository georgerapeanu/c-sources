#include <iostream>
#include <bitset>
using namespace std;
int fstap[50005];///nearly called this one fap :)
int N;
long long rez;
int AIB[100005];
void update(int poz,int val)
{
    for(int i=poz;i<=100000;i+=(i&(-i)))
        AIB[i]+=val;
}
int q(int poz)
{
   int sum=0;
   for(int i=poz;i;i-=(i&(-i)))
        sum+=AIB[i];
   return sum;
}
int main()
{
    cin>>N;
    for(int i=1;i<=2*N;i++)
    {
        int val;
        cin>>val;
        if(!fstap[val]){fstap[val]=i;update(i,1);}
        else
        {
            rez+=q(i)-q(fstap[val]);
            update(fstap[val],-1);
        }
    }
    cout<<rez;
    return 0;
}
