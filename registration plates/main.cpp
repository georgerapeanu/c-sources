#include <iostream>
#include <cstring>
using namespace std;
char C[20];
int N,i,M,j;
bool cifra(char c)
{
    return '0'<=c&&c<='9';
}
bool maj(char c)
{
    return 'A'<=c&&c<='Z';
}
int main()
{
    //cin.sync_with_stdio();
   // cout.sync_with_stdio();
    cin>>N;
    cin.getline(C,20);
    for(i=1;i<=N;i++)
    {
        cin.getline(C,20);
        M=strlen(C);
        if(M>9||M<8)
            {cout<<"Incorrect!\n";continue;}
        if(C[1]!=' ')
        {
            if(M!=9)
                {cout<<"Incorrect!\n";continue;}
            else if(maj(C[0])&&maj(C[1])==0)
                {cout<<"Incorrect!\n";continue;}
            else if(C[2]!=' ')
                {cout<<"Incorrect!\n";continue;}
            else if(!(cifra(C[3])&&cifra(C[4])))
                {cout<<"Incorrect!\n";continue;}
            else if(C[5]!=' ')
                {cout<<"Incorrect!\n";continue;}
            else if(maj(C[6])&&maj(C[7])&&maj(C[8])==0)
                {cout<<"Incorrect!\n";continue;}
            else
                cout<<"Correct!\n";continue;
        }
        else
        {
            if(cifra(C[4]))
                {j=5;if(M!=9)
                {cout<<"Incorrect!\n";continue;}}
            else
                {j=4;if(M!=8)
                {cout<<"Incorrect!\n";continue;}}
             if(C[0]!='B')
                {cout<<"Incorrect!\n";continue;}
            else if(cifra(C[2])&&cifra(C[3])==0)
                {cout<<"Incorrect!\n";continue;}
            else if(C[j]!=' ')
                {cout<<"Incorrect!\n";continue;}
            else if(maj(C[j+1])&&maj(j+2)&&maj(j+3)==0)
                {cout<<"Incorrect!\n";continue;}
            else
                cout<<"Correct!\n";continue;
        }
    }
    return 0;
}
