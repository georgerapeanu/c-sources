#include <iostream>

using namespace std;
int N,nr,val;
int sample;
char rez[8];
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
        sample=sample*10+1;
    nr=N-1;
    for(int i=1;i<=9;i++)
    {
        cout<<"Q "<<sample*i<<"\n";
        cin>>val;
        cout.flush();
        for(int j=nr-val+1;j<=nr;j++)
            rez[j]=i+'0';
        nr=nr-val;
    }
    cout<<rez;
    return 0;
}
