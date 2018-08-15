#include <iostream>

using namespace std;
char A[12];
int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int main()
{
    for(int i=1;i<=3;i++)
    {
        cin.getline(A+1,12);
        if(A[8]!='1'&&A[8]!='6'&&A[8]!='9'){cout<<"0\n";continue;}
        int sum=0;for(int i=1;i<=8;i++)sum=(sum+(A[i]-'0')*(A[i]-'0'))%7;
        if(sum!=A[9]-'0'){cout<<"0\n";continue;}
        int d,m,a;
        d=(A[1]-'0')*10+A[2]-'0';
        m=(A[3]-'0')*10+A[4]-'0';
        a=(A[5]<'6' ? 2000:1000)+(A[5]-'0')*100+(A[6]-'0')*10+A[7]-'0';
        bool leap=(a%4==0);
        if(a%4==0&&a%100==0&&a%400!=0)leap=0;
        if(d==0||m==0||m>12){cout<<"0\n";continue;}
        if(d>days[m]+(m==2&&leap)){cout<<"0\n";continue;}
        cout<<"1\n";continue;
    }
    return 0;
}
