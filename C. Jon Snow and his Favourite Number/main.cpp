#include <iostream>
#define VMAX 2048
#define POZ (i%2)
using namespace std;
int fr[2][VMAX];
int N,K,x;
int maimici=0;
int main()
{
    cin>>N>>K>>x;
    for(int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        fr[0][val]++;
    }
    for(int i=1;i<=K;i++)
    {
        maimici=0;
        for(int j=0;j<VMAX;j++)
            fr[POZ][j]=0;
        for(int j=0;j<VMAX;j++)
        {
            int adaug=fr[1-POZ][j]/2+(maimici%2==0&&fr[1-POZ][j]%2==1);
            fr[POZ][x^j]+=adaug;
            fr[POZ][j]+=fr[1-POZ][j]-adaug;
            maimici+=fr[1-POZ][j];
        }
    }
    int minim=(1<<30),maxim=0;
    for(int i=0;i<VMAX;i++)
    {
        if(fr[K%2][i])
            {minim=min(minim,i);maxim=max(i,maxim);}
    }
    cout<<maxim<<" "<<minim;
    return 0;
}
