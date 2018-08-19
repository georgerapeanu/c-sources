#include <iostream>
using namespace std;
int N,val;
int r=0;
///o gramada se va sparge in gramezi de 1 doar dupa [nrpietre/2] mutari
///fie nr=2*N+1
///il spargem in nr1=2*n1+1,nr2=2*n2+1,nr3=2*n3+1,n1+n2+n3=N-1,nr1%2=nr2%2=nr3%2=1
///putem sa spunem deci,deoarece gramezile se vor sparge in serie,ca mutari(nr)=mutari(nr1)+mutari(nr2)+mutari(nr3)+1,adica spargerea de acum
///daca mutari(val)=[val]/2
///mutari(1)=0
///mutari(nr)=[nr1]/2+[nr2]/2+[nr3]/2+1=N
///n1+n2+n3+1=N,adevarat
///daca numarul de mutari e par,castiga al doilea
///altfel primul
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        r+=val/2;
        r%=2;
    }
    if(!r)  cout<<"Stannis";
    else    cout<<"Daenerys";
    return 0;
}
