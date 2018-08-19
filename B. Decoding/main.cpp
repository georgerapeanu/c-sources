#include <iostream>
using namespace std;
char C[2005];
char R[2005];
int N,mid;
int main()
{
    cin>>N;
    cin.getline(C+1,2005);
    cin.getline(C+1,2005);
    if(N%2==0)
    {
        mid=N/2;
        R[mid]=C[1];
        for(int i=1;i<=N/2-1;i++)
        {
            R[mid+i]=C[2*i];
            R[mid-i]=C[2*i+1];
        }
        R[N]=C[N];
        cout<<R+1;
    }
    else
    {
        mid=1+N/2;
        R[mid]=C[1];
        for(int i=1;i<=N/2;i++)
        {
            R[mid-i]=C[2*i];
            R[mid+i]=C[2*i+1];
        }
        cout<<R+1;
    }
    return 0;
}
