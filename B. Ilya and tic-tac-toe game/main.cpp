#include <iostream>
using namespace std;
char C[4][4];
int main()
{
    for(int i=0;i<4;i++)
        cin.getline(C[i],5);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(C[i][j]=='.')
            {
                ///verticala
                int st,dr;
                st=dr=i;
                while(st>0&&C[st-1][j]=='x')
                    st--;
                while(dr<3&&C[dr+1][j]=='x')
                    dr++;
                if(dr-st+1>=3)
                    {cout<<"YES";return 0;}
                ///orizontala
                st=dr=j;
                while(st>0&&C[i][st-1]=='x')
                    st--;
                while(dr<3&&C[i][dr+1]=='x')
                    dr++;
                if(dr-st+1>=3)
                    {cout<<"YES";return 0;}
                ///diagonala1
                st=dr=0;
                while(i+st>0&&j+st>0&&C[i+st-1][j+st-1]=='x')
                    st--;
                while(i+dr<3&&j+dr<3&&C[i+dr+1][j+dr+1]=='x')
                    dr++;
                if(dr-st+1>=3)
                    {cout<<"YES";return 0;}
                ///diagonala2
                st=dr=0;
                while(i-st<3&&j+st>0&&C[i-st+1][j+st-1]=='x')
                    st--;
                while(i-dr>0&&j+dr<3&&C[i-dr-1][j+dr+1]=='x')
                    dr++;
                if(dr-st+1>=3)
                   {cout<<"YES";return 0;}
            }
        }
    }
    cout<<"NO";
    return 0;
}
